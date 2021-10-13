#include "memory/memory.h"
void *__wrap_malloc(size_t size){
	void* ptr = __real_malloc(size);
	return ptr;
}
void __wrap_free(void* ptr){
	__real_free(ptr);
}