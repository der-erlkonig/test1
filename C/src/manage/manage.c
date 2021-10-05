#include "manage/manage.h"

static Message* parseMessage(char*);
static char* dumpMessage(Message*);


static Message* parseMessage(char* response){
	Message* msg = (Message*)malloc(sizeof(Message));
	cJSON* json_response = cJSON_Parse(response);
	cJSON_GetObjectItem(json_response, "timestamp");
	
}

static char* dumpMessage(Message* msg);