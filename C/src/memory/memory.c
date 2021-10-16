/**
 * @file C/src/memory/memory.c
 * @brief      This file implements memory pool.
 * @version    0.0.2
 * @author     Ji Xiangyu
 * @date       2021.10.15
 */
#include "memory/memory.h"
#include <pthread.h>

static Memory_Pool pool = NULL;
static Memory_State state = NULL;
static Block_Table blocks = NULL;
static int signal = 0;//1 - lock, 0 - unlock, only used to init lock
static pthread_mutex_t lock;

static void init_pool(int);
static void collect_pool();
/**
 * @brief      wrap standard malloc method
 * @param[size_t]  size:The requested size
 * @return     pointer of allocated memory, NULL if fail.
 * @retval     void* memory
 */
void *__wrap_malloc(size_t size){
	void* ptr = __real_malloc(size);
	return ptr;
}
/**
 * @brief      wrap standard free method
 * @param[void*]      ptr:The pointer that points to memory to be collected
 */
void __wrap_free(void* ptr){
	__real_free(ptr);
}

static void init_pool(int size){
    //first lock
    asm volatile("movl %0, %%rax\n\t \
                  xchg %%rax, %1\n\t"
                  :"=r"(signal)
                  :"i"(1)
                  :"%rax");

    if(signal || pool != NULL)
        return;
    if(size != 0){
        pool = (Memory_Pool)__real_malloc(size);
        state = (Memory_State)__real_malloc(size);
    }
    else{
        pool = (Memory_Pool)__real_malloc(DEFAULT_POOL_SIZE);
        state = (Memory_State)__real_malloc(DEFAULT_POOL_SIZE);
    }
    pthread_mutex_init(&lock, NULL);
}

static void collect_pool(){
    if(pool == NULL)
        return;
    __real_free(pool);
    __real_free(state);
}