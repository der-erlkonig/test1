/**
 * @file       include/management/manage.h
 * @brief      host cluster management.
 * @version    0.0.2
 * @author     Ji Xiangyu
 * @date       2021.10.5
 */
#pragma once

/**
 * @typedef PTZ_State
 * @struct  PTZ_State
 * @brief   record the current state of ptz camera
 */
typedef struct PTZ_State PTZ_State;

/**
 * @typedef Message
 * @struct  Message
 * @brief   hosts' heartbeat message structure  
 */
typedef struct Message Message;

/**
 * @typedef Host
 * @struct Host
 * @brief  host image of current computer
 */
typedef struct Host Host;

/**
 * @typedef Cluster
 * @brief   cluster entity
 */
typedef Host* Cluster;
