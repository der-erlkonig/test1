#include "manage/manage.h"

static Message* parseMessage(char*);
static char* dumpMessage(Message*);

/**
 * @par Message Format
 *      stanard json format
 */
static Message* parseMessage(char* response){
	Message* msg = (Message*)malloc(sizeof(Message));
	cJSON* json_response = cJSON_Parse(response);
	
	
}

static char* dumpMessage(Message* msg);