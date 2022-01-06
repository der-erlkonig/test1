/**
 * @file modules/network/network.c
 * @brief      network module.
 * @version    0.0.2
 * @author     Ji Xiangyu
 * @date       2021.10.19
 */
#include "network.h"
#include "onvif_lib.h"
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>

#define BROADCAST_ADDR "255.255.255.255"/*!< broadcast address */
#define BROADCAST_PORT 11111/*!< broadcast port */
#define LISTEN_ADDR "0.0.0.0"/*!< listening address */
#define LISTEN_PORT 11111/*!< listening port */
#define MAX_CLIENTS 30/*!< maximum number of clients */

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
