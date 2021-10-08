/**
 * @file C/include/utils/bits.h
 * @brief      some useful bit-related methods
 * @version    0.0.2
 * @author     Ji Xiangyu
 * @date       2021.10.6
 */
#include "lib.h"

#define UUID_BELOW -1
#define UUID_EQUAL 0
#define UUID_GREATER 1
#define UUID_LEN_ERROR 2
#define UUID_FORMAT_ERROR 3

int uuidcmp(char*, char*);
