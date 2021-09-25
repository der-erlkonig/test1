/**
 * @file C/src/snap/media.c
 * @brief      implementation of media-related methods.
 * @version    0.0.1-dev
 * @author     Ji Xiangyu
 * @date       2021.9.14
 */
#include "snap/media.h"
/**
 * @brief      Gets the profile, default is index 0.
 * @param[char*]      xaddrs:The media service address
 * @param[char*]      username:The username
 * @param[char*]      passwd:The password
 * @param[char*]      profile:string pointer to store profile token
 */
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

/**
 * @brief      Gets the snapshot uri.
 * @param[char*]      xaddrs:The media service address
 * @param[char*]      token:The media profile token
 * @param[char*]      username:The username
 * @param[char*]      passwd:The passwd
 * @param[char*]      snapshotUri:string pointer to store the snapshot uri
 */
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

/**
 * @brief      Gets the stream uri.
 * @param[char*]      xaddrs:The media service address
 * @param[char*]      token      The token
 * @param      username   The username
 * @param      passwd     The passwd
 * @param      streamUri  The stream uri
 */
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

/**
 * @brief      Gets the snapshot.
 * @param[char*] xaddrs:The media service address
 * @param[char*] username:The username
 * @param[char*] passwdThe password
 * @param[char*] path:The path to store image
 */
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