/**
 *  2024.7.4
 * Gedit by fourier intelligent
 *
 */

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
/**
 * @brief namespace for transmit
 */

    namespace Transmit
    {
    /**
     * @brief udp socket send and receive, use udp port 2333 and 2334, control: 2333, feedback: 2334
     */

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