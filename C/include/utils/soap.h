/**
 * @file C/include/utils/soap.h
 * @brief      definition of utils for soap, allocate/free soap instance,etc.
 * @author     Ji Xiangyu
 * @date       2021.9.11
 * @version    0.0.1-dev
 */
#pragma once
#include "lib.h"
/**
 * @defgroup    SOAP
 * @brief       utils for soap
 * @{
 */
/**
 * @defgroup   SOAP_Exported_Methods
 * @brief      difinition of exported methods of soap
 * @{
 */
#define SOAP_TIMEOUT 10/*!< default timeout for soap */
struct soap* new_soap(int);
void* soap_alloc(struct soap*, unsigned int);
void free_soap(struct soap*);
int set_auth(struct soap*, char*, char*);
/**
 * @}
 */
/**
 * @}
 */
