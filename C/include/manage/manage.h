#include "common.h"
#include <pthread.h>

enum{
	DIFF = 0,
	RESCOVERY = 1
};

typedef struct{
	char* xaddr;
	float pan;
	float tilt;
	float zoom;
} PTZ_State;//TODO

typedef struct{
	uint64_t timestamp;
	int category;
	union{
		struct{
			int insertion;
			PTZ_State* insertion;
			int 
		}
		
	};

} Message;