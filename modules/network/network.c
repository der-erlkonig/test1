/**
 * @file modules/network/network.c
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
                num++;
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
 * @param[char*]      msg:The message
 */
void sendGlobalMessage(char* msg){
    //init
    int client = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in receiver;
    //settings
    receiver.sin_family = AF_INET;
    receiver.sin_port = htons(BROADCAST_PORT);
    receiver.sin_addr.s_addr = inet_addr(BROADCAST_ADDR);
    bzero(&(receiver.sin_zero), 8);

    //here we go
    sendto(client, msg, strlen(msg), MSG_NOSIGNAL, (struct sockaddr*)&receiver, (socklen_t)sizeof(receiver));
    close(client);
}

/**
 * @brief      Sends an unicast message via TCP, note that it is blocked.
 * @param[char*]      addr:The address
 * @param[int]  port  The port
 * @param[char*]      msg:The message
 */
void sendUnicastMessage(char* addr, int port, char* msg){
    
    //init
    int client = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in receiver;
    //settings
    receiver.sin_family = AF_INET;
    receiver.sin_port = htons(port);
    receiver.sin_addr.s_addr = inet_addr(addr);
    bzero(&(receiver.sin_zero), 8);

    //here we go
    connect(client, (struct sockaddr*)&receiver, (socklen_t)sizeof(receiver));
    send(client, msg, strlen(msg), MSG_NOSIGNAL);
    close(client);
}

/**
 * @brief      receive n lines of messages via TCP
 * @param[char**]      msgs:The messages
 * @param[unsigned int]  n      number of lines
 */
void recvnUnicastMessage(char** msgs, unsigned int n){
    int i = 0;
    int server = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sender;
    sender.sin_family = AF_INET;
    sender.sin_port = htons(LISTEN_PORT);
    sender.sin_addr.s_addr = inet_addr(LISTEN_ADDR);
    bzero(&(sender.sin_zero), 8);
    bind(server, (struct sockaddr*)&sender, sizeof(sender));
    listen(server, MAX_CLIENTS);
    int len = sizeof(sender);
    while(i < n){
        int cSocket = accept(server, (struct sockaddr*)&sender, (socklen_t*)&len);
        recv(cSocket, msgs[i], sizeof(msgs[i]) - 1, 0);
        i++;
        close(cSocket);
    }
    close(server);
}

/**
 * @brief      receive n lines of messages via UDP
 * @param[char**]      msgs:The messages
 * @param[unsigned int]  n      number of lines
 */
void recvnGlobalMessage(char** msgs, unsigned int n){
    int i = 0;
    int server = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in sender;
    sender.sin_family = AF_INET;
    sender.sin_port = htons(LISTEN_PORT);
    sender.sin_addr.s_addr = inet_addr(LISTEN_ADDR);
    bzero(&(sender.sin_zero), 8);
    bind(server, (struct sockaddr*)&sender, sizeof(sender));
    int len = sizeof(sender);
    while(i < n){
        recvfrom(server, msgs[i], sizeof(msgs[i]) - 1, 0, (struct sockaddr*)&sender, (socklen_t*)&len);
        i++;
    }
    close(server);
}
