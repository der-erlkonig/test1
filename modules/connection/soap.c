/**
 * @file modules/connection/soap.c
 * @brief      implementation of utils for soap, allocate/free soap instance,etc.
 * @author     Ji Xiangyu
 * @date       2021.9.11
 * @version    0.0.1-dev
 */


#include "soap.h"
#include "namespace.h"
#include "soapH.h"

soap* new_soap(int timeout){
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

void* soap_alloc(soap* soap, unsigned int n){
    void* p = NULL;
    if(n > 0){
        p = soap_malloc(soap, (size_t)n);
        if(p == NULL)
            return NULL;
            memset(p, 0, (size_t)n);
    }
    return p;
}

void free_soap(soap* soap){
    //free memory allocated by soap_malloc
    soap_destroy(soap);
    //free data
    soap_end(soap);
    //free context
    soap_done(soap);
    //confirm free
    soap_free(soap);
}

int set_auth(soap* soap, char* username, char* passwd){
    if(soap == NULL || username == NULL || passwd == NULL)
        return -1;
    //TODO:implicit declaration
    return soap_wsse_add_UsernameTokenDigest(soap, NULL, username, passwd);
}
