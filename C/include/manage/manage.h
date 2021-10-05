#include "common.h"
#include "device/camera_pool.h"
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
	int running;
} PTZ_State;

typedef struct{
	uint64_t timestamp;
	int category;
	union{
		struct{
			int modify;
			PTZ_State* modifiers;
		};
		struct{
			int cameras;
			PTZ_State* all_cameras;
		};
	};
} Message;

typedef struct{
	pthread_t heartbeat;
	int cluster_size;
	int capacity;
	int* thread_mapping;
	int running_threads;
}Host;

typedef Host* hosts;