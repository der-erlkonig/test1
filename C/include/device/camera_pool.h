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
enum{
    MAIN=0,
    BACKUP=1,
    UNUSED=2
};

enum{
    RUNNING=128,
    WAITING=129,
    DISCONNECTED=130
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
 * @{
 */
typedef struct{
    char* xaddr;/*!< camera's media service address */
    int catelogy;/*!< camera's status */
    int state;/*!< camera's state */
    int disconnection;/*!< camera's times of disconnection */
} Camera;
/**
 * @}
 */

/**
 * @typedef CameraPool
 * @struct CameraPool
 * @brief  definition of camera pool    
 * @{
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
