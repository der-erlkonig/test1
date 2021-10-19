/**
 * @file C/src/network/network.c
 * @brief      network module.
 * @version    0.0.2
 * @author     Ji Xiangyu
 * @date       2021.10.19
 */
#include "network/network.h"
/**
 * @brief      Gets all local addresses.
 * @param[char**]      addrs:The addresses buffer.
 * @return      number
 * @retval      int number of addresses
 */
int getLocalAddress(char** addrs){
    struct ifaddrs *ifaddr, *ifa;
    int num = 0;
    if(getifaddrs(&ifaddr) != -1){
        for(ifa = ifaddr; ifa != NULL;ifa = ifa -> ifa_next){
            if(ifa -> ifa_addr->sa_family == AF_INET){
                strcpy(addrs[num], inet_ntoa(((struct sockaddr_in*)ifa -> ifa_addr) -> sin_addr));
                i++;
            }
        }
        freeifaddrs(ifaddr);
    }
    return num;
}

/**
 * @brief      Sends a global message via broadcast.
 * @details    This is a wrapper of traditional socket
 *             communication, packaging the burdersome
 *             steps. Subjected to its type, we use UDP
 *             to send and receive, so it is non-blocked
 *             method.
 * @param      msg   The message
 */
void sendGlobalMessage(char* msg){
    int client = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in receiver;
    //settings
    receiver.sin_family = AF_INET;
    receiver.sin_port = htons(BROADCAST_PORT);
    receiver.sin_addr.s_addr = inet_addr(BROADCAST_ADDR);
    bzero(&(receiver.sin_zero), 8);

    //here we go
    connect(client, (struct sockaddr*)&receiver, sizeof(receiver));
    send(client, msg, strlen(msg), MSG_NOSIGNAL);
}
