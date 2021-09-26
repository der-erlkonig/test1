/**
 * @file C/include/device/pool.h
 * @brief      This file defines camera management.
 * @version    0.0.2
 * @author     Ji Xiangyu
 * @date       2021.9.25
 */
#include "common.h"
#include <pthread.h>

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

typedef struct{
    char* xaddr;
    int catelogy;
    int state;
    int disconnection;
} Camera;

typedef struct{
    uint64_t timestamp;
    Camera* cameras;
    int size;
    int main_num;
    int backup_num;
    pthread_mutex_t lock;
    int max_timeout;
    int heart;
} CaremaPool;

CaremaPool* createCameraPool(int main_num, int backup_num);
void heartbeat(CaremaPool*);
void stopHeartbeat(CaremaPool*);