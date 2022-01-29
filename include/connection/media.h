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
typedef struct{
    int valid;
    /** Optional element 'tt:Analytics' of XML schema type 'tt:AnalyticsCapabilities' */
    struct tt__AnalyticsCapabilities *Analytics;            
    /** Optional element 'tt:Device' of XML schema type 'tt:DeviceCapabilities' */
    struct tt__DeviceCapabilities *Device;
    /** Optional element 'tt:Events' of XML schema type 'tt:EventCapabilities' */
    struct tt__EventCapabilities *Events;
    /** Optional element 'tt:Imaging' of XML schema type 'tt:ImagingCapabilities' */
    struct tt__ImagingCapabilities *Imaging;
    /** Optional element 'tt:Media' of XML schema type 'tt:MediaCapabilities' */
    struct tt__MediaCapabilities *Media;
    /** Optional element 'tt:PTZ' of XML schema type 'tt:PTZCapabilities' */
    struct tt__PTZCapabilities *PTZ;
    /** Optional element 'tt:Extension' of XML schema type 'tt:CapabilitiesExtension' */
    struct tt__CapabilitiesExtension *Extension;
} capabilities_model;


void get_capabilities(char* xaddrs, capabilities_model* cap, char* username, char* passwd);