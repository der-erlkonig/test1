/**
 * @file C/include/manage/manage.h
 * @brief      host cluster management.
 * @version    0.0.2
 * @author     Ji Xiangyu
 * @date       2021.10.5
 */
#pragma once
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
#define STR_MAX 100/*!< unified max length of string */
/**
 * @enum request category
 * @brief      identifiers of request type
 */
enum{
	DIFF = 0,/*!< difference notification, in which the message only contains the difference bewteen the last message, the most regular type */
	RESCOVERY = 1,/*!< rescovery mode, in which the message will contains all camera's state, often used to reply recovery request */
	REQUEST=2,/*!< request mode, in which the rest of the message is empty(or default value), represented that the host requests recovery */
    PROBE=3,/*!< probe mode, when one host notifies other host that it is online*/
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
        struct{
            int n;/*!< utility for assignment/load, recommend not to use it directly */
            PTZ_State* value;/*!< utility for assignment/load, recommend not to use it directly */
        };
	};/*!< message body */
} Message;
/**
 * @}
 */

/**
 * @struct Host
 * @typedef Host
 * @brief  host image of current computer
 */
typedef struct{
	pthread_t send;/*!< sending thread */
	pthread_t recv;/*!< receiving thread */
    int cluster_size;/*!< cluster size */
	int capacity;/*!< maximum of threads which host can be held */
	uint64_t* thread_mapping;/*!< mapping between cameras' addresses and host's thread */
	int running_threads;/*!< current running thread */
} Host;

/**
 * @typedef Cluster
 * @brief   cluster entity
 */
typedef Host* Cluster;



/**
 * @}
 */

/**
 * @defgroup   Cluster_Exported_Methods
 * @brief      exported cluster methods
 * @{
 */
/**
 * @}
 */

/**
 * @}
 */