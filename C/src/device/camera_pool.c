/**
 * @file C/src/device/camera_pool.c
 * @brief      This file implements camera pool.
 * @version    0.0.2
 * @author     Ji Xiangyu & Jiao Hongtong
 * @date       2021.9.26
 */
#include "device/camera_pool.h"

static void update_cameras(CameraPool*);
static void update_cameras_exec(CameraPool*);
static void resize(CameraPool*,int);
static void toBigCapital(CameraPool*);

/**
 * @brief      Creates a camera pool.
 * @param[int]  main_num:The main camera number.
 * @param[int]  backup_num:The backup camera number.
 * @param[int]  max_timeout:The maximum times of disconnection.
 * @return     CameraPool* Camera pool
 */
CameraPool* createCameraPool(int main_num, int backup_num, int max_timeout){
    CameraPool* pool = (CameraPool*)malloc(sizeof(CameraPool));
    pool -> timestamp = 0;
    pool -> main_num = main_num;
    pool -> backup_num = backup_num;
    pool -> capital = main_num + backup_num;
    pool -> size = 0;
    pthread_mutex_init(&(pool -> lock), NULL);
    pool -> max_timeout = max_timeout;
    return pool;
}

/**
* @brief 
* @param[char*] xaddr:working address of each camera
* @return Camera* camera
*/
Camera* createCamera(char* xaddr){
    Camera* camera = (Camera*)malloc(sizeof(Camera));
    camera->xaddr = xaddr;
    camera->catelogy = MAIN;
    camera->state = RUNNING;
    camera->disconnection = 0;
    return camera;
}
/**
* @brief 
* @param[char*] xaddr:working address of each camera
* @return Camera* camera
*/
static void copyItemFromOld(Camera *oldItems, Camera *newItems, int endIndex) {
    for (int i = 0; i < endIndex; i++) {
        newItems[i] = oldItems[i];
    }
}

/**
* @brief add the capital of camerapool 
* @param[CaremaPool*] pool:The camera pool
*/
static void toBigPool(CameraPool* pool){
    int oldCapital = pool -> capital;
    int newCapital = (int)pool -> capital *3/2;
    resize(pool,newCapital);

}
/**
* @brief change the camera pool's size to newsize 
* @param[CaremaPool*] pool:The camera pool;newCapital:The new size
*/
static void resize(CameraPool* pool,int newCapital){
    if(newCapital <= 0){
        return ;
    }
    Camera* newCameras = (Camera*)malloc(newCapital * sizeof(Camera));
    Camera* oldCameras = pool -> cameras;
    copyItemFromOld(oldCameras,newCameras,pool->size -1);
    free(pool->cameras);
    pool -> cameras = NULL;
    pool -> cameras = newCameras;
    pool -> capital = newCapital;

}
/**
 * @brief      start heartbeat request
 * @param[CaremaPool*]      pool:The camera pool
 */
void heartbeat(CameraPool* pool){
    pool -> heart = 1;
    update_cameras(pool);
}

/**
 * @brief      stop heartbeat request
 * @param[CaremaPool*]      pool:The camera pool
 */
void stopHeartbeat(CameraPool* pool){
    pool -> heart = 0;
}


//static methods
static void update_cameras(CameraPool* pool){

}