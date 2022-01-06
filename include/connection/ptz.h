/**
 * @file       include/connection/ptz.h
 * @brief      Basic methods of ptz.
 * @version    0.0.1-dev
 * @author     Ji Xiangyu
 * @date       2021.9.15
 */
#pragma once

/**
 * @brief     execute absolute move
 * @param[in] xaddrs   The media service address
 * @param[in] token    The token
 * @param[in] username The username
 * @param[in] passwd   The password
 * @param[in] pan      The pan
 * @param[in] tilt     The tilt
 * @param[in] zoom     The zoom
 */
void absoluteMove(char* xaddrs, char* token, char* username, char* passwd, float pan, float tilt, float zoom);

/**
 * @brief      perform continuous move
 * @param[in]  xaddrs   The media service address
 * @param[in]  token    The token
 * @param[in]  username The username
 * @param[in]  passwd   The password
 * @param[in]  pan      The pan
 * @param[in]  tilt     The tilt
 * @param[in]  zoom     The zoom
 * @param[in]  timeout  The timeout, NULL if not needed.
 * @note       please set one direction at once for correctness
 */
void continuousMove(char* xaddrs, char* token, char* username, char* passwd, float pan, float tilt, float zoom, char* timeout);

/**
 * @brief     stop move
 * @param[in] xaddrs   The media service address
 * @param[in] token    The token
 * @param[in] username The username
 * @param[in] passwd   The password
 */
void stop(char* xaddrs, char* token, char* username, char* passwd);