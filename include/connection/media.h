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