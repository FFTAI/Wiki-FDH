#include "../include/HandSocket.h"
#include "../include/HandResult.h"

#define MAX_SEND_SIZE 1024
#define MAX_RECV_SIZE 1024

using namespace HandSocket::Transmit;

UDPSocket::UDPSocket(std::string ip, uint16_t remote_port)
{

    strcpy(ip_, ip.c_str());
    ser_addr_.sin_family = AF_INET;
    ser_addr_.sin_addr.s_addr = inet_addr(ip_);
    ser_addr_.sin_port = htons(remote_port);
    sfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct timeval timeout;
    timeout.tv_sec = 1 / 1000;
    timeout.tv_usec = (1 % 1000) * 1000;
    setsockopt(sfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
}

UDPSocket::~UDPSocket() { close(sfd); }

int UDPSocket::SendData(std::vector<uint8_t> &send_data)
{
    char sendbuffer[1024-8] {0}; // -8: send buffer + hand/tail(8 bits)
    memset(sendbuffer, '\0', sizeof(sendbuffer));
    memcpy(sendbuffer, send_data.data(), send_data.size());
    int ret;
    ret = sendto(sfd, sendbuffer, sizeof(sendbuffer), 0, (struct sockaddr *)&ser_addr_, sizeof(ser_addr_));
    if (ret < 0)
    {
        return HandSocket::ResultCode::SOCKET_SEND_FAILED;
    }
    if (ret != sizeof(sendbuffer))
    {
        return HandSocket::ResultCode::SOCKET_SEND_SIZE_WRONG;
    }
    return HandSocket::ResultCode::SUCCESS;
}

int UDPSocket::ReceiveData(std::string &rec_ptr)
{
    char buff[1024];
    memset(buff, '\0', sizeof(buff));
    int ret;
    socklen_t addrlen = sizeof(ser_addr_);
    ret = recvfrom(sfd, &buff, 1024, MSG_DONTWAIT, (struct sockaddr *)&ser_addr_, &addrlen);
    if (ret <= 0)
    {
        return HandSocket::ResultCode::SOCKET_RECEIVE_FAILED;
    }
    else
    {
        rec_ptr = buff;
    }
    return HandSocket::ResultCode::SUCCESS;
}
