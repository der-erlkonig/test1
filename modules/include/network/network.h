/**
 * @file modules/include/network/network.h
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
#define LISTEN_ADDR "0.0.0.0"/*!< listening address */
#define LISTEN_PORT 11111/*!< listening port */
#define MAX_CLIENTS 30/*!< maximum number of clients */
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
void sendUnicastMessage(char*, int, char*);
void recvnUnicastMessage(char**, unsigned int);
void recvnGlobalMessage(char**, unsigned int);
/**
 * @}
 */

/**
 * @}
 */
