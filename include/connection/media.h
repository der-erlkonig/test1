/**
 * @file       include/connection/media.h
 * @brief      methods for snap(also include some media unified methods).
 * @version    0.0.1-dev
 * @author     Ji Xiangyu
 * @date       2021.9.13
 */
#pragma once

/**
 * @brief      Gets the profile, default is index 0.
 * @param[in]  xaddrs The media service address
 * @param[in]  username The username
 * @param[in]  passwd The password
 * @param[out] profile string pointer to store profile token
 */
void getProfile(char* xaddrs, char* username, char* passwd, char* profile);

/**
 * @brief      Gets the snapshot uri.
 * @param[in]  xaddrs      The media service address
 * @param[in]  token       The media profile token
 * @param[in]  username    The username
 * @param[in]  passwd      The passwd
 * @param[out] snapshotUri string pointer to store the snapshot uri
 */
void getSnapshotUri(char* xaddrs, char* token, char* username, char* passwd, char* snapshotUri);

/**
 * @brief      Gets the stream uri.
 * @param[in]      xaddrs     The media service address
 * @param[in]      token      The token
 * @param[in]      username   The username
 * @param[in]      passwd     The passwd
 * @param[out]     streamUri  The stream uri
 */
void getStreamUri(char* xaddrs, char* token, char* username, char* passwd, char* streamUri);

/**
 * @brief     Gets the snapshot.
 * @param[in] xaddrs   The snapshot address
 * @param[in] username The username
 * @param[in] passwd   The password
 * @param[in] path     The path to store image
 */
void getSnapshot(char* xaddrs, char* username, char* passwd, char* path);

/**
 * @brief     Gets the capabilities.
 * @param[in] xaddrs   The media service address
 * @param[in] username The username
 * @param[in] passwd   The password
 * @param[out] cap     The information of capabilities
 */


enum xsd__boolean11 {
            xsd__boolean__false_11 = 0,
            xsd__boolean__true_11 = 1
};

struct tt__OnvifVersion11 {
        /** Required element 'tt:Major' of XML schema type 'xsd:int' */
        int Major;
        /** Required element 'tt:Minor' of XML schema type 'xsd:int' */
        int Minor;
};


typedef struct{
    int valid;
    /** Optional element 'tt:Analytics' of XML schema type 'tt:AnalyticsCapabilities' */
    struct tt__AnalyticsCapabilities11 *Analytics;            
    /** Optional element 'tt:Device' of XML schema type 'tt:DeviceCapabilities' */
    struct tt__DeviceCapabilities11 *Device;
    /** Optional element 'tt:Events' of XML schema type 'tt:EventCapabilities' */
    struct tt__EventCapabilities11 *Events;
    /** Optional element 'tt:Imaging' of XML schema type 'tt:ImagingCapabilities' */
    struct tt__ImagingCapabilities11 *Imaging;
    /** Optional element 'tt:Media' of XML schema type 'tt:MediaCapabilities' */
    struct tt__MediaCapabilities11 *Media;
    /** Optional element 'tt:PTZ' of XML schema type 'tt:PTZCapabilities' */
    struct tt__PTZCapabilities11 *PTZ;
    /** Optional element 'tt:Extension' of XML schema type 'tt:CapabilitiesExtension' */
    struct tt__CapabilitiesExtension11 *Extension;
} capabilities_model;


    struct tt__AnalyticsCapabilities11 {
            /** Required element 'tt:XAddr' of XML schema type 'xsd:anyURI' */
            char *XAddr;
            /** Required element 'tt:RuleSupport' of XML schema type 'xsd:boolean' */
            enum xsd__boolean11 RuleSupport;
            /** Required element 'tt:AnalyticsModuleSupport' of XML schema type 'xsd:boolean' */
            enum xsd__boolean11 AnalyticsModuleSupport;
    };


    struct tt__DeviceCapabilities11 {
            /** Required element 'tt:XAddr' of XML schema type 'xsd:anyURI' */
            char *XAddr;
            /** Optional element 'tt:Network' of XML schema type 'tt:NetworkCapabilities' */
            struct tt__NetworkCapabilities11 *Network;
            /** Optional element 'tt:System' of XML schema type 'tt:SystemCapabilities' */
            struct tt__SystemCapabilities11 *System;
            /** Optional element 'tt:IO' of XML schema type 'tt:IOCapabilities' */
            struct tt__IOCapabilities11 *IO;
            /** Optional element 'tt:Security' of XML schema type 'tt:SecurityCapabilities' */
            struct tt__SecurityCapabilities11 *Security;
            /** Optional element 'tt:Extension' of XML schema type 'tt:DeviceCapabilitiesExtension' */
            struct tt__DeviceCapabilitiesExtension11 *Extension;
    };
       

        struct tt__NetworkCapabilities11 {
                /** Optional element 'tt:IPFilter' of XML schema type 'xsd:boolean' */
                enum xsd__boolean11 *IPFilter;
                /** Optional element 'tt:ZeroConfiguration' of XML schema type 'xsd:boolean' */
                enum xsd__boolean11 *ZeroConfiguration;
                /** Optional element 'tt:IPVersion6' of XML schema type 'xsd:boolean' */
                enum xsd__boolean11 *IPVersion6;
                /** Optional element 'tt:DynDNS' of XML schema type 'xsd:boolean' */
                enum xsd__boolean11 *DynDNS;
                /** Optional element 'tt:Extension' of XML schema type 'tt:NetworkCapabilitiesExtension' */
                struct tt__NetworkCapabilitiesExtension11 *Extension;
        };


            struct tt__NetworkCapabilitiesExtension11 {
                    /** Optional element 'tt:Dot11Configuration' of XML schema type 'xsd:boolean' */
                    enum xsd__boolean11 *Dot11Configuration;
                    /** Optional element 'tt:Extension' of XML schema type 'tt:NetworkCapabilitiesExtension2' */
                    struct tt__NetworkCapabilitiesExtension211 *Extension;
            };


                struct tt__NetworkCapabilitiesExtension211 {
                #ifdef WITH_NOEMPTYSTRUCT
                    char dummy;	/* empty struct is a GNU extension */
                #endif
                };


            struct tt__SystemCapabilities11 {
                    /** Required element 'tt:DiscoveryResolve' of XML schema type 'xsd:boolean' */
                    enum xsd__boolean11 DiscoveryResolve;
                    /** Required element 'tt:DiscoveryBye' of XML schema type 'xsd:boolean' */
                    enum xsd__boolean11 DiscoveryBye;
                    /** Required element 'tt:RemoteDiscovery' of XML schema type 'xsd:boolean' */
                    enum xsd__boolean11 RemoteDiscovery;
                    /** Required element 'tt:SystemBackup' of XML schema type 'xsd:boolean' */
                    enum xsd__boolean11 SystemBackup;
                    /** Required element 'tt:SystemLogging' of XML schema type 'xsd:boolean' */
                    enum xsd__boolean11 SystemLogging;
                    /** Required element 'tt:FirmwareUpgrade' of XML schema type 'xsd:boolean' */
                    enum xsd__boolean11 FirmwareUpgrade;
                    /** Sequence of at least 1 elements 'tt:SupportedVersions' of XML schema type 'tt:OnvifVersion' stored in dynamic array SupportedVersions of length __sizeSupportedVersions */
                    int __sizeSupportedVersions;
                    struct tt__OnvifVersion11 *SupportedVersions;
                    /** Optional element 'tt:Extension' of XML schema type 'tt:SystemCapabilitiesExtension' */
                    struct tt__SystemCapabilitiesExtension11 *Extension;
            };


                struct tt__SystemCapabilitiesExtension11 {
                        /** Optional element 'tt:HttpFirmwareUpgrade' of XML schema type 'xsd:boolean' */
                        enum xsd__boolean11 *HttpFirmwareUpgrade;
                        /** Optional element 'tt:HttpSystemBackup' of XML schema type 'xsd:boolean' */
                        enum xsd__boolean11 *HttpSystemBackup;
                        /** Optional element 'tt:HttpSystemLogging' of XML schema type 'xsd:boolean' */
                        enum xsd__boolean11 *HttpSystemLogging;
                        /** Optional element 'tt:HttpSupportInformation' of XML schema type 'xsd:boolean' */
                        enum xsd__boolean11 *HttpSupportInformation;
                        /** Optional element 'tt:Extension' of XML schema type 'tt:SystemCapabilitiesExtension2' */
                        struct tt__SystemCapabilitiesExtension211 *Extension;
                };


                    struct tt__SystemCapabilitiesExtension211 {
                    #ifdef WITH_NOEMPTYSTRUCT
                        char dummy;	/* empty struct is a GNU extension */
                    #endif
                    };


        struct tt__IOCapabilities11 {
                /** Optional element 'tt:InputConnectors' of XML schema type 'xsd:int' */
                int *InputConnectors;
                /** Optional element 'tt:RelayOutputs' of XML schema type 'xsd:int' */
                int *RelayOutputs;
                /** Optional element 'tt:Extension' of XML schema type 'tt:IOCapabilitiesExtension' */
                struct tt__IOCapabilitiesExtension11 *Extension;
        };


            struct tt__IOCapabilitiesExtension11 {
                    /** Optional element 'tt:Auxiliary' of XML schema type 'xsd:boolean' */
                    enum xsd__boolean11 *Auxiliary;
                    /** Sequence of elements 'tt:AuxiliaryCommands' of XML schema type 'tt:AuxiliaryData' stored in dynamic array AuxiliaryCommands of length __sizeAuxiliaryCommands */
                    int __sizeAuxiliaryCommands;
                    char **AuxiliaryCommands;
                    /** Required element 'tt:Extension' of XML schema type 'tt:IOCapabilitiesExtension2' */
                    struct tt__IOCapabilitiesExtension211 *Extension;
            };


                struct tt__IOCapabilitiesExtension211 {
                #ifdef WITH_NOEMPTYSTRUCT
                    char dummy;	/* empty struct is a GNU extension */
                #endif
                };


        struct tt__SecurityCapabilities11 {
                /** Required element 'tt:TLS1.1' of XML schema type 'xsd:boolean' */
                enum xsd__boolean11 TLS1_x002e1;
                /** Required element 'tt:TLS1.2' of XML schema type 'xsd:boolean' */
                enum xsd__boolean11 TLS1_x002e2;
                /** Required element 'tt:OnboardKeyGeneration' of XML schema type 'xsd:boolean' */
                enum xsd__boolean11 OnboardKeyGeneration;
                /** Required element 'tt:AccessPolicyConfig' of XML schema type 'xsd:boolean' */
                enum xsd__boolean11 AccessPolicyConfig;
                /** Required element 'tt:X.509Token' of XML schema type 'xsd:boolean' */
                enum xsd__boolean11 X_x002e509Token;
                /** Required element 'tt:SAMLToken' of XML schema type 'xsd:boolean' */
                enum xsd__boolean11 SAMLToken;
                /** Required element 'tt:KerberosToken' of XML schema type 'xsd:boolean' */
                enum xsd__boolean11 KerberosToken;
                /** Required element 'tt:RELToken' of XML schema type 'xsd:boolean' */
                enum xsd__boolean11 RELToken;
                /** Optional element 'tt:Extension' of XML schema type 'tt:SecurityCapabilitiesExtension' */
                struct tt__SecurityCapabilitiesExtension11 *Extension;
        };


            struct tt__SecurityCapabilitiesExtension11 {
                    /** Required element 'tt:TLS1.0' of XML schema type 'xsd:boolean' */
                    enum xsd__boolean11 TLS1_x002e0;
                    /** Optional element 'tt:Extension' of XML schema type 'tt:SecurityCapabilitiesExtension2' */
                    struct tt__SecurityCapabilitiesExtension211 *Extension;
            };


                struct tt__SecurityCapabilitiesExtension211 {
                        /** Required element 'tt:Dot1X' of XML schema type 'xsd:boolean' */
                        enum xsd__boolean11 Dot1X;
                        /** Sequence of elements 'tt:SupportedEAPMethod' of XML schema type 'xsd:int' stored in dynamic array SupportedEAPMethod of length __sizeSupportedEAPMethod */
                        int __sizeSupportedEAPMethod;
                        int *SupportedEAPMethod;
                        /** Required element 'tt:RemoteUserHandling' of XML schema type 'xsd:boolean' */
                        enum xsd__boolean11 RemoteUserHandling;
                };


        struct tt__DeviceCapabilitiesExtension11 {
        #ifdef WITH_NOEMPTYSTRUCT
            char dummy;	/* empty struct is a GNU extension */
        #endif
        };


    struct tt__EventCapabilities11 {
            /** Required element 'tt:XAddr' of XML schema type 'xsd:anyURI' */
            char *XAddr;
            /** Required element 'tt:WSSubscriptionPolicySupport' of XML schema type 'xsd:boolean' */
            enum xsd__boolean11 WSSubscriptionPolicySupport;
            /** Required element 'tt:WSPullPointSupport' of XML schema type 'xsd:boolean' */
            enum xsd__boolean11 WSPullPointSupport;
            /** Required element 'tt:WSPausableSubscriptionManagerInterfaceSupport' of XML schema type 'xsd:boolean' */
            enum xsd__boolean11 WSPausableSubscriptionManagerInterfaceSupport;
    };


    struct tt__ImagingCapabilities11 {
            /** Required element 'tt:XAddr' of XML schema type 'xsd:anyURI' */
            char *XAddr;
    };


    struct tt__MediaCapabilities11 {
            /** Required element 'tt:XAddr' of XML schema type 'xsd:anyURI' */
            char *XAddr;
            /** Required element 'tt:StreamingCapabilities' of XML schema type 'tt:RealTimeStreamingCapabilities' */
            struct tt__RealTimeStreamingCapabilities11 *StreamingCapabilities;
            /** Optional element 'tt:Extension' of XML schema type 'tt:MediaCapabilitiesExtension' */
            struct tt__MediaCapabilitiesExtension11 *Extension;
    };


        struct tt__RealTimeStreamingCapabilities11 {
                /** Optional element 'tt:RTPMulticast' of XML schema type 'xsd:boolean' */
                enum xsd__boolean11 *RTPMulticast;
                /** Optional element 'tt:RTP_TCP' of XML schema type 'xsd:boolean' */
                enum xsd__boolean11 *RTP_USCORETCP;
                /** Optional element 'tt:RTP_RTSP_TCP' of XML schema type 'xsd:boolean' */
                enum xsd__boolean11 *RTP_USCORERTSP_USCORETCP;
                /** Optional element 'tt:Extension' of XML schema type 'tt:RealTimeStreamingCapabilitiesExtension' */
                struct tt__RealTimeStreamingCapabilitiesExtension11 *Extension;
        };


            struct tt__RealTimeStreamingCapabilitiesExtension11 {
            #ifdef WITH_NOEMPTYSTRUCT
                char dummy;	/* empty struct is a GNU extension */
            #endif
            };


        struct tt__MediaCapabilitiesExtension11 {
                /** Required element 'tt:ProfileCapabilities' of XML schema type 'tt:ProfileCapabilities' */
                struct tt__ProfileCapabilities11 *ProfileCapabilities;
        };


            struct tt__ProfileCapabilities11 {
                    /** Required element 'tt:MaximumNumberOfProfiles' of XML schema type 'xsd:int' */
                    int MaximumNumberOfProfiles;
            };


    struct tt__PTZCapabilities11 {
            /** Required element 'tt:XAddr' of XML schema type 'xsd:anyURI' */
            char *XAddr;
    };


    struct tt__CapabilitiesExtension11 {
            /** Optional element 'tt:DeviceIO' of XML schema type 'tt:DeviceIOCapabilities' */
            struct tt__DeviceIOCapabilities11 *DeviceIO;
            /** Optional element 'tt:Display' of XML schema type 'tt:DisplayCapabilities' */
            struct tt__DisplayCapabilities11 *Display;
            /** Optional element 'tt:Recording' of XML schema type 'tt:RecordingCapabilities' */
            struct tt__RecordingCapabilities11 *Recording;
            /** Optional element 'tt:Search' of XML schema type 'tt:SearchCapabilities' */
            struct tt__SearchCapabilities11 *Search;
            /** Optional element 'tt:Replay' of XML schema type 'tt:ReplayCapabilities' */
            struct tt__ReplayCapabilities11 *Replay;
            /** Optional element 'tt:Receiver' of XML schema type 'tt:ReceiverCapabilities' */
            struct tt__ReceiverCapabilities11 *Receiver;
            /** Optional element 'tt:AnalyticsDevice' of XML schema type 'tt:AnalyticsDeviceCapabilities' */
            struct tt__AnalyticsDeviceCapabilities11 *AnalyticsDevice;
            /** Optional element 'tt:Extensions' of XML schema type 'tt:CapabilitiesExtension2' */
            struct tt__CapabilitiesExtension211 *Extensions;
    };


        struct tt__DeviceIOCapabilities11 {
                /** Required element 'tt:XAddr' of XML schema type 'xsd:anyURI' */
                char *XAddr;
                /** Required element 'tt:VideoSources' of XML schema type 'xsd:int' */
                int VideoSources;
                /** Required element 'tt:VideoOutputs' of XML schema type 'xsd:int' */
                int VideoOutputs;
                /** Required element 'tt:AudioSources' of XML schema type 'xsd:int' */
                int AudioSources;
                /** Required element 'tt:AudioOutputs' of XML schema type 'xsd:int' */
                int AudioOutputs;
                /** Required element 'tt:RelayOutputs' of XML schema type 'xsd:int' */
                int RelayOutputs;
        };


        struct tt__DisplayCapabilities11 {
                /** Required element 'tt:XAddr' of XML schema type 'xsd:anyURI' */
                char *XAddr;
                /** Required element 'tt:FixedLayout' of XML schema type 'xsd:boolean' */
                enum xsd__boolean11 FixedLayout;
        };


        struct tt__RecordingCapabilities11 {
                /** Required element 'tt:XAddr' of XML schema type 'xsd:anyURI' */
                char *XAddr;
                /** Required element 'tt:ReceiverSource' of XML schema type 'xsd:boolean' */
                enum xsd__boolean11 ReceiverSource;
                /** Required element 'tt:MediaProfileSource' of XML schema type 'xsd:boolean' */
                enum xsd__boolean11 MediaProfileSource;
                /** Required element 'tt:DynamicRecordings' of XML schema type 'xsd:boolean' */
                enum xsd__boolean11 DynamicRecordings;
                /** Required element 'tt:DynamicTracks' of XML schema type 'xsd:boolean' */
                enum xsd__boolean11 DynamicTracks;
                /** Required element 'tt:MaxStringLength' of XML schema type 'xsd:int' */
                int MaxStringLength;
        };


        struct tt__SearchCapabilities11 {
                /** Required element 'tt:XAddr' of XML schema type 'xsd:anyURI' */
                char *XAddr;
                /** Required element 'tt:MetadataSearch' of XML schema type 'xsd:boolean' */
                enum xsd__boolean11 MetadataSearch;
        };


        struct tt__ReplayCapabilities11 {
                /** Required element 'tt:XAddr' of XML schema type 'xsd:anyURI' */
                char *XAddr;
        };


        struct tt__ReceiverCapabilities11 {
                /** Required element 'tt:XAddr' of XML schema type 'xsd:anyURI' */
                char *XAddr;
                /** Required element 'tt:RTP_Multicast' of XML schema type 'xsd:boolean' */
                enum xsd__boolean11 RTP_USCOREMulticast;
                /** Required element 'tt:RTP_TCP' of XML schema type 'xsd:boolean' */
                enum xsd__boolean11 RTP_USCORETCP;
                /** Required element 'tt:RTP_RTSP_TCP' of XML schema type 'xsd:boolean' */
                enum xsd__boolean11 RTP_USCORERTSP_USCORETCP;
                /** Required element 'tt:SupportedReceivers' of XML schema type 'xsd:int' */
                int SupportedReceivers;
                /** Required element 'tt:MaximumRTSPURILength' of XML schema type 'xsd:int' */
                int MaximumRTSPURILength;
        };


        struct tt__AnalyticsDeviceCapabilities11 {
                /** Required element 'tt:XAddr' of XML schema type 'xsd:anyURI' */
                char *XAddr;
                /** Optional element 'tt:RuleSupport' of XML schema type 'xsd:boolean' */
                enum xsd__boolean11 *RuleSupport;
                /** Optional element 'tt:Extension' of XML schema type 'tt:AnalyticsDeviceExtension' */
                struct tt__AnalyticsDeviceExtension11 *Extension;
        };


            struct tt__AnalyticsDeviceExtension11 {
            #ifdef WITH_NOEMPTYSTRUCT
                char dummy;	/* empty struct is a GNU extension */
            #endif
            };


        struct tt__CapabilitiesExtension211 {
        #ifdef WITH_NOEMPTYSTRUCT
            char dummy;	/* empty struct is a GNU extension */
        #endif
        };


void get_capabilities(char* xaddrs, capabilities_model* cap, char* username, char* passwd);

void get_PTZ(char* xaddrs, char* ptzcap, char* username, char* passwd, int* result11);