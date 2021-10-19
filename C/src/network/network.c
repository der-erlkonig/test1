/**
 * @file C/src/network/network.c
 * @brief      network module.
 * @version    0.0.2
 * @author     Ji Xiangyu
 * @date       2021.10.19
 */

/**
 * @brief      Gets all local address.
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