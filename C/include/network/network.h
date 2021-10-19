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


int getLocalAddress(char**);