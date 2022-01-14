/**
 * @file modules/management/bits.c
 * @brief      This file implements bits-level methods.
 * @version    0.0.2
 * @author     Ji Xiangyu
 * @date       2021.10.15
 */
#include "bits.h"
#include <stdio.h>
#include <string.h>

#define getuuid(str, arr) \
		sscanf(str, "%u-%u-%u-%u-%u-%u-%u-%u-%u-%u", \
			   arr, arr + 1, arr + 2, arr + 3, \
			   arr + 4, arr + 5, arr + 6, arr + 7, \
			   arr + 8, arr + 9)

#define setuuid(str, arr) \
		sprintf(str, "%u-%u-%u-%u-%u-%u-%u-%u-%u-%u", \
			   arr[0], arr[1], arr[2], arr[3], \
			   arr[4], arr[5], arr[6], arr[7], \
			   arr[8], arr[9])

#define INIT "0-0-0-0-0-0-0-0-0-0"

int uuidcmp(char* u1, char* u2){
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

void uuidinc(char* uuid){
	unsigned int arr[10];
	int n = getuuid(uuid, arr);
	if(n != 10) return;
	int i = 9;
	int flag = 1;
	for(;flag && i >= 0;i--){
		if(arr[i] == 9999)
			//cannot resolve increasement
			arr[i] = 0;
		else{
			//resolve it, and stop passing
			arr[i] += 1;
			flag = 0;
		}
	}
	setuuid(uuid, arr);
}

char* uuidinit(){
	return INIT;
}