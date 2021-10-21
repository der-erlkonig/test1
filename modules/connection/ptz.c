/**
 * @file modules/connection/ptz.c
 * @brief      This file implements ptz.
 *
 * @author     Changchun
 * @date       2021
 */
#include "connection/ptz.h"
/**
 * @brief      execute absolute move
 * @param[char*] xaddrs:The media service address
 * @param[char*] username:The username
 * @param[char*] passwd:The password
 * @param[float] pan:The pan
 * @param[float] tilt:The tilt
 * @param[float] zoom:The zoom
 */
void absoluteMove(char* xaddrs, char* token, char* username, char* passwd, float pan, float tilt, float zoom){
	char spaces[] = "http://www.onvif.org/ver10/ptz/PanTiltSpaces/PositionGenericSpace";
	if(xaddrs == NULL)
		return;
	struct soap* soap = new_soap(SOAP_TIMEOUT);
	set_auth(soap, username, passwd);
	struct _tptz__AbsoluteMove request;
	struct _tptz__AbsoluteMoveResponse response;
	memset(&request, 0, sizeof(request));
	memset(&response, 0, sizeof(response));
	request.ProfileToken = (char*)soap_alloc(soap, strlen(token) + 1);
	strcpy(request.ProfileToken, token);
	request.Position = (struct tt__PTZVector*)soap_alloc(soap, sizeof(struct tt__PTZVector));
	request.Speed = (struct tt__PTZSpeed*)soap_alloc(soap, sizeof(struct tt__PTZSpeed));
	request.Position -> PanTilt = (struct tt__Vector2D*)soap_alloc(soap, sizeof(struct tt__Vector2D));
	request.Position -> Zoom = (struct tt__Vector1D*)soap_alloc(soap, sizeof(struct tt__Vector1D));
	request.Position -> PanTilt -> x = pan;
	request.Position -> PanTilt -> y = tilt;
	request.Position -> PanTilt -> space = (char*)soap_alloc(soap, strlen(spaces) + 1);
	strcpy(request.Position -> PanTilt -> space, spaces);
	request.Position -> Zoom -> x = zoom;
	request.Position -> Zoom -> space = (char*)soap_alloc(soap, strlen(spaces) + 1);
	strcpy(request.Position -> Zoom -> space, spaces);
	request.Speed -> PanTilt = (struct tt__Vector2D*)soap_alloc(soap, sizeof(struct tt__Vector2D));
	request.Speed -> Zoom = (struct tt__Vector1D*)soap_alloc(soap, sizeof(struct tt__Vector1D));
	request.Speed -> PanTilt -> x = 1;
	request.Speed -> PanTilt -> y = 1;
	request.Speed -> PanTilt -> space = (char*)soap_alloc(soap, strlen(spaces) + 1);
	strcpy(request.Speed -> PanTilt -> space, spaces);
	request.Speed -> Zoom -> x = 1;
	request.Speed -> Zoom -> space = (char*)soap_alloc(soap, strlen(spaces) + 1);
	strcpy(request.Speed -> Zoom -> space, spaces);
	soap_call___tptz__AbsoluteMove(soap, xaddrs, NULL, &request, &response);
	free_soap(soap);
}

/**
 * @brief      perform continuous move
 * @param[char*] xaddrs:The media service address
 * @param[char*] token:The token
 * @param[char*] username:The username
 * @param[char*] passwd:The password
 * @param[int]   pan:The pan
 * @param[int]   tilt:The tilt
 * @param[int]   zoom:The zoom
 * @param[char*] timeout:The timeout
 * @note       please set one direction at once for correctness
 */
void continuousMove(char* xaddrs, char* token, char* username, char* passwd, float pan, float tilt, float zoom, char* timeout){
	if(xaddrs == NULL)
		return;
	struct soap* soap = new_soap(SOAP_TIMEOUT);
	set_auth(soap, username, passwd);
	struct _tptz__ContinuousMove request;
	struct _tptz__ContinuousMoveResponse response;
	memset(&request, 0, sizeof(request));
	memset(&response, 0, sizeof(response));
	request.ProfileToken = (char*)soap_alloc(soap, strlen(token) + 1);
	strcpy(request.ProfileToken, token);
	if(timeout){
		request.Timeout = (char*)soap_alloc(soap, strlen(timeout) + 1);
		strcpy(request.Timeout, timeout);
	}
	request.Velocity = (struct tt__PTZSpeed*)soap_alloc(soap, sizeof(struct tt__PTZSpeed));
	request.Velocity -> PanTilt = (struct tt__Vector2D*)soap_alloc(soap, sizeof(struct tt__Vector2D));
	request.Velocity -> Zoom = (struct tt__Vector1D*)soap_alloc(soap, sizeof(struct tt__Vector1D));
	request.Velocity -> PanTilt -> x = pan;
	request.Velocity -> PanTilt -> y = tilt;
	request.Velocity -> Zoom -> x = zoom;
	soap_call___tptz__ContinuousMove(soap, xaddrs, NULL, &request, &response);
	free_soap(soap);
}

/**
 * @brief      stop move
 * @param[char*] xaddrs:The media service address
 * @param[char*] token:The token
 * @param[char*] username:The username
 * @param[char*] passwd:The password
 */
void stop(char* xaddrs, char* token, char* username, char* passwd){
	if(xaddrs == NULL)
		return;
	struct soap* soap = new_soap(SOAP_TIMEOUT);
	set_auth(soap, username, passwd);
	struct _tptz__Stop request;
	struct _tptz__StopResponse response;
	memset(&request, 0, sizeof(request));
	memset(&response, 0, sizeof(response));
	request.ProfileToken = (char*)soap_alloc(soap, strlen(token) + 1);
	strcpy(request.ProfileToken, token);
	soap_call___tptz__Stop(soap, xaddrs, NULL, &request, &response);
	free_soap(soap);
}
