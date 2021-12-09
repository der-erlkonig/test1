/**
 * @file modules/include/connection/discovery.h
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

void init_probe_header(struct soap*);
void init_probe_type(struct soap*, struct wsdd__ProbeType*);
int detect_device(char**);
