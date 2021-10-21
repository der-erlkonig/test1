/**
 * @file modules/include/management/bits.h
 * @brief      some useful bit-related methods
 * @version    0.0.2
 * @author     Ji Xiangyu
 * @date       2021.10.6
 */
#pragma once
#include "lib.h"

/**
 * @defgroup   Bits
 * @brief      bits-level ops
 * @{
 */
/**
 * @defgroup   Bits-Constant
 * @brief      Some constant defined by macro
 * @{
 */
#define UUID_BELOW -1 /*!< uuid correct, and uuid1 is lower than uuid2 */
#define UUID_EQUAL 0 /*!< uuid correct, and uuid1 is equal to uuid2 */
#define UUID_GREATER 1 /*!< uuid correct, and uuid1 is greater than uuid2 */
#define UUID_LEN_ERROR 2 /*!< uuid wrong, caused by incorrect length */
#define UUID_FORMAT_ERROR 3 /*!< uuid wrong, caused by incorrect format such as wrong or misplaced delimiter, not decimal-compatible number(hexcimal, etc.), and so on*/

/**
 * @}
 */

/**
 * @defgroup   Bits_Exported_Methods
 * @brief exported methods of bits
 * @{
 */
int uuidcmp(char*, char*);
uint64_t hash(char*);
/**
 * @}
 */

/**
 * @}
 */
