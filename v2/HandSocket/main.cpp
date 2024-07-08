#include "include/HandSocket.h"
#include <iostream>
#include <memory>
using namespace HandSocket;

int main()
{
    std::shared_ptr<Transmit::UDPSocket> ctrl_udp_socket;
    std::shared_ptr<Transmit::UDPSocket> comm_udp_socket;

    ctrl_udp_socket = std::make_shared<Transmit::UDPSocket>("192.168.137.39", 2333);
    comm_udp_socket = std::make_shared<Transmit::UDPSocket>("192.168.137.39", 2334);

    std::vector<uint8_t> get_cur, get_status;
    get_cur.push_back(4);
    get_status.push_back(5);

    while (1)
    {
        if (comm_udp_socket->SendData(get_cur) == 0)
        {
            std::string recv_data;
            int counts = 0;
            while (1)
            {
                if (comm_udp_socket->ReceiveData(recv_data) == 0)
                {
                    std::cout << "cur recv :" << recv_data << std::endl;
                    break;
                }
            }
        }
        else
        {
            std::cout << "send failed" << std::endl;
        }

        if (comm_udp_socket->SendData(get_status) == 0)
        {
            std::string recv_data;
            int counts = 0;
            while (1)
            {
                if (comm_udp_socket->ReceiveData(recv_data) == 0)
                {
                    std::cout << "status recv :" << recv_data << std::endl;
                    break;
                }
            }
        }
        else
        {
            std::cout << "send failed" << std::endl;
        }
    }

    return 0;
}