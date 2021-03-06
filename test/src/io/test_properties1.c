//basic test
#include "properties.h"
#include "test_common.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

int main(){
	Log("properties test 1: basic test");
	Properties* properties = readPropertiesFromFile("./../../../../test/static/io/t1.properties");
	assert(properties != NULL);
	char** keys = (char**)malloc(10*sizeof(char*));
	int i = 0;
	for(;i < 10;i++)
		keys[i] = (char*)malloc(100);
	int len = getPropertiesKeys(properties, keys);
	assert(len == 4);
	for(i = 0;i < 10;i++)
		free(keys[i]);
	free(keys);
	int emptykeys = getPropertiesKeys(NULL, NULL);
	assert(emptykeys == 0);
	char* empty = getPropertiesConf(properties, "key5");
	assert(empty == NULL);
	char* nptr = getPropertiesConf(properties, NULL);
	assert(nptr == NULL);
	char* nproperties = getPropertiesConf(NULL, "key4");
	assert(nproperties == NULL);
	char* value1 = getPropertiesConf(properties, "key1");
	char* value2 = getPropertiesConf(properties, "key2");
	char* value3 = getPropertiesConf(properties, "key3");
	char* value4 = getPropertiesConf(properties, "key4");
	assert(value1 != NULL);
	assert(value2 != NULL);
	assert(value3 != NULL);
	assert(value4 != NULL);
	assert(strcmp(value1, "value1") == 0);
	assert(strcmp(value2, "value2") == 0);
	assert(strcmp(value3, "value3") == 0);
	assert(strcmp(value4, "value4") == 0);
	free(value1);
	free(value2);
	free(value3);
	free(value4);
	deleteProperties(properties);
	deleteProperties(NULL);
	Log("Properties test 1: passed");
	return 0;
}