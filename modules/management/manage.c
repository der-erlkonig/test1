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
			void* request;
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
	pthread_t send;/*!< sending thread */
	pthread_t recv;/*!< receiving thread */
    int cluster_size;/*!< cluster size */
	int capacity;/*!< maximum of threads which host can be held */
	uint64_t* thread_mapping;/*!< mapping between cameras' addresses and host's thread */
	int running_threads;/*!< current running thread */
} Cluster;

static int boot = 0;

static struct Message* parseMessage(char*);
static char* dumpMessage(struct Message*);
static void deleteMessage(struct Message*);
static void send_cycle(Cluster*);
static void recv_cycle(Cluster*);

static struct Message* parseMessage(char* response){
	struct Message* msg = (struct Message*)malloc(sizeof(struct Message));
	cJSON* json_response = cJSON_Parse(response);
	msg -> uuid = (char*)malloc(STR_MAX);
	strcpy(msg -> uuid, cJSON_GetObjectItem(json_response, "uuid") -> valuestring);
	int type = cJSON_GetObjectItem(json_response, "type") -> valueint;
	msg -> type = type;
	cJSON* data = cJSON_GetObjectItem(json_response, "data");
	switch(type){
		//TODO: switcher
		case SYNC:
			(msg -> data).sync.begin = (char*)malloc(STR_MAX);
			(msg -> data).sync.end = (char*)malloc(STR_MAX);
			strcpy((msg -> data).sync.begin, cJSON_GetObjectItem(data, "start") -> valuestring);
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
			(msg -> data).move.request = malloc(STR_MAX * STR_MAX);
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
	// if(msg -> uuid == NULL)
	// 	return NULL;
	// cJSON* json_msg = cJSON_CreateObject();
	// cJSON* uuid = cJSON_CreateString(msg -> uuid);
	// cJSON_AddItemToObject(json_msg, "timestamp", uuid);
	// cJSON* reset = cJSON_CreateNumber(msg -> reset);
	// cJSON_AddItemToObject(json_msg, "reset", reset);
	// cJSON* category = cJSON_CreateNumber(msg -> category);
	// cJSON_AddItemToObject(json_msg, "category", category);
	// int num = msg -> n;
	// cJSON* number = cJSON_CreateNumber(num);
	// cJSON_AddItemToObject(json_msg, "number", number);
	// if(num != 0){
	// 	cJSON* cameras = cJSON_CreateArray();
	// 	int i;
	// 	for(i = 0;i < num;i++){
	// 		cJSON* state = cJSON_CreateObject();
	// 		cJSON* xaddr = cJSON_CreateString((msg -> value)[i].xaddr);
	// 		cJSON_AddItemToObject(state, "xaddr", xaddr);
	// 		cJSON* pan = cJSON_CreateNumber((msg -> value)[i].pan);
	// 		cJSON_AddItemToObject(state, "pan", pan);
	// 		cJSON* tilt = cJSON_CreateNumber((msg -> value)[i].tilt);
	// 		cJSON_AddItemToObject(state, "tilt", tilt);
	// 		cJSON* zoom = cJSON_CreateNumber((msg -> value)[i].zoom);
	// 		cJSON_AddItemToObject(state, "zoom", zoom);
	// 		cJSON* running = cJSON_CreateNumber((msg -> value)[i].running);
	// 		cJSON_AddItemToObject(state, "running", running);
	// 		cJSON_AddItemToArray(cameras, state);
	// 	}
	// 	cJSON_AddItemToObject(json_msg, "value", cameras);
	// }
	// char* request = cJSON_PrintUnformatted(json_msg);
	// cJSON_Delete(json_msg);
	// return request;
	return NULL;
}

static void deleteMessage(struct Message* msg){
	// if(msg == NULL)
	// 	return;
	// if(msg -> value != NULL){
	// 	int n = msg -> n;
	// 	int j = 0;
	// 	for(;j < n;j++)
	// 		if((msg -> value)[j].xaddr != NULL)
	// 			free((msg -> value)[j].xaddr);
	// 	free(msg -> value);
	// }
	// free(msg -> uuid);
	// free(msg);
	// msg = NULL;
}

static void send_cycle(Cluster* cluster){

}
static void recv_cycle(Cluster* cluster){

}

void set_boot(){
	boot = 1;
}