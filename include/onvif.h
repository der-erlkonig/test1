/**
 * @file       include/onvif.h
 * @brief      includes all interfaces of this module.
 * @author     Ji Xiangyu
 * @date       2021.9.11
 * @version    0.0.2
 */

#pragma once
#include "connection/discovery.h"
#include "connection/ptz.h"
#include "connection/media.h"
#include "connection/device.h"
// please uncomment this include command, compile and link source files in the deprecated folder with your library if needed.
// But some dependencies has been destroyed, so you need to repair them before installing.
// #include "management/camera_pool.h"
#include "management/manage.h"