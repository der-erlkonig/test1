//basic test
#include "properties.h"
#include <assert.h>

int main(){
	Properties* properties = readFromFile("../../../../../../../test/static/io/t1.properties");
	assert(properties != NULL);
	deleteProperties(properties);
	return 0;
}