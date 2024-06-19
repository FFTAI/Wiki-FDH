#pragma once

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

namespace HandSocket
{
    namespace Transmit
    {
        class UDPSocket
        {
        public:
            UDPSocket(std::string ip, uint16_t remote_port);
            ~UDPSocket();
            int SendData(std::vector<uint8_t> &send_data);
            int ReceiveData(std::string &rec_ptr);
            int sfd;
            char *ip_ = new char[16];
            struct sockaddr_in ser_addr_;
        };
    } // namespace Transmit
}