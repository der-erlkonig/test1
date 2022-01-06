/**
 * @file       include/memory/memory.h
 * @brief      customized memory pool, to improve malloc/free with high frequency
 * @version    0.0.2
 * @author     Ji Xiangyu
 * @date       2021.10.15
 */
#pragma once
#include <stddef.h>
/**
 * @brief      wrap standard malloc method
 * @param[in]  size The requested size
 * @return     pointer of allocated memory, NULL if fail.
 */
void *__wrap_malloc(size_t size);

/**
 * @brief      wrap standard free method
 * @param[void*]      ptr:The pointer that points to memory to be collected
 */
void __wrap_free(void* ptr);

/**
 * @brief      declaration of interposition-needed standard malloc methods
 */
void *__real_malloc(size_t size);
/**
 * @brief      declaration of interposition-needed standard free methods
 */
void __real_free(void* ptr);

#define DEFAULT_POOL_SIZE 5e6/*!< default maximum pool size */