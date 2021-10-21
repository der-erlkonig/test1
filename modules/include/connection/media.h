/**
 * @file modules/include/connection/media.h
 * @brief      methods for snap(also include some media unified methods).
 * @version    0.0.1-dev
 * @author     Ji Xiangyu
 * @date       2021.9.13
 */
#pragma once
#include "common.h"

/**
 * @defgroup   media
 * @brief onvif media support methods
 * @{
 */

/**
 * @defgroup   media_exported_methods
 * @brief      onvif media exported methods
 * @{
 */
/**
 * @defgroup   media_exported_methods_media
 * @brief      onvif media exported methods, specific for basic media methods
 * @{
 */
void getProfile(char*, char*, char*, char*);
/**
 * @}
 */
/**
 * @defgroup   media_exported_methods_stream
 * @brief      onvif media exported methods, specific for stream-related methods
 * @{
 */
void getSnapshotUri(char*, char*, char*, char*, char*);
void getStreamUri(char*, char*, char*, char*, char*);
void getSnapshot(char*, char*, char*, char*);
/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */
