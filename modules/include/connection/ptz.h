/**
 * @file modules/include/connection/ptz.h
 * @brief      Basic methods of ptz.
 * @version    0.0.1-dev
 * @author     Ji Xiangyu
 * @date       2021.9.15
 */
#pragma once
#include "onvif_common.h"

void absoluteMove(char*, char*, char*, char*, float, float, float);
void continuousMove(char*, char*, char*, char*, float, float, float, char*);
void stop(char*, char*, char*, char*);