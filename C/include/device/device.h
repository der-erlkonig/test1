/**
 * @file C/include/device/device.h
 * @brief      methods for basic device information.
 * @version    0.0.1-dev
 * @author     Ji Xiangyu
 * @date       2021.9.13
 */
#pragma once
#include "common.h"
/**
 * @defgroup   device
 * @brief      device basic infomation
 * @{
 */
/**
 * @defgroup   device_type
 * @brief      predefined device infomation structure
 * @{
 */
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
 * @}
 */

/**
 * @defgroup device_exported_methods
 * @brief      exported methods for device
 * @{
 */
void get_device_information(char*, device_info*, char*, char*);
/**
 * @}
 */
/**
 * @}
 */
