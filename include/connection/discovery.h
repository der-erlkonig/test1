/**
 * @file       include/connection/discovery.h
 * @brief      definition of remote discovery
 * @author     Ji Xiangyu
 * @date       2021.9.11
 * @version    0.0.1-dev
 */
#pragma once

/**
 * @brief      detect IPCs, via multicast
 * @param[out] xaddrs array of strings that is used to store the address of IPC
 * @return     number of IPC detected
 */
int detect_device(char** xaddrs);