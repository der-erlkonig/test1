/**
 * @file include/io/properties.h
 * @brief      This file implements properties.
 * @version    0.0.2
 * @author     Ji Xiangyu
 * @date       2022.1.14
 */
#pragma once

/**
 * @typedef Properties
 * @struct  Properties
 * @brief   Properties entity
 */
typedef struct Properties Properties;

/**
 * @brief      Reads a properties configuration from file.
 * @param[in]  path  The file path
 * @return     Properties instance, which is the image of the actual file.
 * @par        Notice
 *             Note that there is not a manager embedded, so each call of reading will create a new Properties instance.
 *             And considering that configuration files only needs to be loaded once, the effciency is not tested specifically.
 * @par        Memory Management
 *             Caller is responsible for memory management.
 *             Please release the memory incase of leak.
 */
Properties* readPropertiesFromFile(char* path);
/**
 * @brief      Gets the properties config entry.
 * @param[in]  properties  The properties
 * @param[in]  key         The key
 * @return     The properties config entry.
 */
char* getPropertiesConf(Properties* properties, char* key);
/**
 * @brief      Gets the properties keys.
 * @param[in]  properties  The properties
 * @param[out] keys        The properties keys array.
 * @return     number of keys
 */
int getPropertiesKeys(Properties* properties, char** keys);
/**
 * @brief      delete properties
 * @param[in]  properties  The properties
 */
void deleteProperties(Properties * properties);