/**
 * @file modules/connection/media.c
 * @brief      implementation of media-related methods.
 * @version    0.0.1-dev
 * @author     Ji Xiangyu
 * @date       2021.9.14
 */
#include "media.h"
#include "soap.h"
#include <string.h>
#include <stdlib.h>
#include "soapH.h"

void getProfile(char* xaddrs, char* username, char* passwd, char* profile){
	if(xaddrs == NULL || profile == NULL)
		return;
	struct soap* soap = new_soap(SOAP_TIMEOUT);
	set_auth(soap, username, passwd);
	struct _trt__GetProfiles request;
	struct _trt__GetProfilesResponse response;
	memset(&request, 0, sizeof(request));
	memset(&response, 0, sizeof(response));
	int result = soap_call___trt__GetProfiles(soap, xaddrs, NULL, &request, &response);
	if(result == SOAP_OK)
		if(response.__sizeProfiles != 0){
			strcpy(profile, response.Profiles -> token);
			free_soap(soap);
			return;
		}	
	strcpy(profile, "");
	free_soap(soap);
	return;
}

void getSnapshotUri(char* xaddrs, char* token, char* username, char* passwd, char* snapshotUri){
	if(xaddrs == NULL || token == NULL)
		return;
	struct soap* soap = new_soap(SOAP_TIMEOUT);
	set_auth(soap, username, passwd);
	struct _trt__GetSnapshotUri request;
	struct _trt__GetSnapshotUriResponse response;
	memset(&request, 0, sizeof(request));
	memset(&response, 0, sizeof(response));
	request.ProfileToken = (char*)soap_alloc(soap, strlen(token) + 1);
	strcpy(request.ProfileToken, token);
	int result = soap_call___trt__GetSnapshotUri(soap, xaddrs, NULL, &request, &response);
	if(result == SOAP_OK){
		strcpy(snapshotUri, response.MediaUri -> Uri);
		free_soap(soap);
		return;
	}else{
		strcpy(snapshotUri, "");
		free_soap(soap);
		return;
	}
}

void getStreamUri(char* xaddrs, char* token, char* username, char* passwd, char* streamUri){
	
	if(xaddrs == NULL || token == NULL)
		return;
	struct soap* soap = new_soap(SOAP_TIMEOUT);
	set_auth(soap, username, passwd);
	struct _trt__GetStreamUri request;
	struct _trt__GetStreamUriResponse response;
	memset(&request, 0, sizeof(request));
	memset(&response, 0, sizeof(response));
	request.ProfileToken = (char*)soap_alloc(soap, strlen(token) + 1);
	strcpy(request.ProfileToken, token);
	request.StreamSetup = (struct tt__StreamSetup*)soap_alloc(soap, sizeof(struct tt__StreamSetup));
	request.StreamSetup -> Stream = 0;
	request.StreamSetup -> Transport = (struct tt__Transport*)soap_alloc(soap, sizeof(struct tt__Transport));
	request.StreamSetup -> Transport -> Protocol = 2;
	int result = soap_call___trt__GetStreamUri(soap, xaddrs, NULL, &request, &response);
	if(result == SOAP_OK){
		strcpy(streamUri, response.MediaUri -> Uri);
		free_soap(soap);
		return;
	}else{
		strcpy(streamUri, "");
		free_soap(soap);
		return;
	}
}

void getSnapshot(char* xaddrs, char* username, char* passwd, char* path){
	char* cmd = (char*)malloc(200);
	memset(cmd, 0, 200);
	strcat(cmd, "nohup wget -O ");
	strcat(cmd, path);
	strcat(cmd, " http://");
	if(username && passwd){
		strcat(cmd, username);
		strcat(cmd, ":");
		strcat(cmd, passwd);
		strcat(cmd, "@");
	}
	strcat(cmd, xaddrs + 7);
	strcat(cmd, " &");
	system(cmd);
	system("\n");
	return;
}

void get_capabilities(char* xaddr, capabilities_model* cap, char* username, char* passwd){
    if(xaddr==NULL || cap==NULL)
        return;

    struct soap* soap = new_soap(SOAP_TIMEOUT);

    if(soap ==NULL){
        cap -> valid =0;
        return;
    }

    set_auth(soap, username, passwd);

    struct _tds__GetCapabilities request;
	struct _tds__GetCapabilitiesResponse response;
    memset(&request, 0, sizeof(request));
	memset(&response, 0, sizeof(response));

    int result = soap_call___tds__GetCapabilities(soap, xaddr, NULL, &request, &response);
    if(result == SOAP_OK){
        if(response.Capabilities->Analytics)
            cap->Analytics = response.Capabilities->Analytics;
        else
            cap->Analytics = NULL;


        if(response.Capabilities->Device)
            cap->Device = response.Capabilities->Device;
        else
            cap->Device = NULL;


        if(response.Capabilities->Events)
            cap->Events = response.Capabilities->Events;
        else
            cap->Events = NULL;


        if(response.Capabilities->Imaging)
            cap->Imaging = response.Capabilities->Imaging;
        else
            cap->Imaging = NULL;


        if(response.Capabilities->Media)
            cap->Media = response.Capabilities->Media;
        else
            cap->Media = NULL;


        if(response.Capabilities->PTZ)
            cap->PTZ = response.Capabilities->PTZ;
        else
            cap->PTZ = NULL;


        if(response.Capabilities->Extension)
            cap->Extension = response.Capabilities->Extension;
        else
            cap->Extension = NULL;    
    }else{
        cap->valid = 0;
        return;
    }
    free_soap(soap);
}