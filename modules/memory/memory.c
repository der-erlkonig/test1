/**
 * @file modules/memory/memory.c
 * @brief      This file implements memory pool.
 * @version    0.0.2
 * @author     Ji Xiangyu
 * @date       2021.10.15
 */
#include "memory/memory.h"
#include <pthread.h>

static Memory_Pool pool = NULL;
static Memory_Block next = NULL;
static unsigned char signal = 0;//1 - lock, 0 - unlock, only used to init lock
static pthread_mutex_t lock;

static void init_pool(void);
static void collect_pool(void);

void *__wrap_malloc(size_t size){
    if(pool == NULL)
        init_pool();

    void* ptr = NULL;
    int p = 0;

    pthread_mutex_lock(&lock);
    while(p < DEFAULT_POOL_SIZE && next[p] < size){
        if(next[p] < 0)
            p = (-1) * next[p];
        else
            p += next[p];
    }

    if(p == DEFAULT_POOL_SIZE)
        return NULL;

    int remain = p + size;
    ptr = pool + p;
    int origin = next[p];
    next[p] = (-1) * next[remain];

    if(size != origin)
        next[remain] = next[p] - size;
    pthread_mutex_unlock(&lock);
	return ptr;
}

void __wrap_free(void* ptr){
    int location = ptr - pool;
    //not our pool
    if(location < 0 || location >= DEFAULT_POOL_SIZE)
        return;
    pthread_mutex_lock(&lock);
    //not header or hanging pointer
    if(next[location] >= 0)
        return;
    int end = (-1) * next[location] - 1;
    int length = end - location + 1;
    memset(next + location, 0, length);
    next[location] = length;
    int p = 0;
    while(p < DEFAULT_POOL_SIZE && next[p] > 0 && p + next[p] == location){
        if(next[p] < 0)
            p = (-1) * next[p];
        else
            p += next[p];
    }
    if(p == DEFAULT_POOL_SIZE)
        return;
    //merge
    next[p] += length;
    next[location] = 0;
    pthread_mutex_unlock(&lock);
}

static void init_pool(){

    //first lock
    asm volatile("movb %1, %%al\n\t \
                  xchg %%al, %0\n\t"
                  :"=r"(signal)
                  :"i"(1)
                  :"%al");

    if(signal)
        return;
    pool = (Memory_Pool)__real_malloc(DEFAULT_POOL_SIZE);
    next = (Memory_Block)__real_malloc(DEFAULT_POOL_SIZE);
    memset(pool, 0, DEFAULT_POOL_SIZE);
    memset(next, 0, DEFAULT_POOL_SIZE);
    next[0] = DEFAULT_POOL_SIZE;
    pthread_mutex_init(&lock, NULL);
}

static void collect_pool(){
    if(pool == NULL)
        return;
    __real_free(pool);
    __real_free(next);
}
