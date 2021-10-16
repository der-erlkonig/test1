/**
 * @file C/include/ptz/ptz.h
 * @brief      Basic methods of ptz.
 * @version    0.0.1-dev
 * @author     Ji Xiangyu
 * @date       2021.9.15
 */
#pragma once
#include "common.h"

/**
 * @defgroup   ptz
 * @brief module that controls ptz
 * @{
 */
/**
 * @defgroup   ptz_Exported_Methods
 * @brief      exported methods of ptz
 * @{
 */
void absoluteMove(char*, char*, char*, char*, float, float, float);
void continuousMove(char*, char*, char*, char*, float, float, float, char*);
void stop(char*, char*, char*, char*);
/**
 * @}
 */
/**
 * @}
 */
