/**
 * @file C/include/device/pool.h
 * @brief      This file defines camera pool.
 * @version    0.0.2
 * @author     Ji Xiangyu
 * @date       2021.9.25
 */
#include "common.h"
#include <pthread.h>

/**
 * @defgroup   Camera_Pool
 * @brief      camera pool for camera cluster
 * @{
 */
/**
 * @defgroup   Camera_Pool_State
 * @brief      camera's state and status
 * @{
 */
/**
 * @enum
 * @brief      camera's catelogy
 */
enum{
    MAIN=0,/*!< main camera, used at first */
    BACKUP=1,/*!< backup camera, used when main camera does not work */
    UNUSED=2/*!< unused camera, usually not assigned to a main camera */
};

/**
 * @enum 
 * @brief      camera's state
 */
enum{
    RUNNING=128,/*!< running, camera works smoothly */
    WAITING=129,/*!< waiting, camera is on the air but not used now */
    DISCONNECTED=130/*!< disconnected, host cannot make sure if the camera keeps alive */
};
/**
 * @}
 */
/**
 * @defgroup   Camera_Pool_Type
 * @brief      definition of type
 * @{
 */
/**
 * @typedef Camera
 * @struct Camera
 * @brief      wrapper of physical camera
 */
typedef struct{
    char* xaddr;/*!< camera's media service address */
    int catelogy;/*!< camera's status */
    int state;/*!< camera's state */
    int disconnection;/*!< camera's times of disconnection */
} Camera;

/**
 * @typedef CameraPool
 * @struct CameraPool
 * @brief  definition of camera pool    
 */
typedef struct{
    uint64_t timestamp;/*!< detection timeout */
    Camera* cameras;/*!< cameras array */
    int size;/*!< cameras number */
    int main_num;/*!< main cameras number */
    int backup_num;/*!< backup cameras number */
    pthread_mutex_t lock;/*!< thread lock */
    int max_timeout;/*!< maximum acceptable times of disconnection */
    int heart;/*!< weather to use heartbeat */
} CameraPool;
/**
 * @}
 */

/**
 * @defgroup   Camera_Pool_Exported_Methods
 * @brief      exported methods of camera pool
 * @{
 */
CameraPool* createCameraPool(int, int, int);
void heartbeat(CameraPool*);
void stopHeartbeat(CameraPool*);
/**
 * @}
 */
/**
 * @}
 */
