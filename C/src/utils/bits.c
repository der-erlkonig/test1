#include "utils/bits.h"

#define getuuid(str, arr) \
		sscanf(str, "%u-%u-%u-%u-%u-%u-%u-%u-%u-%u",
			   arr[0], arr[1], arr[2], arr[3],
			   arr[4], arr[5], arr[6], arr[7],
			   arr[8], arr[9])

int uuidcmp(char* u1, char* u2){
	int len1 = strlen(u1);
	int len2 = strlen(u2);
	if(len1 != 89 || len2 != 89)
		return UUID_LEN_ERROR;
	unsigned int uuid1[10];
	unsigned int uuid2[10];
	int n1 = getuuid(u1, uuid1);
	int n2 = getuuid(u2, uuid2);
	

}