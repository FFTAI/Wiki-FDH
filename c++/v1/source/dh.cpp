#include "dh.h"

using namespace Predefine;
using namespace Utils;

DH::DhCls::DhCls(/* args */)
{
}

DH::DhCls::~DhCls()
{
}

int DH::DhCls::init()
{
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;

    this->dh_socket = socket(AF_INET, SOCK_DGRAM, 0);
    int set_sock_opt_flg = setsockopt(this->dh_socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    if (set_sock_opt_flg == -1)
    {
        Logger::get_instance()->print_trace_error("Error: init_network() setsockopt() failed\n");
        return FunctionResult::FAILURE;
    }

    this->left_ctrl_addr.sin_family = AF_INET;
    this->left_ctrl_addr.sin_port = htons(CTRL_PORT);
    inet_pton(AF_INET, LEFT_IP, &this->left_ctrl_addr.sin_addr.s_addr);

    this->left_fdb_addr.sin_family = AF_INET;
    this->left_fdb_addr.sin_port = htons(FDB_PORT);
    inet_pton(AF_INET, LEFT_IP, &this->left_fdb_addr.sin_addr.s_addr);

    this->right_ctrl_addr.sin_family = AF_INET;
    this->right_ctrl_addr.sin_port = htons(CTRL_PORT);
    inet_pton(AF_INET, RIGHT_IP, &this->right_ctrl_addr.sin_addr.s_addr);

    this->right_fdb_addr.sin_family = AF_INET;
    this->right_fdb_addr.sin_port = htons(FDB_PORT);
    inet_pton(AF_INET, RIGHT_IP, &this->right_fdb_addr.sin_addr.s_addr);

#ifdef DEBUG
    Logger::get_instance()->print_trace_debug("init finished\n");
#endif

    return FunctionResult::SUCCESS;
}

int DH::DhCls::communicaiton(std::string ip, int port)
{
    int ret = -1;
    if (this->isInit)
    {
        this->isInit = 0;
        if (this->init() != FunctionResult::SUCCESS)
        {
            return FunctionResult::FAILURE;
        }
    }

#ifdef DEBUG
    Logger::get_instance()->print_trace_debug("ip: %s, port: %d\n", ip.c_str(), port);
#endif

    if ((LEFT_IP == ip) && (port == CTRL_PORT))
    {
        ret = sendto(this->dh_socket, this->send_msg, BUFFSIZE, 0, (struct sockaddr *)&this->left_ctrl_addr, sizeof(this->left_ctrl_addr));
#ifdef DEBUG
#endif
    }
    else if ((LEFT_IP == ip) && (port == FDB_PORT))
    {
        ret = sendto(this->dh_socket, this->send_msg, BUFFSIZE, 0, (struct sockaddr *)&this->left_fdb_addr, sizeof(this->left_fdb_addr));
#ifdef DEBUG

#endif
    }
    else if ((RIGHT_IP == ip) && (port == CTRL_PORT))
    {
        ret = sendto(this->dh_socket, this->send_msg, BUFFSIZE, 0, (struct sockaddr *)&this->right_ctrl_addr, sizeof(this->right_ctrl_addr));
#ifdef DEBUG
        Logger::get_instance()->print_trace_debug("send output->");
        for (int i = 0; i < 2; i++)
        {
            std::cout << std::hex << static_cast<int>(this->send_msg[i]) << " ";
        }
        std::cout << std::endl;

#endif
    }
    else if ((RIGHT_IP == ip) && (port == FDB_PORT))
    {
        ret = sendto(this->dh_socket, this->send_msg, BUFFSIZE, 0, (struct sockaddr *)&this->right_fdb_addr, sizeof(this->right_fdb_addr));
#ifdef DEBUG

#endif
    }
    else
    {
        Logger::get_instance()->print_trace_error("error: ip or port\n");
        return FunctionResult::FAILURE;
    }

    if (ret == -1)
    {
        Logger::get_instance()->print_trace_error("hand sendto() failed\n");
        return FunctionResult::FAILURE;
    }

    // ret = -1;
    // if (recvmsg == NULL)
    // {
    //     return FunctionResult::SUCCESS;
    // }

    do
    {
        ret = recvfrom(this->dh_socket, this->recv_msg, BUFFSIZE, 0, (struct sockaddr *)&this->recv_addr, &sockaddr_len);
        if (ret <= 0)
        {
            Logger::get_instance()->print_trace_warning("Cannot receive msg, ErrorCode: 1001\n");
        }
        else
        {
#ifdef DEBUG
            Logger::get_instance()->print_trace("recv: %s\n", this->recv_msg);
#endif
        }

    } while (ret <= 0);

    return FunctionResult::SUCCESS;
}

int DH::DhCls::encode(uint8_t *en_msg, uint8_t msg_size)
{
    memset(this->send_msg, 0, BUFFSIZE);
    unsigned char *bytes = reinterpret_cast<unsigned char *>(en_msg);
    for (int i = 0; i < msg_size; ++i)
    {
        std::cout << std::hex << static_cast<int>(bytes[i]) << " ";
    }
    std::cout << std::endl;

    memcpy(this->send_msg, bytes, msg_size);
    for (int i = 0; i < msg_size; i++)
    {
        std::cout << std::hex << static_cast<int>(this->send_msg[i]) << " ";
    }
    std::cout << std::endl;

#ifdef DEBUG
    for (uint8_t i = 0; i < msg_size; i++)
    {
        Logger::get_instance()->print_trace("input: %d", (uint8_t)this->send_msg[i]);
    }
    std::cout << std::endl;

#endif
    return FunctionResult::SUCCESS;
}

int DH::DhCls::decode(uint8_t *de_msg)
{
    Logger::get_instance()->print_trace_debug("%s\n", de_msg);
    return FunctionResult::SUCCESS;
}

int DH::DhCls::do_ctrl(HandTypeDef HandType, uint8_t *word, uint8_t msg_size)
{
    if (this->encode(word, msg_size) != FunctionResult::SUCCESS)
    {
        return FunctionResult::FAILURE;
    }

#ifdef DEBUG
#endif

    switch (HandType)
    {
    case LEFT_HAND:
    {
        if (this->communicaiton(LEFT_IP, CTRL_PORT) != FunctionResult::SUCCESS)
        {
            return FunctionResult::FAILURE;
        }
        break;
    }

    case RIGHT_HAND:
    {
        if (this->communicaiton(RIGHT_IP, CTRL_PORT) != FunctionResult::SUCCESS)
        {
            return FunctionResult::FAILURE;
        }
        break;
    }

    default:
        break;
    }

    return FunctionResult::SUCCESS;
}

int DH::DhCls::do_fdb(HandTypeDef HandType, GetFdbControlWordTypeDef controlword, void *fdbmsg)
{
    if (this->encode((uint8_t *)&controlword, 8) != FunctionResult::SUCCESS)
    {
        return FunctionResult::FAILURE;
    }

#ifdef DEBUG
#endif
    switch (HandType)
    {
    case LEFT_HAND:
    {
        if (this->communicaiton(LEFT_IP, FDB_PORT) != FunctionResult::SUCCESS)
        {
            return FunctionResult::FAILURE;
        }
        break;
    }

    case RIGHT_HAND:
    {
        if (this->communicaiton(RIGHT_IP, FDB_PORT) != FunctionResult::SUCCESS)
        {
            return FunctionResult::FAILURE;
        }
        break;
    }

    default:
        break;
    }

    return FunctionResult::SUCCESS;
}

DH::DhCls *HandControl = new DH::DhCls();

int DH::calibration()
{
    uint8_t buff[2] = {0x01, 0x01};
    HandControl->do_ctrl(LEFT_HAND, buff, 2);
    HandControl->do_ctrl(RIGHT_HAND, buff, 2);
}

int DH::calibration(HandTypeDef HandType)
{
    uint8_t buff[2];
    buff[0] = 0x01;
    buff[1] = 0x01;
    HandControl->do_ctrl(HandType, buff, sizeof(buff));
}

int DH::set_pid(LoopTypeDef tar_loop, float _p, float _i, float _d)
{
}

int DH::set_target(LoopTypeDef tar_loop, float _target)
{
}

int DH::set_finger_limited(FingerTypeDef fingerid, float minValue, float maxValue)
{
}

float DH::get_angle(HandTypeDef HandType)
{
    HandControl->do_fdb(HandType, GET_ANGLE, NULL);
}