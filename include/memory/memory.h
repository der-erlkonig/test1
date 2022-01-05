/**
 * @file       include/memory/memory.h
 * @brief      customized memory pool, to improve malloc/free with high frequency
 * @version    0.0.2
 * @author     Ji Xiangyu
 * @date       2021.10.15
 */
#pragma once
#include <stdlib.h>
#include <string.h>

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

/**
 * @typedef Memory_Pool
 * @brief   pool pointer
 */
typedef void* Memory_Pool;

/**
 * @typedef Memory_Block
 * @brief   record memory block
 * @details We use integer to record which block a byte belongs to.
 *          
 *          When it is negetive, this block is reserved, and this 
 *          byte is the first of this block. The absolute value of 
 *          this number is what the next block's first address.
 *          
 *          When it is positive, this block is free and a requested 
 *          zero page. This byte is the first byte of this block. 
 *          Its value represents the block's length.
 *          
 *          When it is zero, this byte is in the middle of a certain 
 *          block. We need to find a certain footer or header.
 */
typedef int* Memory_Block;

#define DEFAULT_POOL_SIZE 5e6/*!< default maximum pool size */