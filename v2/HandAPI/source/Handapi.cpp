/**
 *  2024.7.4
 * Gedit by fourier intelligent
 *
 */

#include <sstream>
#include "../include/Handapi.h"
#include "../include/HandapiFunctionResult.h"

#define DEBUG

using namespace HandSocket;
using namespace HandProtocol;

void Handapi::init(const std::string &ip)
{
    ip_ = ip;
    ctrl_udp_socket = std::make_shared<Transmit::UDPSocket>(ip, 2333);
    comm_udp_socket = std::make_shared<Transmit::UDPSocket>(ip, 2334);
}

int Handapi::calibration()
{
    int ret;
    std::vector<uint8_t> send_data;
    send_data.push_back(0x01);
    send_data.push_back(0x01);
    begin = std::chrono::steady_clock::now();

    while (1)
    {
        switch (calibration_flg)
        {
        case 0:
        {
            ret = ctrl_udp_socket->SendData(send_data);
            if (ret < 0)
            {
#ifdef DEBUG
                std::cout << "ctrl send data failed" << std::endl;
#endif // DEBUG
            }
            else
            {
                calibration_flg = 1;
            }
            break;
        }
        case 1:
        {
            //
            return APIResultCode::SUCCESS;
        }

        default:
            break;
        }
        end = std::chrono::steady_clock::now();
        int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        if (int_ms.count() > 1000)
        {
            if (calibration_flg)
            {
                std::cout << "DEVICE RECVFROM: " << ip_ << ", TIMEOUT" << std::endl;
            }
            else
            {
                std::cout << "DEVICE SENDTO: " << ip_ << ", TIMEOUT" << std::endl;
            }
            calibration_flg = 0;
            return APIResultCode::TIMEOUT;
        }
    }
    return APIResultCode::FAIL;
}

int Handapi::get_cnt(std::vector<long> &fdb)
{
    int ret;
    std::vector<uint8_t> send_data;
    send_data.push_back(0x01);
    begin = std::chrono::steady_clock::now();

    while (1)
    {
        switch (get_cnt_flg)
        {
        case 0:
        {
            ret = comm_udp_socket->SendData(send_data);
            if (ret < 0)
            {
#ifdef DEBUG
                std::cout << "ctrl send data failed" << std::endl;
#endif // DEBUG
            }
            else
            {
                get_cnt_flg = 1;
            }
            break;
        }
        case 1:
        {
            std::string recv_data;
            static uint32_t recv_counts = 0;
            ret = comm_udp_socket->ReceiveData(recv_data);
            if (ret < 0)
            {
                recv_counts++;
                if (recv_counts > wait_replt_counts_max)
                {
                    recv_counts = 0;
                    get_cnt_flg = 0;
                }
            }
            else
            {
                recv_counts = 0;
                std::istringstream iss(recv_data);
                std::string token;
                while (std::getline(iss, token, ' '))
                {
                    long num = 0.0;
                    std::istringstream(token) >> num;
                    fdb.push_back(num);
                }
                get_cnt_flg = 0;
                return APIResultCode::SUCCESS;
            }
        }
        default:
            break;
        }
        end = std::chrono::steady_clock::now();
        int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        if (int_ms.count() > 1000)
        {
            if (get_cnt_flg)
            {
                std::cout << "DEVICE RECVFROM: " << ip_ << ", TIMEOUT" << std::endl;
            }
            else
            {
                std::cout << "DEVICE SENDTO: " << ip_ << ", TIMEOUT" << std::endl;
            }
            get_cnt_flg = 0;
            return APIResultCode::TIMEOUT;
        }
    }
    return APIResultCode::FAIL;
}

// get sensor data
int Handapi::get_pos(std::vector<float> &fdb)
{
    int ret;
    std::vector<uint8_t> send_data;
    send_data.push_back(0x02);
    begin = std::chrono::steady_clock::now();

    while (1)
    {
        switch (get_pos_flg)
        {
        case 0:
        {
            ret = comm_udp_socket->SendData(send_data);
            if (ret < 0)
            {
#ifdef DEBUG
                std::cout << "ctrl send data failed" << std::endl;
#endif // DEBUG
            }
            else
            {
                get_pos_flg = 1;
            }
            break;
        }
        case 1:
        {
            std::string recv_data;
            static uint32_t recv_counts = 0;
            ret = comm_udp_socket->ReceiveData(recv_data);
            if (ret < 0)
            {
                recv_counts++;
                if (recv_counts > wait_replt_counts_max)
                {
                    recv_counts = 0;
                    get_pos_flg = 0;
                }

            }
            else
            {
                recv_counts = 0;
                std::istringstream iss(recv_data);
                std::string token;
                while (std::getline(iss, token, ' '))
                {
                    float num = 0.0;
                    std::istringstream(token) >> num;
                    fdb.push_back(num);
                }
                get_pos_flg = 0;
                return APIResultCode::SUCCESS;
            }
        }
        default:
            break;
        }
        end = std::chrono::steady_clock::now();
        int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        if (int_ms.count() > 1000)
        {
            if (get_pos_flg)
            {
                std::cout << "DEVICE RECVFROM: " << ip_ << ", TIMEOUT" << std::endl;
            }
            else
            {
                std::cout << "DEVICE SENDTO: " << ip_ << ", TIMEOUT" << std::endl;
            }
            get_pos_flg = 0;
            return APIResultCode::TIMEOUT;
        }
    }
    return APIResultCode::FAIL;
}

int Handapi::get_current(std::vector<float> &fdb)
{
    int ret;
    std::vector<uint8_t> send_data;
    send_data.push_back(0x04);
    begin = std::chrono::steady_clock::now();

    while (1)
    {
        switch (get_current_flg)
        {
        case 0:
        {
            ret = comm_udp_socket->SendData(send_data);
            if (ret < 0)
            {
#ifdef DEBUG
                std::cout << "ctrl send data failed" << std::endl;
#endif // DEBUG
            }
            else
            {
                get_current_flg = 1;
            }
            break;
        }
        case 1:
        {
            std::string recv_data;
            static uint32_t recv_counts = 0;
            ret = comm_udp_socket->ReceiveData(recv_data);
            if (ret < 0)
            {
                recv_counts++;
                if (recv_counts == wait_replt_counts_max)
                {
                    get_pos_flg = 0;
                    recv_counts = 0;
                }

            }
            else
            {
                std::istringstream iss(recv_data);
                std::string token;
                recv_counts = 0;
                while (std::getline(iss, token, ' '))
                {
                    float num = 0.0;
                    std::istringstream(token) >> num;
                    fdb.push_back(num);
                }
                get_current_flg = 0;
                return APIResultCode::SUCCESS;
            }
        }
        default:
            break;
        }
        end = std::chrono::steady_clock::now();
        int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        if (int_ms.count() > 1000)
        {
            if (get_current_flg)
            {
                std::cout << "DEVICE RECVFROM: " << ip_ << ", TIMEOUT" << std::endl;
            }
            else
            {
                std::cout << "DEVICE SENDTO: " << ip_ << ", TIMEOUT" << std::endl;
            }
            get_current_flg = 0;
            return APIResultCode::TIMEOUT;
        }
    }
    return APIResultCode::FAIL;
}

int Handapi::get_velocity(std::vector<float> &fdb)
{
    int ret;
    std::vector<uint8_t> send_data;
    send_data.push_back(0x03);
    begin = std::chrono::steady_clock::now();

    while (1)
    {
        switch (get_velocity_flg)
        {
        case 0:
        {
            ret = comm_udp_socket->SendData(send_data);
            if (ret < 0)
            {
#ifdef DEBUG
                std::cout << "ctrl send data failed" << std::endl;
#endif // DEBUG
            }
            else
            {
                get_velocity_flg = 1;
            }
            break;
        }
        case 1:
        {
            std::string recv_data;
            static uint32_t recv_counts = 0;
            ret = comm_udp_socket->ReceiveData(recv_data);
            if (ret < 0)
            {
                recv_counts++;
                if (recv_counts == wait_replt_counts_max)
                {
                    get_velocity_flg = 0;
                    recv_counts = 0;
                }

            }
            else
            {
                std::istringstream iss(recv_data);
                std::string token;
                recv_counts = 0;
                while (std::getline(iss, token, ' '))
                {
                    float num = 0.0;
                    std::istringstream(token) >> num;
                    fdb.push_back(num);
                }
                get_velocity_flg = 0;
                return APIResultCode::SUCCESS;
            }
        }

        default:
            break;
        }
        end = std::chrono::steady_clock::now();
        int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        if (int_ms.count() > 1000)
        {
            if (get_velocity_flg)
            {
                std::cout << "DEVICE RECVFROM: " << ip_ << ", TIMEOUT" << std::endl;
            }
            else
            {
                std::cout << "DEVICE SENDTO: " << ip_ << ", TIMEOUT" << std::endl;
            }
            get_velocity_flg = 0;
            return APIResultCode::TIMEOUT;
        }
    }
    return APIResultCode::FAIL;
}

int Handapi::get_errorcode(std::vector<long> &fdb)
{
    int ret;
    std::vector<uint8_t> send_data;
    send_data.push_back(0x06);
    begin = std::chrono::steady_clock::now();

    while (1)
    {
        switch (get_errorcode_flg)
        {
        case 0:
        {
            ret = comm_udp_socket->SendData(send_data);
            if (ret < 0)
            {
#ifdef DEBUG
                std::cout << "ctrl send data failed" << std::endl;
#endif // DEBUG
            }
            else
            {
                get_errorcode_flg = 1;
            }
            break;
        }
        case 1:
        {
            std::string recv_data;
            static uint32_t recv_counts = 0;
            ret = comm_udp_socket->ReceiveData(recv_data);
            if (ret < 0)
            {
                recv_counts++;
                if (recv_counts == wait_replt_counts_max)
                {
                    recv_counts = 0;
                    get_errorcode_flg = 0;
                }

            }
            else
            {
                recv_counts = 0;
                std::istringstream iss(recv_data);
                std::string token;
                while (std::getline(iss, token, ' '))
                {
                    long num = 0.0;
                    std::istringstream(token) >> num;
                    fdb.push_back(num);
                }
                get_errorcode_flg = 0;
                return APIResultCode::SUCCESS;
            }
        }

        default:
            break;
        }
        end = std::chrono::steady_clock::now();
        int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        if (int_ms.count() > 1000)
        {
            if (get_errorcode_flg)
            {
                std::cout << "DEVICE RECVFROM: " << ip_ << ", TIMEOUT" << std::endl;
            }
            else
            {
                std::cout << "DEVICE SENDTO: " << ip_ << ", TIMEOUT" << std::endl;
            }
            get_errorcode_flg = 0;
#ifdef DEBUG
            std::cout << "DEVICE: " << ip_ << ", TIMEOUT" << std::endl;
#endif // DEBUG
            return APIResultCode::TIMEOUT;
        }
    }
    return APIResultCode::FAIL;
}

int Handapi::get_status(std::vector<uint8_t> &fdb)
{
    int ret;
    std::vector<uint8_t> send_data;
    send_data.push_back(0x05);
    begin = std::chrono::steady_clock::now();

    while (1)
    {
        switch (get_status_flg)
        {
        case 0:
        {
            ret = comm_udp_socket->SendData(send_data);
            if (ret < 0)
            {
#ifdef DEBUG
                std::cout << "ctrl send data failed" << std::endl;
#endif // DEBUG
            }
            else
            {
                get_status_flg = 1;
            }
            break;
        }
        case 1:
        {
            std::string recv_data;
            static uint32_t recv_counts = 0;
            recv_counts++;
            ret = comm_udp_socket->ReceiveData(recv_data);
            if (ret < 0)
            {
                if (recv_counts == wait_replt_counts_max)
                {
                    recv_counts = 0;
                    get_status_flg = 0;
                }

            }
            else
            {
                std::istringstream iss(recv_data);
                std::string token;
                recv_counts = 0;
                while (std::getline(iss, token, ' '))
                {
                    int num = 0;
                    std::istringstream(token) >> num;
                    fdb.push_back(num);
                }
                get_status_flg = 0;
                return APIResultCode::SUCCESS;
            }
        }

        default:
            break;
        }

        end = std::chrono::steady_clock::now();
        int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        if (int_ms.count() > 1000)
        {
            if (get_status_flg)
            {
                std::cout << "DEVICE RECVFROM: " << ip_ << ", TIMEOUT" << std::endl;
            }
            else
            {
                std::cout << "DEVICE SENDTO: " << ip_ << ", TIMEOUT" << std::endl;
            }
            get_status_flg = 0;
            return APIResultCode::TIMEOUT;
        }
    }
    return APIResultCode::FAIL;
}

int Handapi::get_pos_limited(std::vector<float> &fdb)
{
    int ret;
    std::vector<uint8_t> send_data;
    send_data.push_back(0x0b);
    begin = std::chrono::steady_clock::now();

    while (1)
    {
        switch (get_pos_limited_flg)
        {
        case 0:
        {
            ret = comm_udp_socket->SendData(send_data);
            if (ret < 0)
            {
#ifdef DEBUG
                std::cout << "ctrl send data failed" << std::endl;
#endif // DEBUG
            }
            else
            {
                get_pos_limited_flg = 1;
            }
            break;
        }
        case 1:
        {
            static uint32_t recv_counts = 0;
            recv_counts++;
            std::string recv_data;
            ret = comm_udp_socket->ReceiveData(recv_data);
            if (ret < 0)
            {
                if (recv_counts == wait_replt_counts_max)
                {
                    recv_counts = 0;
                    get_pos_limited_flg = 0;
                }

            }
            else
            {
                std::istringstream iss(recv_data);
                std::string token;
                recv_counts = 0;
                while (std::getline(iss, token, ' '))
                {
                    float num = 0.0;
                    std::istringstream(token) >> num;
                    fdb.push_back(num);
                }
                get_pos_limited_flg = 0;
                return APIResultCode::SUCCESS;
            }
        }

        default:
            break;
        }
        end = std::chrono::steady_clock::now();
        int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        if (int_ms.count() > 1000)
        {
            if (get_pos_limited_flg)
            {
                std::cout << "DEVICE RECVFROM: " << ip_ << ", TIMEOUT" << std::endl;
            }
            else
            {
                std::cout << "DEVICE SENDTO: " << ip_ << ", TIMEOUT" << std::endl;
            }
            get_pos_limited_flg = 0;
            return APIResultCode::TIMEOUT;
        }
    }
    return APIResultCode::FAIL;
}

int Handapi::get_velocity_limited(std::vector<float> &fdb)
{
    int ret;
    std::vector<uint8_t> send_data;
    send_data.push_back(0x0c);
    begin = std::chrono::steady_clock::now();
    while (1)
    {
        switch (get_velocity_limited_flg)
        {
        case 0:
        {
            ret = comm_udp_socket->SendData(send_data);
            if (ret < 0)
            {
#ifdef DEBUG
                std::cout << "ctrl send data failed" << std::endl;
#endif // DEBUG
            }
            else
            {
                get_velocity_limited_flg = 1;
            }
            break;
        }
        case 1:
        {
            static uint32_t recv_counts = 0;
            recv_counts++;
            std::string recv_data;
            ret = comm_udp_socket->ReceiveData(recv_data);
            if (ret < 0)
            {
                if (recv_counts == wait_replt_counts_max)
                {
                    recv_counts = 0;
                    get_velocity_limited_flg = 0;
                }


            }
            else
            {
                recv_counts = 0;
                std::istringstream iss(recv_data);
                std::string token;
                while (std::getline(iss, token, ' '))
                {
                    float num = 0.0;
                    std::istringstream(token) >> num;
                    fdb.push_back(num);
                }
                get_velocity_limited_flg = 0;
                return APIResultCode::SUCCESS;
            }
        }

        default:
            break;
        }
        end = std::chrono::steady_clock::now();
        int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        if (int_ms.count() > 1000)
        {
            if (get_velocity_limited_flg)
            {
                std::cout << "DEVICE RECVFROM: " << ip_ << ", TIMEOUT" << std::endl;
            }
            else
            {
                std::cout << "DEVICE SENDTO: " << ip_ << ", TIMEOUT" << std::endl;
            }
            get_velocity_limited_flg = 0;
            return APIResultCode::TIMEOUT;
        }
    }
    return APIResultCode::FAIL;
}

int Handapi::get_current_limited(std::vector<float> &fdb)
{
    int ret;
    std::vector<uint8_t> send_data;
    send_data.push_back(0x0d);
    begin = std::chrono::steady_clock::now();

    while (1)
    {
        switch (get_current_limited_flg)
        {
        case 0:
        {
            ret = comm_udp_socket->SendData(send_data);
            if (ret < 0)
            {
#ifdef DEBUG
                std::cout << "ctrl send data failed" << std::endl;
#endif // DEBUG
            }
            else
            {
                get_current_limited_flg = 1;
            }
            break;
        }
        case 1:
        {
            static uint32_t recv_counts = 0;
            recv_counts++;
            std::string recv_data;
            ret = comm_udp_socket->ReceiveData(recv_data);
            if (ret < 0)
            {
                if (recv_counts == wait_replt_counts_max)
                {
                    recv_counts = 0;
                    get_current_limited_flg = 0;
                }


            }
            else
            {
                recv_counts = 0;
                std::istringstream iss(recv_data);
                std::string token;
                while (std::getline(iss, token, ' '))
                {
                    float num = 0.0;
                    std::istringstream(token) >> num;
                    fdb.push_back(num);
                }
                get_current_limited_flg = 0;
                return APIResultCode::SUCCESS;
            }
        }

        default:
            break;
        }
        end = std::chrono::steady_clock::now();
        int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        if (int_ms.count() > 1000)
        {
            if (get_current_limited_flg)
            {
                std::cout << "DEVICE RECVFROM: " << ip_ << ", TIMEOUT" << std::endl;
            }
            else
            {
                std::cout << "DEVICE SENDTO: " << ip_ << ", TIMEOUT" << std::endl;
            }
            get_current_limited_flg = 0;
            return APIResultCode::TIMEOUT;
        }
    }
    return APIResultCode::FAIL;
}

int Handapi::get_ip(std::string &_ip)
{
    int ret;
    std::vector<uint8_t> send_data;
    send_data.push_back(0x0f);
    begin = std::chrono::steady_clock::now();

    while (1)
    {
        switch (get_ip_flg)
        {
        case 0:
        {
            ret = comm_udp_socket->SendData(send_data);
            if (ret < 0)
            {
#ifdef DEBUG
                std::cout << "ctrl send data failed" << std::endl;
#endif // DEBUG
            }
            else
            {
                get_ip_flg = 1;
            }
            break;
        }
        case 1:
        {
            static uint32_t recv_counts = 0;
            recv_counts++;
            std::string recv_data;
            ret = comm_udp_socket->ReceiveData(recv_data);
            if (ret < 0)
            {
                if (recv_counts == wait_replt_counts_max)
                {
                    recv_counts = 0;
                    get_ip_flg = 0;
                }


            }
            else
            {
                get_ip_flg = 0;
                _ip = recv_data;
                return APIResultCode::SUCCESS;
            }
        }

        default:
            break;
        }
        end = std::chrono::steady_clock::now();
        int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        if (int_ms.count() > 1000)
        {
            if (get_ip_flg)
            {
                std::cout << "DEVICE RECVFROM: " << ip_ << ", TIMEOUT" << std::endl;
            }
            else
            {
                std::cout << "DEVICE SENDTO: " << ip_ << ", TIMEOUT" << std::endl;
            }
            get_ip_flg = 0;
            return APIResultCode::TIMEOUT;
        }
    }
    return APIResultCode::FAIL;
}

int Handapi::get_pos_pid(std::vector<float> &fdb)
{
    int ret;
    std::vector<uint8_t> send_data;
    send_data.push_back(0x08);
    begin = std::chrono::steady_clock::now();

    while (1)
    {
        switch (get_pos_pid_flg)
        {
        case 0:
        {
            ret = comm_udp_socket->SendData(send_data);
            if (ret < 0)
            {
#ifdef DEBUG
                std::cout << "ctrl send data failed" << std::endl;
#endif // DEBUG
            }
            else
            {
                get_pos_pid_flg = 1;
            }
            break;
        }
        case 1:
        {
            static uint32_t recv_counts = 0;
            recv_counts++;
            std::string recv_data;
            ret = comm_udp_socket->ReceiveData(recv_data);
            if (ret < 0)
            {
                if (recv_counts == wait_replt_counts_max)
                {
                    recv_counts = 0;
                    get_pos_pid_flg = 0;
                }


            }
            else
            {
                recv_counts = 0;
                std::istringstream iss(recv_data);
                std::string token;
                while (std::getline(iss, token, ' '))
                {
                    float num = 0.0;
                    std::istringstream(token) >> num;
                    fdb.push_back(num);
                }
                get_pos_pid_flg = 0;
                return APIResultCode::SUCCESS;
            }
        }

        default:
            break;
        }
        end = std::chrono::steady_clock::now();
        int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        if (int_ms.count() > 1000)
        {
            if (get_pos_pid_flg)
            {
                std::cout << "DEVICE RECVFROM: " << ip_ << ", TIMEOUT" << std::endl;
            }
            else
            {
                std::cout << "DEVICE SENDTO: " << ip_ << ", TIMEOUT" << std::endl;
            }
            get_pos_pid_flg = 0;
            return APIResultCode::TIMEOUT;
        }
    }
    return APIResultCode::FAIL;
}

int Handapi::get_velocity_pid(std::vector<float> &fdb)
{
    int ret;
    std::vector<uint8_t> send_data;
    send_data.push_back(0x09);
    begin = std::chrono::steady_clock::now();

    while (1)
    {
        switch (get_vel_pid_flg)
        {
        case 0:
        {
            ret = comm_udp_socket->SendData(send_data);
            if (ret < 0)
            {
#ifdef DEBUG
                std::cout << "ctrl send data failed" << std::endl;
#endif // DEBUG
            }
            else
            {
                get_vel_pid_flg = 1;
            }
            break;
        }
        case 1:
        {
            static uint32_t recv_counts = 0;
            recv_counts++;
            std::string recv_data;
            ret = comm_udp_socket->ReceiveData(recv_data);
            if (ret < 0)
            {
                if (recv_counts == wait_replt_counts_max)
                {
                    recv_counts = 0;
                    get_vel_pid_flg = 0;
                }


            }
            else
            {
                recv_counts = 0;
                std::istringstream iss(recv_data);
                std::string token;
                while (std::getline(iss, token, ' '))
                {
                    float num = 0.0;
                    std::istringstream(token) >> num;
                    fdb.push_back(num);
                }
                get_vel_pid_flg = 0;
                return APIResultCode::SUCCESS;
            }
        }

        default:
            break;
        }
        end = std::chrono::steady_clock::now();
        int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        if (int_ms.count() > 1000)
        {
            if (get_vel_pid_flg)
            {
                std::cout << "DEVICE RECVFROM: " << ip_ << ", TIMEOUT" << std::endl;
            }
            else
            {
                std::cout << "DEVICE SENDTO: " << ip_ << ", TIMEOUT" << std::endl;
            }
            get_vel_pid_flg = 0;
            return APIResultCode::TIMEOUT;
        }
    }
    return APIResultCode::FAIL;
}

int Handapi::get_current_pid(std::vector<float> &fdb)
{
    int ret;
    std::vector<uint8_t> send_data;
    send_data.push_back(0x0a);
    begin = std::chrono::steady_clock::now();

    while (1)
    {
        switch (get_cur_pid_flg)
        {
        case 0:
        {
            ret = comm_udp_socket->SendData(send_data);
            if (ret < 0)
            {
#ifdef DEBUG
                std::cout << "ctrl send data failed" << std::endl;
#endif // DEBUG
            }
            else
            {
                get_cur_pid_flg = 1;
            }
            break;
        }
        case 1:
        {
            static uint32_t recv_counts = 0;
            recv_counts++;
            std::string recv_data;
            ret = comm_udp_socket->ReceiveData(recv_data);
            if (ret < 0)
            {
                if (recv_counts == wait_replt_counts_max)
                {
                    recv_counts = 0;
                    get_cur_pid_flg = 0;
                }


            }
            else
            {
                recv_counts = 0;
                std::istringstream iss(recv_data);
                std::string token;
                while (std::getline(iss, token, ' '))
                {
                    float num = 0.0;
                    std::istringstream(token) >> num;
                    fdb.push_back(num);
                }
                get_cur_pid_flg = 0;
                return APIResultCode::SUCCESS;
            }
        }

        default:
            break;
        }
        end = std::chrono::steady_clock::now();
        int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        if (int_ms.count() > 1000)
        {
            if (get_cur_pid_flg)
            {
                std::cout << "DEVICE RECVFROM: " << ip_ << ", TIMEOUT" << std::endl;
            }
            else
            {
                std::cout << "DEVICE SENDTO: " << ip_ << ", TIMEOUT" << std::endl;
            }
            get_cur_pid_flg = 0;
            return APIResultCode::TIMEOUT;
        }
    }
    return APIResultCode::FAIL;
}

int Handapi::get_firmware_version(std::string &ver)
{
    int ret;
    std::vector<uint8_t> send_data;
    send_data.push_back(0x0e);
    begin = std::chrono::steady_clock::now();
    while (1)
    {
        switch (get_firmware_version_flg)
        {
        case 0:
        {
            ret = comm_udp_socket->SendData(send_data);
            if (ret < 0)
            {
#ifdef DEBUG
                std::cout << "ctrl send data failed" << std::endl;
#endif // DEBUG
            }
            else
            {
                get_firmware_version_flg = 1;
            }
            break;
        }
        case 1:
        {
            static uint32_t recv_counts = 0;
            recv_counts++;
            std::string recv_data;
            ret = comm_udp_socket->ReceiveData(recv_data);
            if (ret < 0)
            {
                if (recv_counts == wait_replt_counts_max)
                {
                    recv_counts = 0;
                    get_firmware_version_flg = 0;
                }


            }
            else
            {
                get_firmware_version_flg = 0;
                ver = recv_data;
                return APIResultCode::SUCCESS;
            }
        }

        default:
            break;
        }
        end = std::chrono::steady_clock::now();
        int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        if (int_ms.count() > 1000)
        {
            if (get_firmware_version_flg)
            {
                std::cout << "DEVICE RECVFROM: " << ip_ << ", TIMEOUT" << std::endl;
            }
            else
            {
                std::cout << "DEVICE SENDTO: " << ip_ << ", TIMEOUT" << std::endl;
            }
            get_firmware_version_flg = 0;
            return APIResultCode::TIMEOUT;
        }
    }
    return APIResultCode::FAIL;
}

// set config params
int Handapi::set_velocity_limited(uint8_t id, float max_speed)
{
    int ret;
    std::vector<uint8_t> send_data;
    send_data.push_back(0);
    send_data.push_back(0x09);
    send_data.push_back(0);
    send_data.push_back(id);
    unsigned int temp = *(unsigned int *)&max_speed;
    send_data.push_back((temp >> 24) & 0xFF);
    send_data.push_back((temp >> 16) & 0xFF);
    send_data.push_back((temp >> 8) & 0xFF);
    send_data.push_back((temp >> 0) & 0xFF);
    begin = std::chrono::steady_clock::now();
    while (1)
    {
        switch (set_velocity_limited_flg)
        {
        case 0:
        {
            ret = ctrl_udp_socket->SendData(send_data);
            if (ret < 0)
            {
#ifdef DEBUG
                std::cout << "ctrl send data failed" << std::endl;
#endif // DEBUG
            }
            else
            {
                set_velocity_limited_flg = 1;
            }
            break;
        }
        case 1:
        {
            set_velocity_limited_flg = 0;
            return APIResultCode::SUCCESS;
        }

        default:
            break;
        }

        end = std::chrono::steady_clock::now();
        int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        if (int_ms.count() > 1000)
        {
            if (set_velocity_limited_flg)
            {
                std::cout << "DEVICE RECVFROM: " << ip_ << ", TIMEOUT" << std::endl;
            }
            else
            {
                std::cout << "DEVICE SENDTO: " << ip_ << ", TIMEOUT" << std::endl;
            }
            set_velocity_limited_flg = 0;
            return APIResultCode::TIMEOUT;
        }
    }
    return APIResultCode::FAIL;
}

int Handapi::set_pos_limited(uint8_t id, float start_angel, float end_angle)
{
    int ret;
    std::vector<uint8_t> send_data;
    send_data.push_back(0x01);
    send_data.push_back(0x08);
    send_data.push_back(0);
    send_data.push_back(id);
    unsigned int temp = *(unsigned int *)&start_angel;
    send_data.push_back((temp >> 24) & 0xFF);
    send_data.push_back((temp >> 16) & 0xFF);
    send_data.push_back((temp >> 8) & 0xFF);
    send_data.push_back((temp >> 0) & 0xFF);
    temp = *(unsigned int *)&end_angle;
    send_data.push_back((temp >> 24) & 0xFF);
    send_data.push_back((temp >> 16) & 0xFF);
    send_data.push_back((temp >> 8) & 0xFF);
    send_data.push_back((temp >> 0) & 0xFF);
    begin = std::chrono::steady_clock::now();
    while (1)
    {
        switch (set_pos_limited_flg)
        {
        case 0:
        {
            ret = ctrl_udp_socket->SendData(send_data);
            if (ret < 0)
            {
#ifdef DEBUG
                std::cout << "ctrl send data failed" << std::endl;
#endif // DEBUG
            }
            else
            {
                set_pos_limited_flg = 1;
            }
            break;
        }
        case 1:
        {
            set_pos_limited_flg = 0;
            return APIResultCode::SUCCESS;
        }

        default:
            break;
        }
        end = std::chrono::steady_clock::now();
        int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        if (int_ms.count() > 1000)
        {
            if (set_pos_limited_flg)
            {
                std::cout << "DEVICE RECVFROM: " << ip_ << ", TIMEOUT" << std::endl;
            }
            else
            {
                std::cout << "DEVICE SENDTO: " << ip_ << ", TIMEOUT" << std::endl;
            }
            set_pos_limited_flg = 0;
            return APIResultCode::TIMEOUT;
        }
    }
    return APIResultCode::FAIL;
}

int Handapi::set_current_limited(uint8_t id, float max_current)
{
    int ret;
    std::vector<uint8_t> send_data;
    send_data.push_back(0x01);
    send_data.push_back(0x0a);
    send_data.push_back(0);
    send_data.push_back(id);
    unsigned int temp = *(unsigned int *)&max_current;
    send_data.push_back((temp >> 24) & 0xFF);
    send_data.push_back((temp >> 16) & 0xFF);
    send_data.push_back((temp >> 8) & 0xFF);
    send_data.push_back((temp >> 0) & 0xFF);
    begin = std::chrono::steady_clock::now();
    while (1)
    {
        switch (set_pos_limited_flg)
        {
        case 0:
        {
            ret = ctrl_udp_socket->SendData(send_data);
            if (ret < 0)
            {
#ifdef DEBUG
                std::cout << "ctrl send data failed" << std::endl;
#endif // DEBUG
            }
            else
            {
                set_pos_limited_flg = 1;
            }
            break;
        }
        case 1:
        {
            set_pos_limited_flg = 0;
            return APIResultCode::SUCCESS;
        }

        default:
            break;
        }
        end = std::chrono::steady_clock::now();
        int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        if (int_ms.count() > 1000)
        {
            if (set_pos_limited_flg)
            {
                std::cout << "DEVICE RECVFROM: " << ip_ << ", TIMEOUT" << std::endl;
            }
            else
            {
                std::cout << "DEVICE SENDTO: " << ip_ << ", TIMEOUT" << std::endl;
            }
            set_pos_limited_flg = 0;
            return APIResultCode::TIMEOUT;
        }
    }
    return APIResultCode::FAIL;
}

int Handapi::set_pos_pid(uint8_t id, std::vector<float> _pid)
{
    int ret;
    std::vector<uint8_t> send_data;
    send_data.push_back(0x01);
    send_data.push_back(0x05);
    send_data.push_back(0);
    send_data.push_back(id);
    for (int i = 0; i < _pid.size(); i++)
    {
        unsigned int temp = *(unsigned int *)&_pid[i];
        send_data.push_back((temp >> 24) & 0xFF);
        send_data.push_back((temp >> 16) & 0xFF);
        send_data.push_back((temp >> 8) & 0xFF);
        send_data.push_back((temp >> 0) & 0xFF);
    }

    begin = std::chrono::steady_clock::now();

    while (1)
    {
        switch (set_pos_limited_flg)
        {
        case 0:
        {
            ret = ctrl_udp_socket->SendData(send_data);
            if (ret < 0)
            {
#ifdef DEBUG
                std::cout << "ctrl send data failed" << std::endl;
#endif // DEBUG
            }
            else
            {
                set_pos_limited_flg = 1;
            }
            break;
        }
        case 1:
        {
            set_pos_limited_flg = 0;
            return APIResultCode::SUCCESS;
        }

        default:
            break;
        }
        end = std::chrono::steady_clock::now();
        int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        if (int_ms.count() > 1000)
        {
            if (set_pos_limited_flg)
            {
                std::cout << "DEVICE RECVFROM: " << ip_ << ", TIMEOUT" << std::endl;
            }
            else
            {
                std::cout << "DEVICE SENDTO: " << ip_ << ", TIMEOUT" << std::endl;
            }
            set_pos_limited_flg = 0;
            return APIResultCode::TIMEOUT;
        }
    }
    return APIResultCode::FAIL;
}

int Handapi::set_velocity_pid(uint8_t id, std::vector<float> _pid)
{
    int ret;
    std::vector<uint8_t> send_data;
    send_data.push_back(0x01);
    send_data.push_back(0x06);
    send_data.push_back(0);
    send_data.push_back(id);
    for (int i = 0; i < _pid.size(); i++)
    {
        unsigned int temp = *(unsigned int *)&_pid[i];
        send_data.push_back((temp >> 24) & 0xFF);
        send_data.push_back((temp >> 16) & 0xFF);
        send_data.push_back((temp >> 8) & 0xFF);
        send_data.push_back((temp >> 0) & 0xFF);
    }

    begin = std::chrono::steady_clock::now();

    while (1)
    {
        switch (set_pos_limited_flg)
        {
        case 0:
        {
            ret = ctrl_udp_socket->SendData(send_data);
            if (ret < 0)
            {
#ifdef DEBUG
                std::cout << "ctrl send data failed" << std::endl;
#endif // DEBUG
            }
            else
            {
                set_pos_limited_flg = 1;
            }
            break;
        }
        case 1:
        {
            set_pos_limited_flg = 0;
            return APIResultCode::SUCCESS;
        }

        default:
            break;
        }
        end = std::chrono::steady_clock::now();
        int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        if (int_ms.count() > 1000)
        {
            if (set_pos_limited_flg)
            {
                std::cout << "DEVICE RECVFROM: " << ip_ << ", TIMEOUT" << std::endl;
            }
            else
            {
                std::cout << "DEVICE SENDTO: " << ip_ << ", TIMEOUT" << std::endl;
            }
            set_pos_limited_flg = 0;
            return APIResultCode::TIMEOUT;
        }
    }
    return APIResultCode::FAIL;
}

int Handapi::set_current_pid(uint8_t id, std::vector<float> _pid)
{
    int ret;
    std::vector<uint8_t> send_data;
    send_data.push_back(0x01);
    send_data.push_back(0x07);
    send_data.push_back(0);
    send_data.push_back(id);
    for (int i = 0; i < _pid.size(); i++)
    {
        unsigned int temp = *(unsigned int *)&_pid[i];
        send_data.push_back((temp >> 24) & 0xFF);
        send_data.push_back((temp >> 16) & 0xFF);
        send_data.push_back((temp >> 8) & 0xFF);
        send_data.push_back((temp >> 0) & 0xFF);
    }

    begin = std::chrono::steady_clock::now();

    while (1)
    {
        switch (set_pos_limited_flg)
        {
        case 0:
        {
            ret = ctrl_udp_socket->SendData(send_data);
            if (ret < 0)
            {
#ifdef DEBUG
                std::cout << "ctrl send data failed" << std::endl;
#endif // DEBUG
            }
            else
            {
                set_pos_limited_flg = 1;
            }
            break;
        }
        case 1:
        {
            set_pos_limited_flg = 0;
            return APIResultCode::SUCCESS;
        }

        default:
            break;
        }
        end = std::chrono::steady_clock::now();
        int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        if (int_ms.count() > 1000)
        {
            if (set_pos_limited_flg)
            {
                std::cout << "DEVICE RECVFROM: " << ip_ << ", TIMEOUT" << std::endl;
            }
            else
            {
                std::cout << "DEVICE SENDTO: " << ip_ << ", TIMEOUT" << std::endl;
            }
            set_pos_limited_flg = 0;
            return APIResultCode::TIMEOUT;
        }
    }
    return APIResultCode::FAIL;
}

int Handapi::set_pos(uint8_t id, float angel)
{
    int ret;
    std::vector<uint8_t> send_data;
    send_data.push_back(0x01);
    send_data.push_back(0x02);
    send_data.push_back(0x00);
    send_data.push_back(id);
    unsigned int temp = *(unsigned int *)&angel;
    send_data.push_back((temp >> 24) & 0xFF);
    send_data.push_back((temp >> 16) & 0xFF);
    send_data.push_back((temp >> 8) & 0xFF);
    send_data.push_back((temp >> 0) & 0xFF);
    begin = std::chrono::steady_clock::now();

    while (1)
    {
        switch (set_pos_limited_flg)
        {
        case 0:
        {
            ret = ctrl_udp_socket->SendData(send_data);
            if (ret < 0)
            {
#ifdef DEBUG
                std::cout << "ctrl send data failed" << std::endl;
#endif // DEBUG
            }
            else
            {
                set_pos_limited_flg = 1;
            }
            break;
        }
        case 1:
        {
            set_pos_limited_flg = 0;
            return APIResultCode::SUCCESS;
        }

        default:
            break;
        }
        end = std::chrono::steady_clock::now();
        int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        if (int_ms.count() > 1000)
        {
            if (set_pos_limited_flg)
            {
                std::cout << "DEVICE RECVFROM: " << ip_ << ", TIMEOUT" << std::endl;
            }
            else
            {
                std::cout << "DEVICE SENDTO: " << ip_ << ", TIMEOUT" << std::endl;
            }
            set_pos_limited_flg = 0;
            return APIResultCode::TIMEOUT;
        }
    }
    return APIResultCode::FAIL;
}

int Handapi::set_pd_control(uint8_t id, float angel, float w)
{
    int ret;
    std::vector<uint8_t> send_data;
    send_data.push_back(0x01);
    send_data.push_back(0x21);
    send_data.push_back(0x00);
    send_data.push_back(id);
    unsigned int temp = *(unsigned int *)&angel;
    send_data.push_back((temp >> 24) & 0xFF);
    send_data.push_back((temp >> 16) & 0xFF);
    send_data.push_back((temp >> 8) & 0xFF);
    send_data.push_back((temp >> 0) & 0xFF);
    temp = *(unsigned int *)&w;
    send_data.push_back((temp >> 24) & 0xFF);
    send_data.push_back((temp >> 16) & 0xFF);
    send_data.push_back((temp >> 8) & 0xFF);
    send_data.push_back((temp >> 0) & 0xFF);
    begin = std::chrono::steady_clock::now();

    while (1)
    {
        switch (set_pd_control_flg)
        {
        case 0:
        {
            ret = ctrl_udp_socket->SendData(send_data);
            if (ret < 0)
            {
#ifdef DEBUG
                std::cout << "ctrl send data failed" << std::endl;
#endif // DEBUG
            }
            else
            {
                set_pd_control_flg = 1;
            }
            break;
        }
        case 1:
        {
            set_pd_control_flg = 0;
            return APIResultCode::SUCCESS;
        }

        default:
            break;
        }
        end = std::chrono::steady_clock::now();
        int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        if (int_ms.count() > 1000)
        {
            if (set_pd_control_flg)
            {
                std::cout << "DEVICE RECVFROM: " << ip_ << ", TIMEOUT" << std::endl;
            }
            else
            {
                std::cout << "DEVICE SENDTO: " << ip_ << ", TIMEOUT" << std::endl;
            }
            set_pd_control_flg = 0;
            return APIResultCode::TIMEOUT;
        }
    }
    return APIResultCode::FAIL;
}

int Handapi::set_pos(std::vector<float> _cmd)
{
    int ret;
    std::vector<uint8_t> send_data;
    send_data.push_back(0x01);
    send_data.push_back(0x11);
    send_data.push_back(0x00);
    send_data.push_back(0x00);
    if (_cmd.size() != 6)
    {
        std::cerr << "SET POSITION ALL : CMD SIZE IS NOT SIX" << std::endl;
        return APIResultCode::FAIL;
    }
    for (int i = 0; i < _cmd.size(); i++)
    {
        unsigned int temp = *(unsigned int *)&_cmd[i];
        send_data.push_back((temp >> 24) & 0xFF);
        send_data.push_back((temp >> 16) & 0xFF);
        send_data.push_back((temp >> 8) & 0xFF);
        send_data.push_back((temp >> 0) & 0xFF);
    }
    begin = std::chrono::steady_clock::now();

    while (1)
    {
        switch (set_position_all)
        {
        case 0:
        {
            ret = ctrl_udp_socket->SendData(send_data);
            if (ret < 0)
            {
#ifdef DEBUG
                std::cout << "ctrl send data failed" << std::endl;
#endif // DEBUG
            }
            else
            {
                set_position_all = 1;
            }
            break;
        }
        case 1:
        {
            set_position_all = 0;
            return APIResultCode::SUCCESS;
        }

        default:
            break;
        }
        end = std::chrono::steady_clock::now();
        int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        if (int_ms.count() > 1000)
        {
            if (set_position_all)
            {
                std::cout << "DEVICE RECVFROM: " << ip_ << ", TIMEOUT" << std::endl;
            }
            else
            {
                std::cout << "DEVICE SENDTO: " << ip_ << ", TIMEOUT" << std::endl;
            }
            set_position_all = 0;
            return APIResultCode::TIMEOUT;
        }
    }
    return APIResultCode::FAIL;
}

int Handapi::set_velocity(uint8_t id, float speed)
{
    int ret;
    std::vector<uint8_t> send_data;
    send_data.push_back(0x01);
    send_data.push_back(0x03);
    send_data.push_back(0x00);
    send_data.push_back(id);
    unsigned int temp = *(unsigned int *)&speed;
    send_data.push_back((temp >> 24) & 0xFF);
    send_data.push_back((temp >> 16) & 0xFF);
    send_data.push_back((temp >> 8) & 0xFF);
    send_data.push_back((temp >> 0) & 0xFF);
    begin = std::chrono::steady_clock::now();

    while (1)
    {
        switch (set_velocity_flg)
        {
        case 0:
        {
            ret = ctrl_udp_socket->SendData(send_data);
            if (ret < 0)
            {
#ifdef DEBUG
                std::cout << "ctrl send data failed" << std::endl;
#endif // DEBUG
            }
            else
            {
                set_velocity_flg = 1;
            }
            break;
        }
        case 1:
        {
            set_velocity_flg = 0;
            return APIResultCode::SUCCESS;
        }

        default:
            break;
        }
        end = std::chrono::steady_clock::now();
        int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        if (int_ms.count() > 1000)
        {
            if (set_velocity_flg)
            {
                std::cout << "DEVICE RECVFROM: " << ip_ << ", TIMEOUT" << std::endl;
            }
            else
            {
                std::cout << "DEVICE SENDTO: " << ip_ << ", TIMEOUT" << std::endl;
            }
            set_velocity_flg = 0;
            return APIResultCode::TIMEOUT;
        }
    }
    return APIResultCode::FAIL;
}

int Handapi::set_current(uint8_t id, float current)
{
    int ret;
    std::vector<uint8_t> send_data;
    send_data.push_back(0x01);
    send_data.push_back(0x04);
    send_data.push_back(0x00);
    send_data.push_back(id);
    unsigned int temp = *(unsigned int *)&current;
    send_data.push_back((temp >> 24) & 0xFF);
    send_data.push_back((temp >> 16) & 0xFF);
    send_data.push_back((temp >> 8) & 0xFF);
    send_data.push_back((temp >> 0) & 0xFF);
    begin = std::chrono::steady_clock::now();

    while (1)
    {
        switch (set_current_flg)
        {
        case 0:
        {
            ret = ctrl_udp_socket->SendData(send_data);
            if (ret < 0)
            {
#ifdef DEBUG
                std::cout << "ctrl send data failed" << std::endl;
#endif // DEBUG
            }
            else
            {
                set_current_flg = 1;
            }
            break;
        }
        case 1:
        {
            set_current_flg = 0;
            return APIResultCode::SUCCESS;
        }

        default:
            break;
        }
        end = std::chrono::steady_clock::now();
        int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        if (int_ms.count() > 1000)
        {
            if (set_current_flg)
            {
                std::cout << "DEVICE RECVFROM: " << ip_ << ", TIMEOUT" << std::endl;
            }
            else
            {
                std::cout << "DEVICE SENDTO: " << ip_ << ", TIMEOUT" << std::endl;
            }
            set_current_flg = 0;
            return APIResultCode::TIMEOUT;
        }
    }
    return APIResultCode::FAIL;
}

int Handapi::set_pwm(uint8_t id, float current)
{
    return APIResultCode::SUCCESS;
}
int Handapi::set_pwm(std::vector<float> _cmd)
{
    int ret;
    std::vector<uint8_t> send_data;
    send_data.push_back(0x01);
    send_data.push_back(0x14);
    send_data.push_back(0x00);
    send_data.push_back(0x00);
    if (_cmd.size() != 6)
    {
        std::cerr << "SET POSITION ALL : CMD SIZE IS NOT SIX" << std::endl;
        return APIResultCode::FAIL;
    }
    for (int i = 0; i < _cmd.size(); i++)
    {
        unsigned int temp = *(unsigned int *)&_cmd[i];
        send_data.push_back((temp >> 24) & 0xFF);
        send_data.push_back((temp >> 16) & 0xFF);
        send_data.push_back((temp >> 8) & 0xFF);
        send_data.push_back((temp >> 0) & 0xFF);
    }

    begin = std::chrono::steady_clock::now();

    while (1)
    {
        switch (set_pwm_all)
        {
        case 0:
        {
            ret = ctrl_udp_socket->SendData(send_data);
            if (ret < 0)
            {
#ifdef DEBUG
                std::cout << "ctrl send data failed" << std::endl;
#endif // DEBUG
            }
            else
            {
                set_pwm_all = 1;
            }
            break;
        }
        case 1:
        {
            set_pwm_all = 0;
            return APIResultCode::SUCCESS;
        }

        default:
            break;
        }
        end = std::chrono::steady_clock::now();
        int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        if (int_ms.count() > 1000)
        {
            if (set_pwm_all)
            {
                std::cout << "DEVICE RECVFROM: " << ip_ << ", TIMEOUT" << std::endl;
            }
            else
            {
                std::cout << "DEVICE SENDTO: " << ip_ << ", TIMEOUT" << std::endl;
            }
            set_pwm_all = 0;
            return APIResultCode::TIMEOUT;
        }
    }
    return APIResultCode::FAIL;
}