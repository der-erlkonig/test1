#include <stdlib.h>
void *__wrap_malloc(size_t size);
void *__real_malloc(size_t size);
void __wrap_free(void* ptr);
void __real_free(void* ptr);