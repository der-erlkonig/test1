/**
 * @file C/include/utils/bits.h
 * @brief      some useful bit-related methods
 * @version    0.0.2
 * @author     Ji Xiangyu
 * @date       2021.10.6
 */
#include "lib.h"

#define UUID_LEN_ERROR 2
#define UUID_FORMAT_ERROR 3

union bit32_t{
	unsigned int uintbit;
	int intbit;
	float floatbit;
};

union bit64_t{
	unsigned long ulongbit;
	long longbit;
	void* ptrbit;
	double doublebit;
};

int uuidcmp(char*, char*);
