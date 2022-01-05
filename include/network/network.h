/**
 * @file       include/network/network.h
 * @brief      Network communication.
 * @version    0.0.2
 * @author     Ji Xiangyu
 * @date       2021.10.19
 */

#pragma once

/**
 * @brief      Gets all local addresses.
 * @param[out]  addrs The addresses buffer.
 * @return      number of addresses
 */
int getLocalAddress(char** addrs);

/**
 * @brief      Sends a global message via broadcast.
 * @details    This is a wrapper of traditional socket
 *             communication, packaging the burdersome
 *             steps. Subjected to its type, we use UDP
 *             to send and receive, so it is non-blocked
 *             method.
 * @param[in]  msg The message
 */
void sendGlobalMessage(char* msg);

/**
 * @brief      Sends an unicast message via TCP, note that it is blocked.
 * @param[in]   addr The address
 * @param[in]   port The port
 * @param[in]   msg  The message
 */
void sendUnicastMessage(char* addr, int port, char* msg);

/**
 * @brief      receive n lines of messages via TCP
 * @param[out]      msgs The messages
 * @param[in]       n    number of lines
 */
void recvnUnicastMessage(char** msgs, unsigned int n);

/**
 * @brief      receive n lines of messages via UDP
 * @param[out] msgs The messages
 * @param[in]  n    number of lines
 */
void recvnGlobalMessage(char** msgs, unsigned int n);