/**
 * @file management/manage.c
 * @brief      implementation of cluster management.
 * @version    0.0.2
 * @author     Ji Xiangyu
 * @date       2021.10.6
 */
#include "manage.h"
#include "soap.h"
#include "bits.h"
#include "network.h"
#include "cJSON.h"
#include "procedure.h"
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#define STR_MAX 100/*!< unified max length of string */

/**
 * @enum request category
 * @brief      identifiers of request type
 */
enum{
	HEART=0,
	ALIVE,
	SYNC,
	RECOVER,
	FAIL,
	MEET,
	PING,
	PONG,
	MOVE,
	DECLARE,
	REJECT,
	STOP
};

struct PTZ_State{
	char* xaddr;/*!< the media service address, used as the unique identifier */
	float pan;/*!< (target/current) pan degree */
	float tilt;/*!< (target/current) tilt degree */
	float zoom;/*!< (target/current) zoom degree */
	int running;/*!< whether the camera is targeting or stand at the given state. */
};

struct Message{
	char* uuid;
	int type;
	union{
		struct{
			char* begin;
			char* end;
			struct Message** messages;
		} sync;
		struct{
			char* begin;
		} recover;
		struct{
			int commit;
			char* ip;
			int port;
		} fail;
		struct{
			char* request;
		} move;
		struct{
			int commit;
			int switcher;
			union{
				struct{
					int slot;
				} light;
				struct{
					int num;
					int* slots;
				} full;
			} mapping;
		} declare;
		struct{
			int switcher;
			union{
				struct{
					int slot;
				} light;
				struct{
					int num;
					int* slots;
				} full;
			} mapping;
		} reject;
		struct{
			void* dummy;
		} exception;
	} data;
};

typedef struct Host{
    int cluster_size;/*!< cluster size */
	int capacity;/*!< maximum of threads which host can be held */
	uint64_t* thread_mapping;/*!< mapping between cameras' addresses and host's thread */
	struct Message** messages;/*!< persistent messages */
	int idle;/*!< whether it is idle node */
} Cluster;

static int boot = 0;
static pthread_t send;/*!< sending thread */
static pthread_t recv;/*!< receiving thread */

static struct Message* parseMessage(char* response);
static char* dumpMessage(struct Message* msg);
static void deleteMessage(struct Message* msg);
static void* send_cycle(void* ptr);
static void* recv_cycle(void* ptr);
static void dummy(void);

static struct Message* parseMessage(char* response){
	struct Message* msg = (struct Message*)malloc(sizeof(struct Message));
	cJSON* json_response = cJSON_Parse(response);
	msg -> uuid = (char*)malloc(STR_MAX);
	strcpy(msg -> uuid, cJSON_GetObjectItem(json_response, "uuid") -> valuestring);
	int type = cJSON_GetObjectItem(json_response, "type") -> valueint;
	msg -> type = type;
	cJSON* data = cJSON_GetObjectItem(json_response, "data");
	switch(type){
		case SYNC:
			(msg -> data).sync.begin = (char*)malloc(STR_MAX);
			(msg -> data).sync.end = (char*)malloc(STR_MAX);
			strcpy((msg -> data).sync.begin, cJSON_GetObjectItem(data, "begin") -> valuestring);
			strcpy((msg -> data).sync.end, cJSON_GetObjectItem(data, "end") -> valuestring);
			cJSON* messages = cJSON_GetObjectItem(data, "messages");
			int check = uuidcmp((msg -> data).sync.begin, (msg -> data).sync.end);
			if(check != UUID_BELOW && check != UUID_EQUAL){
				(msg -> data).sync.messages = NULL;
				break;
			}
			int num = cJSON_GetArraySize(messages);
			(msg -> data).sync.messages = (struct Message**)malloc(num * sizeof(struct Message*));
			int i = 0;
			char* message = (char*)malloc(STR_MAX);
			for(;i < num;i++){
				strcpy(message, cJSON_GetArrayItem(messages, i) -> valuestring);
				(msg -> data).sync.messages[i] = parseMessage(message);
			}
			break;
		case RECOVER:
			(msg -> data).recover.begin = (char*)malloc(STR_MAX);
			strcpy((msg -> data).recover.begin, cJSON_GetObjectItem(data, "begin") -> valuestring);
			break;
		case FAIL:
			(msg -> data).fail.commit = cJSON_GetObjectItem(data, "commit") -> valueint;
			(msg -> data).fail.ip = (char*)malloc(STR_MAX);
			strcpy((msg -> data).fail.ip, cJSON_GetObjectItem(data, "ip") -> valuestring);
			(msg -> data).fail.port = cJSON_GetObjectItem(data, "port") -> valueint;
			break;
		case MOVE:
			(msg -> data).move.request = (char*)malloc(STR_MAX * STR_MAX);
			strcpy((msg -> data).move.request, cJSON_GetObjectItem(data, "request") -> valuestring);
			break;
		case DECLARE:
			(msg -> data).declare.commit = cJSON_GetObjectItem(data, "commit") -> valueint;
			(msg -> data).declare.switcher = cJSON_GetObjectItem(data, "switcher") -> valueint;
			cJSON* mapping_declare = cJSON_GetObjectItem(data, "mapping");
			if((msg -> data).declare.switcher){
				//full mode
				(msg -> data).declare.mapping.full.num = cJSON_GetObjectItem(mapping_declare, "num") -> valueint;
				int num = (msg -> data).declare.mapping.full.num;
				cJSON* slots = cJSON_GetObjectItem(mapping_declare, "slots");
				(msg -> data).declare.mapping.full.slots = (int*)malloc(num * sizeof(int));
				int i = 0;
				for(;i < num;i++)
					(msg -> data).declare.mapping.full.slots[i] = cJSON_GetArrayItem(slots, i) -> valueint;
			}else
				//light mode
				(msg -> data).declare.mapping.light.slot = cJSON_GetObjectItem(mapping_declare, "slot") -> valueint;
			break;
		case REJECT:
			(msg -> data).reject.switcher = cJSON_GetObjectItem(data, "switcher") -> valueint;
			cJSON* mapping_reject = cJSON_GetObjectItem(data, "mapping");
			if((msg -> data).reject.switcher){
				//full mode
				(msg -> data).reject.mapping.full.num = cJSON_GetObjectItem(mapping_reject, "num") -> valueint;
				int num = (msg -> data).reject.mapping.full.num;
				cJSON* slots = cJSON_GetObjectItem(mapping_reject, "slots");
				(msg -> data).reject.mapping.full.slots = (int*)malloc(num * sizeof(int));
				int i = 0;
				for(;i < num;i++)
					(msg -> data).reject.mapping.full.slots[i] = cJSON_GetArrayItem(slots, i) -> valueint;
			}else
				//light mode
				(msg -> data).reject.mapping.light.slot = cJSON_GetObjectItem(mapping_reject, "slot") -> valueint;
			break;
		default:
			(msg -> data).exception.dummy = NULL;
			break;
	}
	cJSON_Delete(json_response);
	return msg;
}

static char* dumpMessage(struct Message* msg){
	if(msg == NULL || msg -> uuid == NULL)
		return NULL;
	cJSON* json_msg = cJSON_CreateObject();
	cJSON* uuid = cJSON_CreateString(msg -> uuid);
	cJSON* type = cJSON_CreateNumber(msg -> type);
	cJSON* data = cJSON_CreateObject();
	switch(msg -> type){
		case SYNC:
			dummy();
			cJSON* begin_sync = cJSON_CreateString((msg -> data).sync.begin);
			cJSON* end_sync = cJSON_CreateString((msg -> data).sync.end);
			cJSON* messages = cJSON_CreateArray();
			int len = sizeof((msg -> data).sync.messages)/sizeof(struct Message*);
			int i = 0;
			for(;i < len;i++){
				char* message = dumpMessage((msg -> data).sync.messages[i]);
				cJSON* json_message = cJSON_CreateString(message);
				cJSON_AddItemToArray(messages, json_message);
				free(message);
			}
			cJSON_AddItemToObject(data, "begin", begin_sync);
			cJSON_AddItemToObject(data, "end", end_sync);
			cJSON_AddItemToObject(data, "messages", messages);
			break;
		case RECOVER:
			dummy();
			cJSON* begin_recover = cJSON_CreateString((msg -> data).recover.begin);
			cJSON_AddItemToObject(data, "begin", begin_recover);
			break;
		case FAIL:
			dummy();
			cJSON* commit_fail = cJSON_CreateNumber((msg -> data).fail.commit);
			cJSON* ip = cJSON_CreateString((msg -> data).fail.ip);
			cJSON* port = cJSON_CreateNumber((msg -> data).fail.port);
			cJSON_AddItemToObject(data, "commit", commit_fail);
			cJSON_AddItemToObject(data, "ip", ip);
			cJSON_AddItemToObject(data, "port", port);
			break;
		case MOVE:
			dummy();
			cJSON* request = cJSON_CreateString((msg -> data).move.request);
			cJSON_AddItemToObject(data, "request", request);
			break;
		case DECLARE:
			dummy();
			cJSON* commit_declare = cJSON_CreateNumber((msg -> data).declare.commit);
			cJSON* switcher_declare = cJSON_CreateNumber((msg -> data).declare.switcher);
			cJSON* mapping = cJSON_CreateObject();
			if((msg -> data).declare.switcher){
				//full mode
				cJSON* num = cJSON_CreateNumber((msg -> data).declare.mapping.full.num);
				cJSON* slots = cJSON_CreateArray();
				int i = 0;
				int len = (msg -> data).declare.mapping.full.num;
				for(;i < len;i++){
					cJSON* slot = cJSON_CreateNumber((msg -> data).declare.mapping.full.slots[i]);
					cJSON_AddItemToArray(slots, slot);
				}
				cJSON_AddItemToObject(mapping, "num", num);
				cJSON_AddItemToObject(mapping, "slots", slots);
			}else{
				//light mode
				cJSON* slot = cJSON_CreateNumber((msg -> data).declare.mapping.light.slot);
				cJSON_AddItemToObject(mapping, "slot", slot);
			}
			cJSON_AddItemToObject(data, "commit", commit_declare);
			cJSON_AddItemToObject(data, "switcher", switcher_declare);
			cJSON_AddItemToObject(data, "mapping", mapping);
			break;
		case REJECT:
			dummy();
			cJSON* switcher_reject = cJSON_CreateNumber((msg -> data).reject.switcher);
			cJSON* mapping_reject = cJSON_CreateObject();
			if((msg -> data).reject.switcher){
				//full mode
				cJSON* num = cJSON_CreateNumber((msg -> data).reject.mapping.full.num);
				cJSON* slots = cJSON_CreateArray();
				int i = 0;
				int len = (msg -> data).reject.mapping.full.num;
				for(;i < len;i++){
					cJSON* slot = cJSON_CreateNumber((msg -> data).reject.mapping.full.slots[i]);
					cJSON_AddItemToArray(slots, slot);
				}
				cJSON_AddItemToObject(mapping_reject, "num", num);
				cJSON_AddItemToObject(mapping_reject, "slots", slots);
			}else{
				//light mode
				cJSON* slot = cJSON_CreateNumber((msg -> data).reject.mapping.light.slot);
				cJSON_AddItemToObject(mapping_reject, "slot", slot);
			}
			cJSON_AddItemToObject(data, "switcher", switcher_reject);
			cJSON_AddItemToObject(data, "mapping", mapping_reject);
			break;
		default:
			break;
	}
	cJSON_AddItemToObject(json_msg, "uuid", uuid);
	cJSON_AddItemToObject(json_msg, "type", type);
	cJSON_AddItemToObject(json_msg, "data", data);
	char* request = cJSON_PrintUnformatted(json_msg);
	cJSON_Delete(json_msg);
	return request;
}

static void deleteMessage(struct Message* msg){
	if(msg == NULL)
		return;
	if(msg -> uuid)
		free(msg -> uuid);
	int type = msg -> type;
	switch(type){
		case SYNC:
			free((msg -> data).sync.begin);
			free((msg -> data).sync.end);
			int len = sizeof((msg -> data).sync.messages)/sizeof(struct Message*);
			int i = 0;
			for(;i < len;i++)
				free((msg -> data).sync.messages[i]);
			free((msg -> data).sync.messages);
			break;
		case RECOVER:
			free((msg -> data).recover.begin);
			break;
		case FAIL:
			free((msg -> data).fail.ip);
			break;
		case MOVE:
			free((msg -> data).move.request);
			break;
		case DECLARE:
			dummy();
			int switcher_declare = (msg -> data).declare.switcher;
			if(switcher_declare)
				//only full mode needs free
				free((msg -> data).declare.mapping.full.slots);
			break;
		case REJECT:
			dummy();
			int switcher_reject = (msg -> data).reject.switcher;
			if(switcher_reject)
				free((msg -> data).reject.mapping.full.slots);
			break;
		default:
			break;
	}
	free(msg);
	msg = NULL;
}

static void* send_cycle(void* ptr){
	Cluster* cluster = (Cluster*)ptr;
	
}
static void* recv_cycle(void* ptr){
	Cluster* cluster = (Cluster*)ptr;
	
}
static void dummy(){}

void set_boot(){
	boot = 1;
}