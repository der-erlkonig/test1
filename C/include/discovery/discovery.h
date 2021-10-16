/**
 * @file C/include/discovery/discovery.h
 * @brief      definition of remote discovery
 * @author     Ji Xiangyu
 * @date       2021.9.11
 * @version    0.0.1-dev
 */
#pragma once
#include "common.h"
/**
 * @defgroup    Discovery
 * @brief       Difinition of remote discovery
 * @{
 */
/**
 * @defgroup    Discovery_constant
 * @brief       common constant of remote discovery
 * @{
 */
#define SOAP_TO "urn:schemas-xmlsoap-org:ws:2005:04:discovery"/*!< SOAP_TO */
#define SOAP_ACTION "http://schemas.xmlsoap.org/ws/2005/04/discovery/Probe"/*!< SOAP_ACTION */

#define SOAP_MULTICAST "soap.udp://239.255.255.250:3702"/*!< multicast address */

#define SOAP_ITEM ""/*!< ITEM */
#define SOAP_TYPES "tdn:NetworkVideoTransmitter"/*!< IPC types */

#define MAX_IPC_STORE 255/*!< max numbers of IPC address. */

/**
 * @}
 */
/**
 * @defgroup   Discovery_Exported_Methods
 * @brief      exported methods of detect device, make all to be not-static for flexibility
 * @{
 */
void init_probe_header(struct soap*);
void init_probe_type(struct soap*, struct wsdd__ProbeType*);
int detect_device(char**);
/**
 * @}
 */
/**
 * @}
 */
