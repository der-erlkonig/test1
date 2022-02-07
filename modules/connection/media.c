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

void get_capabilities(char* xaddrs, capabilities_model* cap, char* username, char* passwd){
    if(xaddrs==NULL || cap==NULL)
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

    int result = soap_call___tds__GetCapabilities(soap, xaddrs, NULL, &request, &response);
    if(result == SOAP_OK){
        if(response.Capabilities->Analytics){
			strcpy( cap->Analytics -> XAddr,  response.Capabilities->Analytics -> XAddr);
            cap->Analytics -> RuleSupport = response.Capabilities->Analytics -> RuleSupport;
			cap->Analytics -> AnalyticsModuleSupport = response.Capabilities->Analytics -> AnalyticsModuleSupport;
		}
        else
            cap->Analytics = NULL;


        if(response.Capabilities->Device){
			strcpy(cap->Device -> XAddr,  response.Capabilities->Device-> XAddr);
			*(cap->Device -> Network -> IPFilter) = *(response.Capabilities->Device -> Network -> IPFilter);
			*(cap->Device -> Network -> ZeroConfiguration) = *(response.Capabilities->Device -> Network -> ZeroConfiguration);
			*(cap->Device -> Network -> IPVersion6) = *(response.Capabilities->Device -> Network -> IPVersion6);
			*(cap->Device -> Network -> DynDNS) = *(response.Capabilities->Device -> Network -> DynDNS);
			*(cap->Device -> Network -> Extension -> Dot11Configuration) = *(response.Capabilities->Device -> Network -> Extension -> Dot11Configuration);
			#ifdef WITH_NOEMPTYSTRUCT
				cap->Device -> Network -> Extension -> Extension ->dummy = response.Capabilities->Device -> Network -> Extension -> Extension ->dummy;
			#endif
			cap->Device -> System -> DiscoveryResolve = response.Capabilities->Device -> System -> DiscoveryResolve;
			cap->Device -> System -> DiscoveryBye = response.Capabilities->Device -> System -> DiscoveryBye;
			cap->Device -> System -> RemoteDiscovery = response.Capabilities->Device -> System -> RemoteDiscovery;
			cap->Device -> System -> SystemBackup = response.Capabilities->Device -> System -> SystemBackup;
			cap->Device -> System -> SystemLogging = response.Capabilities->Device -> System -> SystemLogging;
			cap->Device -> System -> FirmwareUpgrade = response.Capabilities->Device -> System -> FirmwareUpgrade;
			cap->Device -> System -> __sizeSupportedVersions = response.Capabilities->Device -> System -> __sizeSupportedVersions;
			cap->Device -> System -> SupportedVersions -> Major = response.Capabilities->Device -> System -> SupportedVersions -> Major;
			cap->Device -> System -> SupportedVersions -> Minor = response.Capabilities->Device -> System -> SupportedVersions -> Minor;
			*(cap->Device -> System -> Extension ->HttpFirmwareUpgrade)= *(response.Capabilities->Device -> System -> Extension ->HttpFirmwareUpgrade);
			*(cap->Device -> System -> Extension ->HttpSystemBackup)= *(response.Capabilities->Device -> System -> Extension ->HttpSystemBackup);
			*(cap->Device -> System -> Extension ->HttpSystemLogging)= *(response.Capabilities->Device -> System -> Extension ->HttpSystemLogging);
			*(cap->Device -> System -> Extension ->HttpSupportInformation)= *(response.Capabilities->Device -> System -> Extension ->HttpSupportInformation);
			#ifdef WITH_NOEMPTYSTRUCT
				cap->Device -> System -> Extension -> Extension ->dummy = response.Capabilities->Device -> System -> Extension -> Extension ->dummy;
			#endif
			*(cap->Device -> IO -> InputConnectors)= *(response.Capabilities->Device -> IO ->InputConnectors);
			*(cap->Device -> IO -> RelayOutputs)= *(response.Capabilities->Device -> IO ->RelayOutputs);

			*(cap->Device -> IO -> Extension -> Auxiliary)= *(response.Capabilities->Device -> IO ->Extension ->Auxiliary);
			cap->Device -> IO -> Extension -> __sizeAuxiliaryCommands = response.Capabilities->Device -> IO ->Extension -> __sizeAuxiliaryCommands;
			*(cap->Device -> IO -> Extension -> AuxiliaryCommands)= *(response.Capabilities->Device -> IO ->Extension ->AuxiliaryCommands);
			#ifdef WITH_NOEMPTYSTRUCT
				cap->Device -> IO -> Extension ->Extension -> dummy = response.Capabilities->Device -> IO -> Extension ->Extension -> dummy;
			#endif
			cap->Device -> Security -> TLS1_x002e1 = response.Capabilities->Device -> Security -> TLS1_x002e1;
			cap->Device -> Security -> TLS1_x002e2 = response.Capabilities->Device -> Security -> TLS1_x002e2;
			cap->Device -> Security -> OnboardKeyGeneration = response.Capabilities->Device -> Security -> OnboardKeyGeneration;
			cap->Device -> Security -> AccessPolicyConfig = response.Capabilities->Device -> Security -> AccessPolicyConfig;
			cap->Device -> Security -> X_x002e509Token = response.Capabilities->Device -> Security -> X_x002e509Token;
			cap->Device -> Security -> SAMLToken = response.Capabilities->Device -> Security -> SAMLToken;
			cap->Device -> Security -> KerberosToken = response.Capabilities->Device -> Security -> KerberosToken;
			cap->Device -> Security -> RELToken = response.Capabilities->Device -> Security -> RELToken;
			cap->Device -> Security -> Extension -> TLS1_x002e0 = response.Capabilities->Device -> Security -> Extension -> TLS1_x002e0;
			cap->Device -> Security -> Extension -> Extension -> Dot1X = response.Capabilities->Device -> Security -> Extension -> Extension -> Dot1X;
			cap->Device -> Security -> Extension -> Extension -> __sizeSupportedEAPMethod = response.Capabilities->Device -> Security -> Extension -> Extension -> __sizeSupportedEAPMethod;
			*(cap->Device -> Security -> Extension -> Extension -> SupportedEAPMethod) = *(response.Capabilities->Device -> Security -> Extension -> Extension -> SupportedEAPMethod);
			cap->Device -> Security -> Extension -> Extension -> RemoteUserHandling = response.Capabilities->Device -> Security -> Extension -> Extension -> RemoteUserHandling;
			#ifdef WITH_NOEMPTYSTRUCT
				cap->Device -> Extension -> dummy = response.Capabilities->Device->Extension -> dummy;
			#endif
		}
        else
            cap->Device = NULL;


        if(response.Capabilities->Events){
			strcpy( cap->Events -> XAddr,  response.Capabilities->Events -> XAddr);
			cap->Events->WSSubscriptionPolicySupport = response.Capabilities->Events->WSSubscriptionPolicySupport;
			cap->Events->WSPullPointSupport = response.Capabilities->Events->WSPullPointSupport;
			cap->Events->WSPausableSubscriptionManagerInterfaceSupport = response.Capabilities->Events->WSPausableSubscriptionManagerInterfaceSupport;
		}
        else
            cap->Events = NULL;


        if(response.Capabilities->Imaging){
			strcpy( cap->Imaging -> XAddr,  response.Capabilities->Imaging -> XAddr);

		}
        else
            cap->Imaging = NULL;


        if(response.Capabilities->Media){
			strcpy( cap->Media -> XAddr,  response.Capabilities->Media -> XAddr);
			*(cap->Media -> StreamingCapabilities -> RTPMulticast) = *(response.Capabilities->Media -> StreamingCapabilities -> RTPMulticast);
			*(cap->Media -> StreamingCapabilities -> RTP_USCORETCP) = *(response.Capabilities->Media -> StreamingCapabilities -> RTP_USCORETCP);
			*(cap->Media -> StreamingCapabilities -> RTP_USCORERTSP_USCORETCP) = *(response.Capabilities->Media -> StreamingCapabilities -> RTP_USCORERTSP_USCORETCP);
			#ifdef WITH_NOEMPTYSTRUCT
				cap->Media -> StreamingCapabilities -> Extension -> dummy= response.Capabilities->Media -> StreamingCapabilities -> Extension ->dummy;
			#endif
			cap->Media -> Extension -> ProfileCapabilities -> MaximumNumberOfProfiles = response.Capabilities->Media -> Extension -> ProfileCapabilities -> MaximumNumberOfProfiles;
		}
        else
            cap->Media = NULL;


        if(response.Capabilities->PTZ){
			strcpy( cap->PTZ -> XAddr,  response.Capabilities->PTZ -> XAddr);
		}
        else
            cap->PTZ = NULL;


        if(response.Capabilities->Extension){
			strcpy( cap->Extension -> DeviceIO -> XAddr,response.Capabilities->Extension -> DeviceIO -> XAddr);
			cap->Extension -> DeviceIO ->VideoSources= response.Capabilities->Extension -> DeviceIO ->VideoSources;
			cap->Extension -> DeviceIO ->VideoOutputs= response.Capabilities->Extension -> DeviceIO ->VideoOutputs;
			cap->Extension -> DeviceIO ->AudioSources= response.Capabilities->Extension -> DeviceIO ->AudioSources;
			cap->Extension -> DeviceIO ->AudioOutputs= response.Capabilities->Extension -> DeviceIO ->AudioOutputs;
			cap->Extension -> DeviceIO ->RelayOutputs= response.Capabilities->Extension -> DeviceIO ->RelayOutputs;
			strcpy( cap->Extension -> Display -> XAddr,response.Capabilities->Extension -> Display -> XAddr);
			cap->Extension -> Display ->FixedLayout= response.Capabilities->Extension -> Display ->FixedLayout;
			strcpy( cap->Extension -> Recording -> XAddr,response.Capabilities->Extension -> Recording -> XAddr);
			cap->Extension -> Recording ->ReceiverSource= response.Capabilities->Extension -> Recording ->ReceiverSource;
			cap->Extension -> Recording ->MediaProfileSource= response.Capabilities->Extension -> Recording ->MediaProfileSource;
			cap->Extension -> Recording ->DynamicRecordings= response.Capabilities->Extension -> Recording ->DynamicRecordings;
			cap->Extension -> Recording ->DynamicTracks= response.Capabilities->Extension -> Recording ->DynamicTracks;
			cap->Extension -> Recording ->MaxStringLength= response.Capabilities->Extension -> Recording ->MaxStringLength;
			strcpy( cap->Extension -> Search -> XAddr,response.Capabilities->Extension -> Search -> XAddr);
			cap->Extension -> Search ->MetadataSearch= response.Capabilities->Extension -> Search ->MetadataSearch;
			strcpy( cap->Extension -> Replay -> XAddr,response.Capabilities->Extension -> Replay -> XAddr);
			strcpy( cap->Extension -> Receiver -> XAddr,response.Capabilities->Extension -> Receiver -> XAddr);
			cap->Extension -> Receiver ->RTP_USCOREMulticast= response.Capabilities->Extension -> Receiver ->RTP_USCOREMulticast;
			cap->Extension -> Receiver ->RTP_USCORETCP= response.Capabilities->Extension -> Receiver ->RTP_USCORETCP;
			cap->Extension -> Receiver ->RTP_USCORERTSP_USCORETCP= response.Capabilities->Extension -> Receiver ->RTP_USCORERTSP_USCORETCP;
			cap->Extension -> Receiver ->SupportedReceivers= response.Capabilities->Extension -> Receiver ->SupportedReceivers;
			cap->Extension -> Receiver ->MaximumRTSPURILength= response.Capabilities->Extension -> Receiver ->MaximumRTSPURILength;
			strcpy( cap->Extension -> AnalyticsDevice -> XAddr,response.Capabilities->Extension -> AnalyticsDevice -> XAddr);
			*(cap->Extension -> AnalyticsDevice ->RuleSupport)= *(response.Capabilities->Extension -> AnalyticsDevice ->RuleSupport);
			#ifdef WITH_NOEMPTYSTRUCT
				cap->Extension -> AnalyticsDevice ->Extension ->dummy= response.Capabilities->Extension -> AnalyticsDevice ->Extension ->dummy;
			#endif
			#ifdef WITH_NOEMPTYSTRUCT
				cap->Extension -> Extensions ->dummy= response.Capabilities->Extension -> Extensions ->dummy;
			#endif
		}
        else
            cap->Extension = NULL;    
    }else{
        cap->valid = 0;
        return;
    }
    free_soap(soap);
}

void get_PTZ(char* xaddrs, char* ptzcap, char* username, char* passwd, int* result){
	if(xaddrs==NULL)
        return;
    struct soap* soap = new_soap(SOAP_TIMEOUT);
	set_auth(soap, username, passwd);

    struct _tds__GetCapabilities request;
	struct _tds__GetCapabilitiesResponse response;
    memset(&request, 0, sizeof(request));
	memset(&response, 0, sizeof(response));

    int result = soap_call___tds__GetCapabilities(soap, xaddrs, NULL, &request, &response);
    if(result == SOAP_OK){
		if(response.Capabilities -> PTZ -> XAddr){
			strcpy(ptzcap, response.Capabilities -> PTZ -> XAddr);
			*result = 1;
		}
		else{
			strcpy(ptzcap, "");
			*result = 0;
		}
	}
	free_soap(soap);

}