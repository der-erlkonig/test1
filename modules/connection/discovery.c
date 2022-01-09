/**
 * @file modules/connection/discovery.c
 * @brief      implementation of remote discovery.
 * @author     Ji Xiangyu
 * @date       2021.9.11
 * @version    0.0.1-dev
 */
#include "discovery.h"
#include "soap.h"
#include <string.h>
#include <stdlib.h>
#include "soapH.h"
#include "wsaapi.h"

#define SOAP_TO "urn:schemas-xmlsoap-org:ws:2005:04:discovery"/*!< SOAP_TO */
#define SOAP_ACTION "http://schemas.xmlsoap.org/ws/2005/04/discovery/Probe"/*!< SOAP_ACTION */
#define SOAP_MULTICAST "soap.udp://239.255.255.250:3702"/*!< multicast address */
#define SOAP_ITEM ""/*!< ITEM */
#define SOAP_TYPES "tdn:NetworkVideoTransmitter"/*!< IPC types */
#define MAX_IPC_STORE 255/*!< max numbers of IPC address. */

static void init_probe_header(struct soap*);
static void init_probe_type(struct soap* soap, struct wsdd__ProbeType* probe);


static void init_probe_header(struct soap* soap){
	if(soap == NULL)
		return;

	struct SOAP_ENV__Header* header = NULL;
	header = (struct SOAP_ENV__Header*)soap_alloc(soap, sizeof(struct SOAP_ENV__Header));

	//bind header
	soap_default_SOAP_ENV__Header(soap, header);

	//init header
	char* uuid = (char*)soap_wsa_rand_uuid(soap);
	header -> wsa__MessageID = (char*)soap_alloc(soap, strlen(uuid));
	header -> wsa__To = (char*)soap_alloc(soap, strlen(SOAP_TO) + 1);
	header -> wsa__Action = (char*)soap_alloc(soap, strlen(SOAP_ACTION) + 1);
	strcpy(header -> wsa__MessageID, uuid);
	strcpy(header -> wsa__To, SOAP_TO);
	strcpy(header -> wsa__Action, SOAP_ACTION);
}

static void init_probe_type(struct soap* soap, struct wsdd__ProbeType* probe){
	if(soap == NULL || probe == NULL)
		return;

	//init scope
	struct wsdd__ScopesType* scope = NULL;
	scope = (struct wsdd__ScopesType*)soap_alloc(soap, sizeof(wsdd__ScopesType));
	soap_default_wsdd__ScopesType(soap, scope);
	scope -> __item = (char*)soap_alloc(soap, strlen(SOAP_ITEM) + 1);
	strcpy(scope -> __item, SOAP_ITEM);

	//init probe
	memset(probe, 0, sizeof(struct wsdd__ProbeType));
	soap_default_wsdd__ProbeType(soap, probe);
	probe -> Scopes = scope;
	probe -> Types = (char*)soap_alloc(soap, strlen(SOAP_TYPES) + 1);
	strcpy(probe -> Types, SOAP_TYPES);
}

int detect_device(char** xaddrs){
	//error code
	int result;

	int number = 0;
	struct soap* soap = NULL;
	struct wsdd__ProbeType request;
	struct __wsdd__ProbeMatches response;
	struct wsdd__ProbeMatchType* probeMatch;

	//init soap
	soap = new_soap(SOAP_TIMEOUT);
	init_probe_header(soap);
	init_probe_type(soap, &request);

	//send and receive
	result = soap_send___wsdd__Probe(soap, SOAP_MULTICAST, NULL, &request);
	while(result == SOAP_OK){
		memset(&response, 0, sizeof(response));
		result = soap_recv___wsdd__ProbeMatches(soap, &response);
		if(result == SOAP_OK){
			if(soap -> error)
				continue;
			else{
				//dump response
				if(response.wsdd__ProbeMatches != NULL){
					int i;
					for(i = 0; i < response.wsdd__ProbeMatches -> __sizeProbeMatch; i++){
						probeMatch = (response.wsdd__ProbeMatches -> ProbeMatch) + i;
						int j = 0;
						while((probeMatch->XAddrs)[j] != ' ' && (probeMatch->XAddrs)[j] != '\0'){
							xaddrs[number + i][j] = (probeMatch -> XAddrs)[j];
							j++;
						}
					}
					number += response.wsdd__ProbeMatches -> __sizeProbeMatch;
				}
			}
		}else if(soap -> error)
			break;
	}
	return number;
}
