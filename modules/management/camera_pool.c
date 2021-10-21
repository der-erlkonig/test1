/*
 * @file modules/management/camera_pool.c
 * @brief      This file implements camera pool.
 * @version    0.0.2
 * @author     Ji Xiangyu & Jiao Hongtong
 * @date       2021.9.26
 */
#include "management/camera_pool.h"

static void update_cameras(CameraPool*);
// static void update_cameras_exec(CameraPool*,char**,int);
// static void resize(CameraPool*,int);
// static void toBigCapital(CameraPool*);
// static Camera createCamera(char*);

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

/*
static Camera createCamera(char* xaddr){
    Camera camera;
    camera.xaddr = xaddr;
    camera.catelogy = MAIN;
    camera.state = RUNNING;
    camera.disconnection = 0;
    return camera;
}
*/

/**
* @brief move cameras from old array to new array 
* @param [Camera*]oldItems: old cameras to be moved;
* @param [Camera*]newItems: new cameras to be moved into;
* @param [int]endIndex: number of cameras to be moved;
*/
/*
void copyItemFromOld(Camera *oldItems, Camera *newItems, int endIndex){
    for (int i = 0; i < endIndex; i++) {
        newItems[i] = oldItems[i];
    }
}
*/
/**
* @brief add new cameras into the camerapool
* @param[CameraPool*] pool:camera pool
* @param[Camera] newCamera:new camera to be added
*/
/*
void addCamera(CameraPool* pool,Camera newCamera){
    int size = pool -> size;
    if(size + 1 > pool -> capital *3/4){
        toBigCapital(pool);
    }
    pool->cameras[size] = newCamera;
    pool->size++;
}
*/

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

/**
static void toBigPool(CameraPool* pool){
    int newCapital = (int)pool -> capital *3/2;
    resize(pool,newCapital);

}

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
static void update_cameras_exec(CameraPool* pool,char** xaddr,int camera_number){
    Camera* cameras = pool -> cameras;
    if(cameras == NULL){
        for(int i = 0;i < camera_number;i++){
            if(i < pool -> main_num + pool -> backup_num){
                Camera newCamera = createCamera(xaddr[i]);
                if(i >= pool -> main_num){
                    newCamera.catelogy = BACKUP;
                    newCamera.state = WAITING;
                }
                pthread_mutex_lock(&(pool->lock));
                addCamera(pool,newCamera);
                pthread_mutex_unlock(&(pool->lock));
            }
            else{
                break;
            }
        }
    }
*/
    // else{
        // int D_value_to_main = 0; /*the D_value between current_main and pool->main;>=0*/
        // int D_value_to_backup = 0; /*the D_value between current_backup and pool->backup;>=0*/
        // int surplus_main = 0; /*the num of surplus main cameras*/
        // int surplus_backup = 0; /*the num of surplus backup cameras*/
        // int current_disconnected = 0 /*the current number of disconnected main cameras;*/
        // int current_main = 0; /*the current number of main cameras;*/
        // int current_backup = 0; /*the current number of backup cameras;*/
/*        
        for(int i = 0;i < pool -> size;i++){
            switch (cameras[i].catelogy)
            {
            case MAIN:
                current_main++;
                pthread_mutex_lock(&(pool->lock));
                if(cameras[i].state == DISCONNECTED){
                    current_disconnected++;
                }
                pthread_mutex_unlock(&(pool->lock));
                break;
            case BACKUP:
                current_backup++;
                break;
            default:
                break;
            }
            
        }
        size = pool->size;
        bool* isCovered = (bool*)malloc(size*sizeof(bool));
        memset(isCovered,false,size);
*/
        // for(int i = 0;i < camera_number;i++){
            // int flag = 0; /*the signal for whether detected camera is recorded or not;*/
            // for(int j = 0;j < pool -> size;j++){
                // if(xaddr[i]==cameras[j].xaddr){
                    // pthread_mutex_lock(&(pool->lock));
                    // cameras[j].disconnection = 0;
                    // flag = 1;
                    // isCovered[j] = true;
                    // if(current_main >= pool->main_num){
                        // surplus_main++;
                    // }
                    // cameras[j].catelogy = MAIN;
                    // cameras[j].state = RUNNING;
                    // pthread_mutex_unlock(&(pool->lock));
                    // current_main++;
                    // break;
                // }
            // }
            // if(!flag){
                // if(current_main >= pool->main_num){
                    // surplus_main++;
                // }
                // newCamera = createCamera(xaddr[i]);
                // pthread_mutex_lock(&(pool->lock));
                // addCamera(pool,newCamera);
                // pthread_mutex_unlock(&(pool->lock));
                // current_main++;
            // }
        // }
/*
         for(int i = 0;i < size;i++){
            if(!isCovered[i]){
                cameras[i].disconnection++;
                if(cameras[i].disconnection >= pool->max_timeout){
                    pthread_mutex_lock(&(pool->lock));
                    cameras[i].catelogy = UNUSED;
                    cameras[i].state = DISCONNECTED;
                    current_backup--;
                    if(surplus_backup > 0){
                        surplus_backup--;
                    }
                    pthread_mutex_unlock(&(pool->lock));
                    continue;
                }
                switch (cameras[i].catelogy)
                {
                case MAIN:
                    if(current_backup >= pool->backup_num){
                        surplus_backup++;
                    }
                    if(surplus_main > 0){
                        surplus_main--;
                    }
                    pthread_mutex_lock(&(pool->lock));
                    cameras[i].catelogy = BACKUP;
                    cameras[i].state = WAITING;
                    pthread_mutex_unlock(&(pool->lock));
                    current_backup++;
                    current_main--;
                    break;

                default:
                    break;
                }
            }
        }
        if(pool->main_num > current_main){
            D_value_to_main = pool->main_num - current_main;
        }
        if(D_value_to_main){
            for(int i = 0;i < pool->size && D_value_to_main > 0;i++){
                if(cameras[i].catelogy == BACKUP){
                    pthread_mutex_lock(&(pool->lock));
                    cameras[i].catelogy = MAIN;
                    cameras[i].state = RUNNING;
                    pthread_mutex_unlock(&(pool->lock));
                    current_backup--;
                    current_main++;
                    D_value_to_main--;
                }
            }
        }

        if(surplus_main){
            for(int i = 0;i < pool->size && surplus_main > 0 && current_disconnected > 0;i++){
                if(cameras[i].catelogy == MAIN && cameras[i].state == DISCONNECTED){
                    pthread_mutex_lock(&(pool->lock));
                    cameras[i].catelogy = UNUSED;
                    pthread_mutex_unlock(&(pool->lock));
                    surplus_main--;
                    current_disconnected--;
                }
            }
            int iter = 0;
            while(surplus_main){
                
                if(cameras[iter].catelogy == MAIN){
                    if(current_backup >= pool->backup_num){
                        surplus_backup++;
                    }
                    pthread_mutex_lock(&(pool->lock));
                    cameras[iter].catelogy = BACKUP;
                    cameras[iter].state = WAITING;
                    pthread_mutex_unlock(&(pool->lock));
                    surplus_main--;
                    current_backup++;
                }
                iter++;
            }
        }

        if(surplus_backup){
            for(int i = 0;i < pool->size && surplus_backup > 0;i++){
                if(cameras[i].catelogy == BACKUP){
                    pthread_mutex_lock(&(pool->lock));
                    cameras[i].catelogy = UNUSED;
                    cameras[i].catelogy = DISCONNECTED;
                    pthread_mutex_unlock(&(pool->lock));
                    current_backup--;
                    surplus_backup--;
                }
            }
        }



        
    }
    pthread_mutex_lock(&(pool->lock));
    pool->timestamp++;
    pthread_mutex_unlock(&(pool->lock));

}
static void update_cameras(CameraPool* pool){
    while(pool -> heart){
        char** xaddr = (char**)malloc(10000*sizeof(char*));
        int camera_number = detect_device(xaddr);
        pthread_t mythread;
        int res = pthread_create(&mythread,__detachstate,&update_cameras_exec,&pool,&xaddr,&camera_number);





    }



}
*/