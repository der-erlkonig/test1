/**
 * @file modules/include/connection/media.h
 * @brief      methods for snap(also include some media unified methods).
 * @version    0.0.1-dev
 * @author     Ji Xiangyu
 * @date       2021.9.13
 */
#pragma once
#include "onvif_common.h"

void getProfile(char*, char*, char*, char*);
void getSnapshotUri(char*, char*, char*, char*, char*);
void getStreamUri(char*, char*, char*, char*, char*);
void getSnapshot(char*, char*, char*, char*);