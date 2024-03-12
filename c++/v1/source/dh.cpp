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

int DH::DhCls::communicaiton(std::string ip, int port, int sendsize)
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
        ret = sendto(this->dh_socket, this->send_msg, sendsize, 0, (struct sockaddr *)&this->left_ctrl_addr, sizeof(this->left_ctrl_addr));
#ifdef DEBUG
#endif
    }
    else if ((LEFT_IP == ip) && (port == FDB_PORT))
    {
        ret = sendto(this->dh_socket, this->send_msg, sendsize, 0, (struct sockaddr *)&this->left_fdb_addr, sizeof(this->left_fdb_addr));
#ifdef DEBUG

#endif
    }
    else if ((RIGHT_IP == ip) && (port == CTRL_PORT))
    {
        ret = sendto(this->dh_socket, this->send_msg, sendsize, 0, (struct sockaddr *)&this->right_ctrl_addr, sizeof(this->right_ctrl_addr));
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
        ret = sendto(this->dh_socket, this->send_msg, sendsize, 0, (struct sockaddr *)&this->right_fdb_addr, sizeof(this->right_fdb_addr));
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
            Logger::get_instance()->print_trace_debug("recv: %s\n", this->recv_msg);
#endif
        }

    } while (ret <= 0);

    return FunctionResult::SUCCESS;
}

int DH::DhCls::encode(uint8_t *en_msg, uint8_t msg_size)
{
    memset(this->send_msg, 0, BUFFSIZE);
    unsigned char *bytes = reinterpret_cast<unsigned char *>(en_msg);

    memcpy(this->send_msg, bytes, msg_size);

#ifdef DEBUG
    for (uint8_t i = 0; i < msg_size; i++)
    {
        Logger::get_instance()->print_trace_debug("input: %d", (uint8_t)this->send_msg[i]);
    }
    std::cout << std::endl;

#endif
    return FunctionResult::SUCCESS;
}

int DH::DhCls::decode(ParseTypeDef FdbType, void *retmsg)
{
    if (this->recv_msg == NULL)
    {
        Logger::get_instance()->print_trace_error("An unexpected error has occurred\n");
        return FunctionResult::FAILURE;
    }

    switch (FdbType)
    {
    case NONE:
    {
        Logger::get_instance()->print_trace_error("Please choose really feedback type\n");
        return FunctionResult::FAILURE;
    }
    case PARSE_STRING:
    {
#ifdef DEBUG
        Logger::get_instance()->print_trace_debug("decode: %s\n", this->recv_msg);
#endif
        memcpy(retmsg, this->recv_msg, BUFFSIZE);
        return FunctionResult::SUCCESS;
    }
    case PARSE_LONG_LONG:
    {
#ifdef DEBUG
        Logger::get_instance()->print_trace_debug("decode: %s\n", this->recv_msg);
#endif
        long long cnt[6] = {0};
        uint8_t cnt_index = 0;
        char temp_cnt[20] = {0};
        uint8_t temp_index = 0;
        for (int i = 0; i < sizeof(this->recv_msg); i++)
        {
            if (char(this->recv_msg[i] == NULL))
            {
                break;
            }
            if (char(this->recv_msg[i]) == '*')
            {
                cnt[cnt_index++] = strtol(temp_cnt, NULL, 10);
#ifdef DEBUG
                Logger::get_instance()->print_trace_debug("cnt[%d]: %lld\n", cnt_index - 1, cnt[cnt_index - 1]);
#endif // DEBUG
                temp_index = 0;
                memset(temp_cnt, 0, sizeof(temp_cnt));
                continue;
            }
            temp_cnt[temp_index++] = this->recv_msg[i];
        }
        memcpy(retmsg, cnt, sizeof(cnt));
        return FunctionResult::SUCCESS;
    }
    case PARSE_FLOAT:
    {
#ifdef DEBUG
        Logger::get_instance()->print_trace_debug("decode: %s\n", this->recv_msg);
#endif
        float angle[6] = {0};
        uint8_t angle_index = 0;
        char temp_angle[20] = {0};
        uint8_t temp_index = 0;
        for (int i = 0; i < sizeof(this->recv_msg); i++)
        {
            if (char(this->recv_msg[i] == NULL))
            {
                break;
            }
            if (char(this->recv_msg[i]) == '*')
            {
                angle[angle_index++] = strtof(temp_angle, NULL);
#ifdef DEBUG
                Logger::get_instance()->print_trace_debug("angle[%d]: %f\n", angle_index - 1, angle[angle_index - 1]);
#endif // DEBUG
                temp_index = 0;
                memset(temp_angle, 0, sizeof(temp_angle));
                continue;
            }
            temp_angle[temp_index++] = this->recv_msg[i];
        }
        memcpy(retmsg, angle, sizeof(angle));
        return FunctionResult::SUCCESS;
    }
    case PARSE_UINT8:
    {
#ifdef DEBUG
        Logger::get_instance()->print_trace_debug("decode: %s\n", this->recv_msg);
#endif
        uint8_t status[6] = {0};
        uint8_t status_index = 0;
        char temp_status[3] = {0};
        uint8_t temp_index = 0;
        for (int i = 0; i < sizeof(this->recv_msg); i++)
        {
            if (char(this->recv_msg[i] == NULL))
            {
                break;
            }
            if (char(this->recv_msg[i]) == '*')
            {
                status[status_index++] = strtoul(temp_status, NULL, 10);
#ifdef DEBUG
                Logger::get_instance()->print_trace_debug("status[%d]: %u\n", status_index - 1, status[status_index - 1]);
#endif // DEBUG
                temp_index = 0;
                memset(temp_status, 0, sizeof(temp_status));
                continue;
            }
            temp_status[temp_index++] = this->recv_msg[i];
        }
        memcpy(retmsg, status, sizeof(status));
        return FunctionResult::SUCCESS;
    }
    case PARSE_LONG:
    {
#ifdef DEBUG
        Logger::get_instance()->print_trace_debug("decode: %s\n", this->recv_msg);
#endif
        long errorcode[6] = {0};
        long errorcode_index = 0;
        char temp_errorcode[16] = {0};
        uint8_t temp_index = 0;
        for (int i = 0; i < sizeof(this->recv_msg); i++)
        {
            if (char(this->recv_msg[i] == NULL))
            {
                break;
            }
            if (char(this->recv_msg[i]) == '*')
            {
                errorcode[errorcode_index++] = strtoul(temp_errorcode, NULL, 10);
#ifdef DEBUG
                Logger::get_instance()->print_trace_debug("errorcode[%d]: %ld\n", errorcode_index - 1, errorcode[errorcode_index - 1]);
#endif // DEBUG
                temp_index = 0;
                memset(temp_errorcode, 0, sizeof(temp_errorcode));
                continue;
            }
            temp_errorcode[temp_index++] = this->recv_msg[i];
        }
        memcpy(retmsg, errorcode, sizeof(errorcode));
        return FunctionResult::SUCCESS;
    }

    default:
        return FunctionResult::FAILURE;
    }
    Logger::get_instance()->print_trace_error("An unexpected error has occurred\n");
    return FunctionResult::FAILURE;
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
        if (this->communicaiton(LEFT_IP, CTRL_PORT, msg_size) != FunctionResult::SUCCESS)
        {
            return FunctionResult::FAILURE;
        }
        return FunctionResult::SUCCESS;
    }

    case RIGHT_HAND:
    {
        if (this->communicaiton(RIGHT_IP, CTRL_PORT, msg_size) != FunctionResult::SUCCESS)
        {
            return FunctionResult::FAILURE;
        }
        return FunctionResult::SUCCESS;
    }

    default:
        break;
    }

    return FunctionResult::FAILURE;
}

int DH::DhCls::do_fdb(HandTypeDef HandType, GetFdbControlWordTypeDef controlword, ParseTypeDef FdbType, void *fdbmsg)
{
    if (this->encode((uint8_t *)&controlword, 1) != FunctionResult::SUCCESS)
    {
        return FunctionResult::FAILURE;
    }

#ifdef DEBUG
#endif
    switch (HandType)
    {
    case LEFT_HAND:
    {
        if (this->communicaiton(LEFT_IP, FDB_PORT, 1) != FunctionResult::SUCCESS)
        {
            return FunctionResult::FAILURE;
        }
        break;
    }

    case RIGHT_HAND:
    {
        if (this->communicaiton(RIGHT_IP, FDB_PORT, 1) != FunctionResult::SUCCESS)
        {
            return FunctionResult::FAILURE;
        }
        break;
    }

    default:
        break;
    }

    if (this->decode(FdbType, fdbmsg) == FunctionResult::FAILURE)
    {
        return FunctionResult::FAILURE;
    }

    return FunctionResult::SUCCESS;
}

/*****user interface*****/
DH::DhCls *HandControl = new DH::DhCls();

/// @brief calibration left and right hand
/// @return -1 or 0
///     @note -1 means failed
///     @note  0 means success
int DH::calibration()
{
    uint8_t buff[2] = {0x01, 0x01};
    if (HandControl->do_ctrl(LEFT_HAND, buff, sizeof(buff)) == FunctionResult::FAILURE)
    {
        return FunctionResult::FAILURE;
    }
    if (HandControl->do_ctrl(RIGHT_HAND, buff, sizeof(buff)) == FunctionResult::FAILURE)
    {
        return FunctionResult::FAILURE;
    }
    return FunctionResult::SUCCESS;
}

/// @brief Specifies the type of hand to calibrate
/// @param HandType
///     @param  -LEFT_HAND
///     @param  -RIGHT_HAND
/// @return -1 or 0
///     @note -1 means failed
///     @note  0 means success
int DH::calibration(HandTypeDef HandType)
{
    uint8_t buff[2] = {0x01, 0x01};
    if (HandControl->do_ctrl(HandType, buff, sizeof(buff)) == FunctionResult::FAILURE)
    {
        return FunctionResult::FAILURE;
    }
    return FunctionResult::SUCCESS;
}

/// @brief
/// @return -1 or 0
///     @note -1 means failed
///     @note  0 means success
int DH::get_mechanical_limit()
{
    uint8_t buff[2] = {0x01, 0x04};
    if (HandControl->do_ctrl(LEFT_HAND, buff, sizeof(buff)) == FunctionResult::FAILURE)
    {
        return FunctionResult::FAILURE;
    }
    if (HandControl->do_ctrl(RIGHT_HAND, buff, sizeof(buff)) == FunctionResult::FAILURE)
    {
        return FunctionResult::FAILURE;
    }
    return FunctionResult::SUCCESS;
}

/// @brief
/// @param HandType
///     @param  -LEFT_HAND
///     @param  -RIGHT_HAND
/// @return -1 or 0
///     @note -1 means failed
///     @note  0 means success
int DH::get_mechanical_limit(HandTypeDef HandType)
{
    uint8_t buff[2] = {0x01, 0x04};
    HandControl->do_ctrl(HandType, buff, sizeof(buff));
}

/// @brief Get hand ip
/// @param HandType
///     @param  -LEFT_HAND
///     @param  -RIGHT_HAND
/// @return ip
std::string DH::get_ip(HandTypeDef HandType)
{
    char ret[16] = {0};
    char buff[1024] = {0};
    if (HandControl->do_fdb(HandType, GET_IP, PARSE_STRING, (void *)buff) == FunctionResult::FAILURE)
    {
        Logger::get_instance()->print_trace_error("get ip failed\n");
        return "";
    }
    memccpy(ret, buff, '*', sizeof(ret));
    for (uint8_t i = 0; i < sizeof(ret); i++)
    {
        if (ret[i] == '*')
        {
            ret[i] = ' ';
        }
    }
    return std::string(ret);
}

/// @brief Get encoder register cnt value
/// @param HandType
///     @param  -LEFT_HAND
///     @param  -RIGHT_HAND
/// @param fingetid
///     @param  -THUMB_A
///     @param  -LITTLE_F
///     @param  -MIDDLE_F
///     @param  -THUMB_B
///     @param  -FORE_F
///     @param  -RING_F
/// @return cnt
long long DH::get_cnt(HandTypeDef HandType, FingerTypeDef fingetid)
{
    long long cnt[6] = {0};
    if (HandControl->do_fdb(HandType, GET_CNT, PARSE_LONG_LONG, (void *)cnt) == FunctionResult::FAILURE)
    {
        Logger::get_instance()->print_trace_error("get cnt failed\n");
        return FunctionResult::FAILURE;
    }
    return cnt[fingetid - 1];
}

/// @brief Gets the finger Angle of the specified hand
/// @param HandType
///     @param  -LEFT_HAND
///     @param  -RIGHT_HAND
/// @param fingetid
///     @param  -THUMB_A
///     @param  -LITTLE_F
///     @param  -MIDDLE_F
///     @param  -THUMB_B
///     @param  -FORE_F
///     @param  -RING_F
/// @return angle
float DH::get_angle(HandTypeDef HandType, FingerTypeDef fingetid)
{
    float angle[6] = {0};
    if (HandControl->do_fdb(HandType, GET_ANGLE, PARSE_FLOAT, (void *)angle) == FunctionResult::FAILURE)
    {
        Logger::get_instance()->print_trace_error("get angle failed\n");
        return FunctionResult::FAILURE;
    }
    return angle[fingetid - 1];
}

/// @brief Gets the finger Angular speed of the specified hand
/// @param HandType
///     @param  -LEFT_HAND
///     @param  -RIGHT_HAND
/// @param fingetid
///     @param  -THUMB_A
///     @param  -LITTLE_F
///     @param  -MIDDLE_F
///     @param  -THUMB_B
///     @param  -FORE_F
///     @param  -RING_F
/// @return angular speed
float DH::get_speed(HandTypeDef HandType, FingerTypeDef fingetid)
{
    float speed[6] = {0};
    if (HandControl->do_fdb(HandType, GET_SPEED, PARSE_FLOAT, (void *)speed) == FunctionResult::FAILURE)
    {
        Logger::get_instance()->print_trace_error("get speed failed\n");
        return FunctionResult::FAILURE;
    }
    return speed[fingetid - 1];
}

/// @brief Gets the finger current of the specified hand
/// @param HandType
///     @param  -LEFT_HAND
///     @param  -RIGHT_HAND
/// @param fingetid
///     @param  -THUMB_A
///     @param  -LITTLE_F
///     @param  -MIDDLE_F
///     @param  -THUMB_B
///     @param  -FORE_F
///     @param  -RING_F
/// @return current
float DH::get_current(HandTypeDef HandType, FingerTypeDef fingetid)
{
    float current[6] = {0};
    if (HandControl->do_fdb(HandType, GET_CURRENT, PARSE_FLOAT, (void *)current) == FunctionResult::FAILURE)
    {
        Logger::get_instance()->print_trace_error("get current failed\n");
        return FunctionResult::FAILURE;
    }
    return current[fingetid - 1];
}

/// @brief Gets the finger status of the specified hand
/// @param HandType
///     @param  -LEFT_HAND
///     @param  -RIGHT_HAND
/// @param fingetid
///     @param  -THUMB_A
///     @param  -LITTLE_F
///     @param  -MIDDLE_F
///     @param  -THUMB_B
///     @param  -FORE_F
///     @param  -RING_F
/// @return status
uint8_t DH::get_status(HandTypeDef HandType, FingerTypeDef fingetid)
{
    uint8_t status[6] = {0};
    if (HandControl->do_fdb(HandType, GET_STATUS, PARSE_UINT8, (void *)status) == FunctionResult::FAILURE)
    {
        Logger::get_instance()->print_trace_error("get status failed\n");
        return FunctionResult::FAILURE;
    }
    return status[fingetid - 1];
}

/// @brief Gets the finger errorcode of the specified hand
/// @param HandType
///     @param  -LEFT_HAND
///     @param  -RIGHT_HAND
/// @param fingetid
///     @param  -THUMB_A
///     @param  -LITTLE_F
///     @param  -MIDDLE_F
///     @param  -THUMB_B
///     @param  -FORE_F
///     @param  -RING_F
/// @return errorcode
long DH::get_errorcode(HandTypeDef HandType, FingerTypeDef fingetid)
{
    long errorcode[6] = {0};
    if (HandControl->do_fdb(HandType, GET_ERRORCODE, PARSE_LONG, (void *)errorcode) == FunctionResult::FAILURE)
    {
        Logger::get_instance()->print_trace_error("get errorcode failed\n");
        return FunctionResult::FAILURE;
    }
    return errorcode[fingetid - 1];
}

/// @brief Gets the finger control type of the specified hand
/// @param HandType
///     @param  -LEFT_HAND
///     @param  -RIGHT_HAND
/// @param fingetid
///     @param  -THUMB_A
///     @param  -LITTLE_F
///     @param  -MIDDLE_F
///     @param  -THUMB_B
///     @param  -FORE_F
///     @param  -RING_F
/// @return control type
uint8_t DH::get_control_type(HandTypeDef HandType, FingerTypeDef fingetid)
{
    long controlType[6] = {0};
    if (HandControl->do_fdb(HandType, GET_CONTROL_TYPE, PARSE_UINT8, (void *)controlType) == FunctionResult::FAILURE)
    {
        Logger::get_instance()->print_trace_error("get controlType failed\n");
        return FunctionResult::FAILURE;
    }
    return controlType[fingetid - 1];
}

float DH::get_p(HandTypeDef HandType, FingerTypeDef fingetid)
{
    float Proportional[6] = {0};
    if (HandControl->do_fdb(HandType, GET_P, PARSE_FLOAT, (void *)Proportional) == FunctionResult::FAILURE)
    {
        Logger::get_instance()->print_trace_error("get pid->Proportional failed\n");
        return FunctionResult::FAILURE;
    }
    return Proportional[fingetid - 1];
}

float DH::get_i(HandTypeDef HandType, FingerTypeDef fingetid)
{
    float Integral[6] = {0};
    if (HandControl->do_fdb(HandType, GET_I, PARSE_FLOAT, (void *)Integral) == FunctionResult::FAILURE)
    {
        Logger::get_instance()->print_trace_error("get pid->Integral failed\n");
        return FunctionResult::FAILURE;
    }
    return Integral[fingetid - 1];
}

float DH::get_d(HandTypeDef HandType, FingerTypeDef fingetid)
{
    float Derivative[6] = {0};
    if (HandControl->do_fdb(HandType, GET_D, PARSE_FLOAT, (void *)Derivative) == FunctionResult::FAILURE)
    {
        Logger::get_instance()->print_trace_error("get pid->Derivative failed\n");
        return FunctionResult::FAILURE;
    }
    return Derivative[fingetid - 1];
}

float DH::get_angle_limited(HandTypeDef HandType, FingerTypeDef fingetid)
{
    float limitparam[6] = {0};
    if (HandControl->do_fdb(HandType, GET_ANGLE_LIMITED, PARSE_FLOAT, (void *)limitparam) == FunctionResult::FAILURE)
    {
        Logger::get_instance()->print_trace_error("get limitparam failed\n");
        return FunctionResult::FAILURE;
    }
    return limitparam[fingetid - 1];
}

float DH::get_speed_limited(HandTypeDef HandType, FingerTypeDef fingetid)
{
    float limitparam[6] = {0};
    if (HandControl->do_fdb(HandType, GET_SPEED_LIMITED, PARSE_FLOAT, (void *)limitparam) == FunctionResult::FAILURE)
    {
        Logger::get_instance()->print_trace_error("get limitparam failed\n");
        return FunctionResult::FAILURE;
    }
    return limitparam[fingetid - 1];
}

float DH::get_current_limited(HandTypeDef HandType, FingerTypeDef fingetid)
{
    float limitparam[6] = {0};
    if (HandControl->do_fdb(HandType, GET_CURRENT_LIMITED, PARSE_FLOAT, (void *)limitparam) == FunctionResult::FAILURE)
    {
        Logger::get_instance()->print_trace_error("get limitparam failed\n");
        return FunctionResult::FAILURE;
    }
    return limitparam[fingetid - 1];
}