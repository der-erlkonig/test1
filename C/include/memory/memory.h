/**
 * @file C/include/memory/memory.h
 * @brief      customized memory pool, to improve malloc/free with high frequency
 * @version    0.0.2
 * @author     Ji Xiangyu
 * @date       2021.10.15
 */
#include <stdlib.h>
/**
 * @defgroup   Memory
 * @brief      memory pool
 * @{
 */
/**
 * @defgroup   Memory_Wrapper
 * @brief      wrapper of standard functions
 * @details    functions in this part will intercept calling of standard methods,
 *             execute our methods, which wraps standard methods.But we do not expect 
 *             developers to rewrite codes, so library interpositioning is introduced.
 *             In that case, developers only need to change header and add extra options 
 *             to build project. But some wrappers is needed.
 * @{
 */
void *__wrap_malloc(size_t size);
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
 * @}
 */
/**
 * @defgroup   Memory_Type
 * @brief      type of memory pool
 * @{
 */

/**
 * @}
 */
/**
 * @}
 */
