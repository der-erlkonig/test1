/**
 * @file modules/include/connection/device.h
 * @brief      methods for basic device information.
 * @version    0.0.1-dev
 * @author     Ji Xiangyu
 * @date       2021.9.13
 */
#pragma once
#include "onvif_common.h"

/**
 * @typedef device_info
 * @struct device_info
 * @brief copy of gsoap device infomation for easy usage
 */
typedef struct {
	int valid;/*!< valib bit to check state */
	char *Manufacturer;/*!< device manufacturer */
	char *Model;/*!< device model */
	char *FirmwareVersion;/*!< device firmware version */
	char *SerialNumber;/*!< device serial number */
	char *HardwareId;/*!< device hardware ID */
} device_info;

/**
 * @brief      Gets the device information.
 * @param[in]  xaddr    The xaddr(media service address)
 * @param[out] info     The information storage pointer
 * @param[in]  username username
 * @param[in]  passwd   passwd
 * @see        device_info
 */
void get_device_information(char* xaddr, device_info* info, char* username, char* passwd);