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
	DIFF = 0,/*!< difference notification mode, in which the message only contains the difference bewteen the last message, the most regular type */
	RESCOVERY = 1,/*!< rescovery mode, in which the message will contains all camera's state, often used to reply recovery request */
	REQUEST=2,/*!< request mode, in which the rest of the message is empty(or default value), represented that the host requests recovery */
    PROBE=3,/*!< probe mode, when one host notifies other hosts that it is online and probe other hosts*/
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
};

typedef struct Host{
	pthread_t send;/*!< sending thread */
	pthread_t recv;/*!< receiving thread */
    int cluster_size;/*!< cluster size */
	int capacity;/*!< maximum of threads which host can be held */
	uint64_t* thread_mapping;/*!< mapping between cameras' addresses and host's thread */
	int running_threads;/*!< current running thread */
} Cluster;

static boot = 0;

static struct Message* parseMessage(char*);
static char* dumpMessage(struct Message*);
static void deleteMessage(struct Message*);
static void send_cycle(Cluster*);
static void recv_cycle(Cluster*);

//TODO:need to be rewrite
static struct Message* parseMessage(char* response){
	// Message* msg = (Message*)malloc(sizeof(Message));
	// cJSON* json_response = cJSON_Parse(response);
	// msg -> uuid = (char*)malloc(STR_MAX);
	// strcpy(msg -> uuid, cJSON_GetObjectItem(json_response, "timestamp") -> valuestring);
	// msg -> reset = cJSON_GetObjectItem(json_response, "reset") -> valueint;
	// msg -> category = cJSON_GetObjectItem(json_response, "category") -> valueint;
	// int number = cJSON_GetObjectItem(json_response, "number") -> valueint;
	// msg -> n = number;
	// if(number == 0){
	// 	msg -> value = NULL;
	// 	return msg;
	// }
	// cJSON* cameras = cJSON_GetObjectItem(json_response, "value");
	// PTZ_State* values = (PTZ_State*)malloc(number * sizeof(PTZ_State));
	// msg -> value = values;
	// int i = 0;
	// for(;i < number;i++){
	// 	cJSON* state = cJSON_GetArrayItem(cameras, i);
	// 	values[i].xaddr = (char*)malloc(STR_MAX);
	// 	strcpy(values[i].xaddr, cJSON_GetObjectItem(state, "xaddr") -> valuestring);
	// 	values[i].pan = (float)cJSON_GetObjectItem(state, "pan") -> valuedouble;
	// 	values[i].tilt = (float)cJSON_GetObjectItem(state, "tile") -> valuedouble;
	// 	values[i].zoom = (float)cJSON_GetObjectItem(state, "zoom") -> valuedouble;
	// 	values[i].running = cJSON_GetObjectItem(state, "running") -> valueint;
	// }
	// cJSON_Delete(json_response);
	// return msg;
	return NULL;
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