#include "../include/dh.h"

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
        Logger::get_instance()->print_trace_debug("send output->");
        for (int i = 0; i < 2; i++)
        {
            std::cout << std::hex << static_cast<int>(this->send_msg[i]) << " ";
        }
        std::cout << std::endl;
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

    if (sendsize > 1)
    {
        // control communication not reply
        return FunctionResult::SUCCESS;
    }
    

    do
    {
        ret = recvfrom(this->dh_socket, this->recv_msg, BUFFSIZE, 0, (struct sockaddr *)&this->recv_addr, &sockaddr_len);
        if (ret <= 0)
        {
            // Logger::get_instance()->print_trace_warning("Cannot receive msg, ErrorCode: 1001\n");
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
            if (char(this->recv_msg[i]) == ' ')
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
        float data[18] = {0};
        uint8_t data_index = 0;
        char temp_data[20] = {0};
        uint8_t temp_index = 0;
        for (int i = 0; i < sizeof(this->recv_msg); i++)
        {
            if (char(this->recv_msg[i] == NULL))
            {
                break;
            }
            if (char(this->recv_msg[i]) == ' ')
            {
                data[data_index++] = strtof(temp_data, NULL);
#ifdef DEBUG
                Logger::get_instance()->print_trace_debug("data[%d]: %f\n", data_index - 1, data[data_index - 1]);
#endif // DEBUG
                temp_index = 0;
                memset(temp_data, 0, sizeof(temp_data));
                continue;
            }
            temp_data[temp_index++] = this->recv_msg[i];
        }
        memcpy(retmsg, data, sizeof(data));
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
            if (char(this->recv_msg[i]) == ' ')
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
            if (char(this->recv_msg[i]) == ' ')
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

std::vector<string> DHFingerSeq = 
{   
    "INDEX_F",
    "MIDDLE_F",
    "RING_F",
    "PINKY_F",
    "THUMB_A",
    "THUMB_B"
};

std::vector<string> DHLoopSeq = 
{   "POSITION",
    "OMEGA",
    "CURRENT",
};

/// @brief calibrate left and right hand
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

/// @brief Specify the type of hand to calibrate
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

/// @brief Shut down movements of two hands immediately
/// @return -1 or 0
///     @note -1 means failed
///     @note  0 means success
int DH::emergency_stop()
{
    uint8_t buff[2] = {0x01, 0x0b};
    if ((HandControl->do_ctrl(LEFT_HAND, buff, sizeof(buff)) == FunctionResult::FAILURE)||(HandControl->do_ctrl(LEFT_HAND, buff, sizeof(buff)) == FunctionResult::FAILURE))
    {
        return FunctionResult::FAILURE;
    }
    return FunctionResult::SUCCESS;
}

/// @brief Shut down movements of a specified hand immediately
/// @return -1 or 0
///     @note -1 means failed
///     @note  0 means success
int DH::emergency_stop(HandTypeDef HandType)
{
    uint8_t buff[2] = {0x01, 0x0b};
    if (HandControl->do_ctrl(HandType, buff, sizeof(buff)) == FunctionResult::FAILURE)
    {
        return FunctionResult::FAILURE;
    }
    return FunctionResult::SUCCESS;
}

/*****set the hand of controller's parameter*****/
/// @brief Set the finger pid parameter of the specified hand
/// @param HandType
///     @param  -LEFT_HAND
///     @param  -RIGHT_HAND
/// @param tar_loop
///     @param  -POSITION
///     @param  -OMEGA
///     @param  -CURRENT
/// @param fingetid
///     @param  -INDEX_F
///     @param  -MIDDLE_F
///     @param  -RING_F
///     @param  -PINKY_F
///     @param  -THUMB_A
///     @param  -THUMB_B
/// @param _p
/// @param _i
/// @param _d
/// @return -1 or 0
///     @note -1 means failed
///     @note  0 means success
int DH::set_pid(HandTypeDef HandType, LoopTypeDef tar_loop, FingerTypeDef fingerid, float _p, float _i, float _d)
{
    if ((_p < 0) || (_i < 0) || (_d < 0))
    {
        Logger::get_instance()->print_trace_error("_p _i _d have to be positive\n");
        return FunctionResult::FAILURE;
    }
    
    uint8_t msg[16] = {0};
    msg[0] = 0x01;

    switch (tar_loop)
    {
    case POSITION:
        msg[1] = 0x05;        
        break;
    case OMEGA:
        msg[1] = 0x06;        
        break;
    case CURRENT:
        msg[1] = 0x07;        
        break;
    default:
        Logger::get_instance()->print_trace_error("Unexpected Error\n");
        return FunctionResult::FAILURE;
    }
    msg[2] = 0x00;
    msg[3] = (uint8_t)(fingerid);
    
    unsigned int temp = *(unsigned int *)&_p;
    msg[4] = (temp >> 24) & 0xFF;
    msg[5] = (temp >> 16) & 0xFF;
    msg[6] = (temp >> 8) & 0xFF;
    msg[7] = (temp >> 0) & 0xFF;
    temp = *(unsigned int *)&_i;
    msg[8] = (temp >> 24) & 0xFF;
    msg[9] = (temp >> 16) & 0xFF;
    msg[10] = (temp >> 8) & 0xFF;
    msg[11] = (temp >> 0) & 0xFF;
    temp = *(unsigned int *)&_d;
    msg[12] = (temp >> 24) & 0xFF;
    msg[13] = (temp >> 16) & 0xFF;
    msg[14] = (temp >> 8) & 0xFF;
    msg[15] = (temp >> 0) & 0xFF;
    

    if (HandControl->do_ctrl(HandType, msg, sizeof(msg)) == FunctionResult::FAILURE)
    {
        return FunctionResult::FAILURE;
    }
    return FunctionResult::SUCCESS;    
}

/// @brief Set the finger target of the specified hand
/// @param HandType
///     @param  -LEFT_HAND
///     @param  -RIGHT_HAND
/// @param tar_loop
///     @param  -POSITION
///     @param  -OMEGA
///     @param  -CURRENT
/// @param fingetid
///     @param  -INDEX_F
///     @param  -MIDDLE_F
///     @param  -RING_F
///     @param  -PINKY_F
///     @param  -THUMB_A
///     @param  -THUMB_B
/// @param _target
/// @return -1 or 0
///     @note -1 means failed
///     @note  0 means success
int DH::set_target(HandTypeDef HandType, LoopTypeDef tar_loop, FingerTypeDef fingerid, float _target)
{
    uint8_t msg[8] = {0};
    msg[0] = 0x01;

    switch (tar_loop)
    {
    case POSITION:
        msg[1] = 0x02;        
        break;
    case OMEGA:
        msg[1] = 0x03;        
        break;
    case CURRENT:
        msg[1] = 0x04;        
        break;
    default:
        Logger::get_instance()->print_trace_error("Unexpected Error\n");
        return FunctionResult::FAILURE;
    }
    msg[2] = 0x00;
    msg[3] = (uint8_t)(fingerid);
    
    unsigned int temp = *(unsigned int *)&_target;
    msg[4] = (temp >> 24) & 0xFF;
    msg[5] = (temp >> 16) & 0xFF;
    msg[6] = (temp >> 8) & 0xFF;
    msg[7] = (temp >> 0) & 0xFF;

    if (HandControl->do_ctrl(HandType, msg, sizeof(msg)) == FunctionResult::FAILURE)
    {
        return FunctionResult::FAILURE;
    }
    return FunctionResult::SUCCESS;  
}

/// @brief Set the finger limit of the specified hand
/// @param HandType
///     @param  -LEFT_HAND
///     @param  -RIGHT_HAND
/// @param tar_loop
///     @param  -POSITION
///     @param  -OMEGA
///     @param  -CURRENT
/// @param fingetid
///     @param  -INDEX_F
///     @param  -MIDDLE_F
///     @param  -RING_F
///     @param  -PINKY_F
///     @param  -THUMB_A
///     @param  -THUMB_B
/// @param maxValue
/// @return -1 or 0
///     @note -1 means failed
///     @note  0 means success
int DH::set_limit(HandTypeDef HandType, LoopTypeDef tar_loop, FingerTypeDef fingerid, float maxValue)
{
    uint8_t msg[8] = {0};
    msg[0] = 0x01;

    switch (tar_loop)
    {
    case POSITION:
        msg[1] = 0x08;        
        break;
    case OMEGA:
        msg[1] = 0x09;        
        break;
    case CURRENT:
        msg[1] = 0x0a;        
        break;
    default:
        Logger::get_instance()->print_trace_error("Unexpected Error\n");
        return FunctionResult::FAILURE;
    }
    msg[2] = 0x00;
    msg[3] = (uint8_t)(fingerid);
    
    unsigned int temp = *(unsigned int *)&maxValue;
    msg[4] = (temp >> 24) & 0xFF;
    msg[5] = (temp >> 16) & 0xFF;
    msg[6] = (temp >> 8) & 0xFF;
    msg[7] = (temp >> 0) & 0xFF;

    if (HandControl->do_ctrl(HandType, msg, sizeof(msg)) == FunctionResult::FAILURE)
    {
        return FunctionResult::FAILURE;
    }
    return FunctionResult::SUCCESS;  
}

/*****get the hand of controller's feedback*****/

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
    memcpy(ret, buff, sizeof(ret));
    return std::string(ret);
}

/// @brief Get encoder register cnt value
/// @param HandType
///     @param  -LEFT_HAND
///     @param  -RIGHT_HAND
/// @param fingetid
///     @param  -INDEX_F
///     @param  -MIDDLE_F
///     @param  -RING_F
///     @param  -PINKY_F
///     @param  -THUMB_A
///     @param  -THUMB_B
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

/// @brief Get the finger position of the specified hand
/// @param HandType
///     @param  -LEFT_HAND
///     @param  -RIGHT_HAND
/// @param fingetid
///     @param  -INDEX_F
///     @param  -MIDDLE_F
///     @param  -RING_F
///     @param  -PINKY_F
///     @param  -THUMB_A
///     @param  -THUMB_B
/// @return position
float DH::get_position(HandTypeDef HandType, FingerTypeDef fingetid)
{
    float data[18] = {0};
    if (HandControl->do_fdb(HandType, GET_ANGLE, PARSE_FLOAT, (void *)data) == FunctionResult::FAILURE)
    {
        Logger::get_instance()->print_trace_error("get position failed\n");
        return FunctionResult::FAILURE;
    }
    return data[fingetid - 1];
}

/// @brief Get the finger angular speed of the specified hand
/// @param HandType
///     @param  -LEFT_HAND
///     @param  -RIGHT_HAND
/// @param fingetid
///     @param  -INDEX_F
///     @param  -MIDDLE_F
///     @param  -RING_F
///     @param  -PINKY_F
///     @param  -THUMB_A
///     @param  -THUMB_B
/// @return angular speed
float DH::get_omega(HandTypeDef HandType, FingerTypeDef fingetid)
{
    float data[18] = {0};
    if (HandControl->do_fdb(HandType, GET_OMEGA, PARSE_FLOAT, (void *)data) == FunctionResult::FAILURE)
    {
        Logger::get_instance()->print_trace_error("get omega failed\n");
        return FunctionResult::FAILURE;
    }
    return data[fingetid - 1];
}

/// @brief Get the finger current of the specified hand
/// @param HandType
///     @param  -LEFT_HAND
///     @param  -RIGHT_HAND
/// @param fingetid
///     @param  -INDEX_F
///     @param  -MIDDLE_F
///     @param  -RING_F
///     @param  -PINKY_F
///     @param  -THUMB_A
///     @param  -THUMB_B
/// @return current
float DH::get_current(HandTypeDef HandType, FingerTypeDef fingetid)
{
    float data[18] = {0};
    if (HandControl->do_fdb(HandType, GET_CURRENT, PARSE_FLOAT, (void *)data) == FunctionResult::FAILURE)
    {
        Logger::get_instance()->print_trace_error("get current failed\n");
        return FunctionResult::FAILURE;
    }
    return data[fingetid - 1];
}

/// @brief Get the finger status of the specified hand
/// @param HandType
///     @param  -LEFT_HAND
///     @param  -RIGHT_HAND
/// @param fingetid
///     @param  -INDEX_F
///     @param  -MIDDLE_F
///     @param  -RING_F
///     @param  -PINKY_F
///     @param  -THUMB_A
///     @param  -THUMB_B
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

/// @brief Get the finger errorcode of the specified hand
/// @param HandType
///     @param  -LEFT_HAND
///     @param  -RIGHT_HAND
/// @param fingetid
///     @param  -INDEX_F
///     @param  -MIDDLE_F
///     @param  -RING_F
///     @param  -PINKY_F
///     @param  -THUMB_A
///     @param  -THUMB_B
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

/// @brief Print the finger pid parameter of the specified hand
/// @param HandType
///     @param  -LEFT_HAND
///     @param  -RIGHT_HAND
/// @param tar_loop
///     @param  -POSITION
///     @param  -OMEGA
///     @param  -CURRENT
/// @param fingetid
///     @param  -INDEX_F
///     @param  -MIDDLE_F
///     @param  -RING_F
///     @param  -PINKY_F
///     @param  -THUMB_A
///     @param  -THUMB_B
/// @return -1 or 0
///     @note -1 means failed
///     @note  0 means success
int DH::get_pid(HandTypeDef HandType, LoopTypeDef tar_loop, FingerTypeDef fingetid)
{
    float data[18] = {0};
    switch (tar_loop)
    {
    case POSITION:
        if (HandControl->do_fdb(HandType, GET_PID_ANGLE, PARSE_FLOAT, (void *)data) == FunctionResult::FAILURE)
        {
            Logger::get_instance()->print_trace_error("get pid position failed\n");
            return FunctionResult::FAILURE;
        }  
        break;
    case OMEGA:
        if (HandControl->do_fdb(HandType, GET_PID_OMEGA, PARSE_FLOAT, (void *)data) == FunctionResult::FAILURE)        
        {
            Logger::get_instance()->print_trace_error("get pid omega failed\n");
            return FunctionResult::FAILURE;
        }
        break;
    case CURRENT:
        if (HandControl->do_fdb(HandType, GET_PID_CURRENT, PARSE_FLOAT, (void *)data) == FunctionResult::FAILURE)        
        {
            Logger::get_instance()->print_trace_error("get pid current failed\n");
            return FunctionResult::FAILURE;
        }
        break;
    default:
            Logger::get_instance()->print_trace_error("Unexpected Error\n");
            return FunctionResult::FAILURE;
    }
    cout << DHFingerSeq[fingetid-1] << "|" << DHLoopSeq[tar_loop] << ":" << " p:" << data[(fingetid-1)*3]<< " i:" << data[(fingetid-1)*3+1]<< " d:" << data[(fingetid-1)*3+2] << endl;  
    return FunctionResult::SUCCESS;
}

/// @brief Print the finger limit of the specified hand
/// @param HandType
///     @param  -LEFT_HAND
///     @param  -RIGHT_HAND
/// @param tar_loop
///     @param  -POSITION
///     @param  -OMEGA
///     @param  -CURRENT
/// @param fingetid
///     @param  -INDEX_F
///     @param  -MIDDLE_F
///     @param  -RING_F
///     @param  -PINKY_F
///     @param  -THUMB_A
///     @param  -THUMB_B
/// @return -1 or 0
///     @note -1 means failed
///     @note  0 means success
int DH::get_limit(HandTypeDef HandType, LoopTypeDef tar_loop, FingerTypeDef fingetid)
{
    float data[18] = {0};
    switch (tar_loop)
    {
    case POSITION:
        if (HandControl->do_fdb(HandType, GET_ANGLE_LIMITED, PARSE_FLOAT, (void *)data) == FunctionResult::FAILURE)
        {
            Logger::get_instance()->print_trace_error("get limitparam failed\n");
            return FunctionResult::FAILURE;
        } 
        cout << DHFingerSeq[fingetid-1] << "|" << DHLoopSeq[tar_loop] << ":" << " limit: " << data[(fingetid-1)*2] << " - " << data[(fingetid-1)*2+1] << endl;  
        break;
    case OMEGA:
        if (HandControl->do_fdb(HandType, GET_OMEGA_LIMITED, PARSE_FLOAT, (void *)data) == FunctionResult::FAILURE)
        {
            Logger::get_instance()->print_trace_error("get limitparam failed\n");
            return FunctionResult::FAILURE;
        }
        cout << DHFingerSeq[fingetid-1] << "|" << DHLoopSeq[tar_loop] << ":" << " limit: " << '0' << " - " << data[fingetid-1] << endl;  
        break;
    case CURRENT:
        if (HandControl->do_fdb(HandType, GET_CURRENT_LIMITED, PARSE_FLOAT, (void *)data) == FunctionResult::FAILURE)        
        {
            Logger::get_instance()->print_trace_error("get limitparam failed\n");
            return FunctionResult::FAILURE;
        }
        cout << DHFingerSeq[fingetid-1] << "|" << DHLoopSeq[tar_loop] << ":" << " limit: " << '0' << " - " << data[fingetid-1] << endl;  
        break;
    default:
            Logger::get_instance()->print_trace_error("Unexpected Error\n");
            return FunctionResult::FAILURE;
    }
    return FunctionResult::SUCCESS;
}

/// @brief Get fdh interface version
/// @param HandType
///     @param  -LEFT_HAND
///     @param  -RIGHT_HAND
/// @return version
std::string DH::get_version(HandTypeDef HandType)
{
    char ret[16] = {0};
    char buff[1024] = {0};
    if (HandControl->do_fdb(HandType, GET_VERSION, PARSE_STRING, (void *)buff) == FunctionResult::FAILURE)
    {
        Logger::get_instance()->print_trace_error("get version failed\n");
        return "";
    }
    memcpy(ret, buff, sizeof(ret));
    return std::string(ret);
}