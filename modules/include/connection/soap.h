/**
 * @file modules/include/connection/soap.h
 * @brief      definition of utils for soap, allocate/free soap instance,etc.
 * @author     Ji Xiangyu
 * @date       2021.9.11
 * @version    0.0.1-dev
 */
#pragma once
#include "onvif_lib.h"

#define SOAP_TIMEOUT 10/*!< default timeout for soap */

/**
 * @brief      allocate a new soap instance
 * @param[in]  timeout The timeout
 * @return     a new soap instance
 */
struct soap* new_soap(int timeout);

/**
 * @brief      allocate memory with soap
 * @param[in]  soap The soap
 * @param[in]  n    bytes of memory which needs to be allocated
 * @return     pointer which points to the first address of memory
 */
void* soap_alloc(struct soap* soap, unsigned int n);

/**
 * @brief      free soap
 * @param[in]  soap The soap
 */
void free_soap(struct soap* soap);

/**
 * @brief      Sets the authentication infomation.
 * @param[in]  soap     The soap
 * @param[in]  username The username
 * @param[in]  passwd   The password
 * @return     state code of set authentication operation, 0 if success.
 * @note       all onvif methods will require username and password, but in the specification, not all interfaces need to be authenrized, so just set any of username or password NULL.
 */
int set_auth(struct soap* soap, char* username, char* passwd);