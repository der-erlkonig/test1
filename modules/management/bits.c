/**
 * @file modules/management/bits.c
 * @brief      This file implements bits-level methods.
 * @version    0.0.2
 * @author     Ji Xiangyu
 * @date       2021.10.15
 */
#include "management/bits.h"

/**
 * @def getuuid(str, arr)
 * @brief      try to read decimal numbers from given string to given array
 * @param[char*(awk string reference or pointer)] str:uuid string
 * @param[int*(awk array pointer whose type is compatible to unsigned integer)] arr:array used to store numbers
 */
#define getuuid(str, arr) \
		sscanf(str, "%u-%u-%u-%u-%u-%u-%u-%u-%u-%u", \
			   arr, arr + 1, arr + 2, arr + 3, \
			   arr + 4, arr + 5, arr + 6, arr + 7, \
			   arr + 8, arr + 9)

/**
 * @brief      compare uuid
 * @param[char*]      u1:The first uuid
 * @param[char*]      u2:The second uuid
 * @return     result code, whose meaning can be referred to definition.
 * @retval     int code
 */
int uuidcmp(char* u1, char* u2){
	int len1 = strlen(u1);
	int len2 = strlen(u2);
	if(len1 != 89 || len2 != 89)
		return UUID_LEN_ERROR;
	unsigned int uuid1[10];
	unsigned int uuid2[10];
	int n1 = getuuid(u1, uuid1);
	int n2 = getuuid(u2, uuid2);
	if(n1 != 10 || n2 != 10)
		return UUID_FORMAT_ERROR;
	int i;
	for(i = 0;i < 10;i++)
		if(uuid1[i] < uuid2[i])
			return UUID_BELOW;
		else if(uuid1[i] > uuid2[i])
			return UUID_GREATER;
		else
			continue;
	return UUID_EQUAL;
}

/**
 * @brief      compute hash of given string, range 0 to 2^64-2
 * @param[char*]      str:The string
 * @return     hash value, 2^64-1(aka -1) if string is NULL
 * @retval     uint64_t hash value
 */
uint64_t hash(char* str){
	if(str == NULL)
		return -1;
	uint64_t value = 0;
	int len = strlen(str);
	int i = 0;
	for(i = 0;i < len; i++)
		value = value * 31 + str[i];
	return value;
}