/**
 * @file C/include/network/network.h
 * @brief      Network communication.
 * @version    0.0.2
 * @author     Ji Xiangyu
 * @date       2021.10.19
 */

#pragma once
#include "lib.h"
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>

/**
 * @defgroup   Network
 * @brief      network communication
 * @{
 */
/**
 * @defgroup   Network_Constant
 * @brief      constant used by communication
 * @{
 */
#define BROADCAST_ADDR "255.255.255.255"/*!< broadcast address */
#define BROADCAST_PORT 11111/*!< broadcast port */
/**
 * @}
 */
/**
 * @defgroup   Network_Exported_Method
 * @brief      exported methods of network
 * @{
 */
int getLocalAddress(char**);
void sendGlobalMessage(char*);
/**
 * @}
 */

/**
 * @}
 */
