/**
 * @file modules/connection/ptz.c
 * @brief      This file implements ptz.
 *
 * @author     Changchun
 * @date       2021
 */
#include "connection/ptz.h"

void absoluteMove(char* xaddrs, char* token, char* username, char* passwd, float pan, float tilt, float zoom){
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
	request.Position -> Zoom -> x = zoom;
	request.Speed -> PanTilt = (struct tt__Vector2D*)soap_alloc(soap, sizeof(struct tt__Vector2D));
	request.Speed -> Zoom = (struct tt__Vector1D*)soap_alloc(soap, sizeof(struct tt__Vector1D));
	request.Speed -> PanTilt -> x = 1;
	request.Speed -> PanTilt -> y = 1;
	request.Speed -> Zoom -> x = 1;
	soap_call___tptz__AbsoluteMove(soap, xaddrs, NULL, &request, &response);
	free_soap(soap);
}

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