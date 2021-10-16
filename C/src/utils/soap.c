/**
 * @file C/src/utils/soap.c
 * @brief      implementation of utils for soap, allocate/free soap instance,etc.
 * @author     Ji Xiangyu
 * @date       2021.9.11
 * @version    0.0.1-dev
 */
#include "utils/soap.h"
#include "namespace.h"
/**
 * @brief      allocate a new soap instance
 * @param[int] timeout:The timeout
 * @return     a new soap instance
 * @retval     soap*  soap instance
 */
struct soap* new_soap(int timeout){
    struct soap* soap = NULL;
    
    soap = soap_new();
    if(soap == NULL)
        return NULL;

    //bind namespaces
    soap_set_namespaces(soap, namespaces);
    soap -> recv_timeout = timeout;
    soap -> send_timeout = timeout;
    soap -> connect_timeout = timeout;

#if defined(__linux__) || defined(__linux)
    soap -> socket_flags = MSG_NOSIGNAL;
#endif

    //set charset
    soap_set_mode(soap, SOAP_C_UTFSTRING);
    return soap;
}
/**
 * @brief      allocate memory
 * @param[soap*] soap:The soap
 * @param[unsigned int]  n:bytes of memory which needs to be allocated
 * @return     pointer which points to the first address of memory
 * @retval     void*  memory pointer
 */
void* soap_alloc(struct soap* soap, unsigned int n){
    void* p = NULL;
    if(n > 0){
        p = soap_malloc(soap, (size_t)n);
        if(p == NULL)
            return NULL;
            memset(p, 0, (size_t)n);
    }
    return p;
}
/**
 * @brief      free soap
 * @param[soap*] soap:The soap
 */
void free_soap(struct soap* soap){
    //free memory allocated by soap_malloc
    soap_destroy(soap);
    //free data
    soap_end(soap);
    //free context
    soap_done(soap);
    //confirm free
    soap_free(soap);
}

/**
 * @brief      Sets the authentication infomation.
 * @param[soap*]      soap:The soap
 * @param[char*]      username:The username
 * @param[char*]      passwd:The password
 * @return     state code of set authentication operation.
 * @retval     int  state code
 * @note       all onvif methods will require username and password, but in the specification, not all interfaces need authenrized, so just set any of username or password NULL.
 */
int set_auth(struct soap* soap, char* username, char* passwd){
    if(soap == NULL || username == NULL || passwd == NULL)
        return -1;
    return soap_wsse_add_UsernameTokenDigest(soap, NULL, username, passwd);
}