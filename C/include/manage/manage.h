/**
 * @file C/include/manage/manage.h
 * @brief      host cluster management.
 * @version    0.0.2
 * @author     Ji Xiangyu
 * @date       2021.10.5
 */
#include "common.h"
#include "device/camera_pool.h"
#include <pthread.h>

/**
 * @defgroup   Cluster
 * @brief      hosts cluster
 * @{
 */
/**
 * @defgroup   Cluster_type
 * @brief      type of cluster
 * @{
 */
/**
 * @enum request category
 * @brief      identifiers of request type
 */
enum{
	DIFF = 0,/*!< difference notification, in which the message only contains the difference bewteen the last message, the most regular type */
	RESCOVERY = 1,/*!< rescovery mode, in which the message will contains all camera's state, often used to reply recovery request */
	REQUEST=2/*!< request mode, in which the rest of the message is empty(or default value), represented that the host requests recovery. */
};

/**
 * @typedef PTZ_State
 * @struct  PTZ_State
 * @brief   record the current state of ptz camera
 */
typedef struct{
	char* xaddr;/*!< the media service address, used as the unique identifier */
	float pan;/*!< (target/current) pan degree */
	float tilt;/*!< (target/current) tilt degree */
	float zoom;/*!< (target/current) zoom degree */
	int running;/*!< whether the camera is targeting or stand at the given state. */
} PTZ_State;

/**
 * @typedef Message
 * @struct  Message
 * @brief   hosts' heartbeat message structure  
 */
typedef struct{
	char* uuid;/*!< message's unique identifier */
	int reset;/*!< reset flag. When set, the host that receives this message will forget all previous message, and start a new working cycle.Use it to restart.*/
	int category;/*!< message category. Type code has been described before. */
	union{
		struct{
			int modify;/*!< number of modified cameras */
			PTZ_State* modifiers;/*!< modified cameras */
		};/*!< modify-related */
		struct{
			int cameras;/*!< number of all cameras */
			PTZ_State* all_cameras;/*!< all cameras */
		};/*!< all-related */
	};/*!< message body */
} Message;
/**
 * @}
 */

/**
 * @typedef Host
 * @struct Host
 */
typedef struct{
	pthread_t heartbeat;/*!< heartbeat thread */
	int cluster_size;/*!< cluster size */
	int capacity;/*!< maximum of threads which host can be held */
	int* thread_mapping;/*!< mapping between cameras' addresses and host's thread */
	int running_threads;/*!< current running thread */
}Host;

/**
 * @typedef cluster
 * @brief      cluster entity
 */
typedef Host* cluster;



/**
 * @}
 */
/**
 * @}
 */