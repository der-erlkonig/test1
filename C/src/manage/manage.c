/**
 * @file C/src/manage/manage.c
 * @brief      implementation of cluster management.
 * @version    0.0.2
 * @author     Ji Xiangyu
 * @date       2021.10.6
 */
#include "manage/manage.h"

static Message* parseMessage(char*);
static char* dumpMessage(Message*);


static Message* parseMessage(char* response){
	Message* msg = (Message*)malloc(sizeof(Message));
	cJSON* json_response = cJSON_Parse(response);
	cJSON_GetObjectItem(json_response, "timestamp");
	
}

static char* dumpMessage(Message* msg){
	
}