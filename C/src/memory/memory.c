/**
 * @file C/src/memory/memory.c
 * @brief      This file implements memory pool.
 * @version    0.0.2
 * @author     Ji Xiangyu
 * @date       2021.10.15
 */
#include "memory/memory.h"
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