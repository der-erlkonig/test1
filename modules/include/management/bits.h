/**
 * @file modules/include/management/bits.h
 * @brief      some useful bit-related methods
 * @version    0.0.2
 * @author     Ji Xiangyu
 * @date       2021.10.6
 */
#pragma once
#include "onvif_lib.h"

#define UUID_BELOW -1 /*!< uuid correct, and uuid1 is lower than uuid2 */
#define UUID_EQUAL 0 /*!< uuid correct, and uuid1 is equal to uuid2 */
#define UUID_GREATER 1 /*!< uuid correct, and uuid1 is greater than uuid2 */
#define UUID_LEN_ERROR 2 /*!< uuid wrong, caused by incorrect length */
#define UUID_FORMAT_ERROR 3 /*!< uuid wrong, caused by incorrect format such as wrong or misplaced delimiter, not decimal-compatible number(hexcimal, etc.), and so on*/

/**
 * @brief      compare uuid
 * @param[in]  u1 The first uuid
 * @param[in]  u2 The second uuid
 * @return     result code, whose meaning can be referred to definition.
 */
int uuidcmp(char* u1, char* u2);

/**
 * @brief      compute hash of given string, range 0 to 2^64-2
 * @param[in]  str The string
 * @return     hash value, 2^64-1(aka -1) if string is NULL
 * @retval     uint64_t hash value
 */
uint64_t hash(char* str);