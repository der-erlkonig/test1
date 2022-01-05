/**
 * @file       include/connection/discovery.h
 * @brief      definition of remote discovery
 * @author     Ji Xiangyu
 * @date       2021.9.11
 * @version    0.0.1-dev
 */
#pragma once
#include "onvif_common.h"

#define SOAP_TO "urn:schemas-xmlsoap-org:ws:2005:04:discovery"/*!< SOAP_TO */
#define SOAP_ACTION "http://schemas.xmlsoap.org/ws/2005/04/discovery/Probe"/*!< SOAP_ACTION */
#define SOAP_MULTICAST "soap.udp://239.255.255.250:3702"/*!< multicast address */
#define SOAP_ITEM ""/*!< ITEM */
#define SOAP_TYPES "tdn:NetworkVideoTransmitter"/*!< IPC types */
#define MAX_IPC_STORE 255/*!< max numbers of IPC address. */

/**
 * @brief      Initializes the probe header.
 * @param[in]  soap The soap environment
 */
void init_probe_header(struct soap*);

/**
 * @brief      Initializes the probe type.
 * @param[in]  soap  The soap
 * @param[out] probe The probe pointer, which is used to store infomation.
 */
void init_probe_type(struct soap* soap, struct wsdd__ProbeType* probe);

/**
 * @brief      detect IPCs, via multicast
 * @param[out] xaddrs array of strings that is used to store the address of IPC
 * @return     number of IPC detected
 */
int detect_device(char** xaddrs);