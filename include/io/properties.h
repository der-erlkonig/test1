/**
 * @file include/io/properties.h
 * @brief      This file implements properties.
 * @version    0.0.2
 * @author     Ji Xiangyu
 * @date       2022.1.14
 */
#pragma once

typedef struct Properties Properties;

Properties* readFromFile(char* path);
char* getConf(Properties* properties, char* key);
char** getKeys(Properties* properties);