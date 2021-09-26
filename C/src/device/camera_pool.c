/**
 * @file C/src/device/camera_pool.c
 * @brief      This file implements camera pool.
 * @version    0.0.2
 * @author     Ji Xiangyu
 * @date       2021.9.26
 */
#include "device/pool.h"

static void update_cameras(CaremaPool*);

/**
 * @brief      Creates a camera pool.
 * @param[int]  main_num：The main camera number.
 * @param[int]  backup_num:The backup camera number.
 * @param[int]  max_timeout:The maximum times of disconnection.
 * @return     CameraPool* Camera pool
 */
CaremaPool* createCameraPool(int main_num, int backup_num, int max_timeout){
    CameraPool* pool = (CaremaPool*)malloc(sizeof(CaremaPool));
    pool -> timestamp = 0;
    pool -> main_num = main_num;
    pool -> backup_num = backup_num;
    pthread_mutex_init(&(pool -> lock), NULL);
    pool -> max_timeout = max_timeout;
    pool -> heart = 1;
    update_cameras(pool);
    return pool;
}
/**
 * @brief      start heartbeat request
 * @param[CaremaPool*]      pool:The camera pool
 */
void heartbeat(CaremaPool* pool){
	
}

/**
 * @brief      stop heartbeat request
 * @param[CaremaPool*]      pool:The camera pool
 */
void stopHeartbeat(CaremaPool* pool){

}


//static methods
static void update_cameras(CaremaPool* pool){

}