#ifndef _DH_H_
#define _DH_H_

#include <iostream>
#include <string.h>
#include <ctime>
#include <unistd.h>
#include <arpa/inet.h>
#include <sstream>
#include <vector>

#include "function_result.h"
#include "os.h"
#include "logger.h"

#define BROADCAST_IP "192.168.137.255"
#define LEFT_IP "192.168.137.39"
#define RIGHT_IP "192.168.137.19"
#define CTRL_PORT 2334
#define FDB_PORT 2333
#define BUFFSIZE 1024

#define DEBUG

namespace DH
{
    typedef enum
    {
        LEFT_HAND,
        RIGHT_HAND
    } HandTypeDef;

    typedef enum
    {
        GET_CNT = 0x01,
        GET_ANGLE,
        GET_SPEED,
        GET_CURRENT,
        GET_STATUS,
        GET_ERRORCODE,
        GET_CONTROL_TYPE,
        GET_P,
        GET_I,
        GET_D,
        GET_ANGLE_LIMITED,
        GET_SPEED_LIMITED,
        GET_CURRENT_LIMITED,
        GET_VERSION,
        GET_IP,
        GET_,
    } GetFdbControlWordTypeDef;

    typedef enum
    {
        POSITION,
        SPEED,
        CURRENT
    } LoopTypeDef;

    typedef enum
    {
        THUMB_A = 0x01,
        LITTLE_F = 0x02,
        MIDDLE_F = 0x03,
        THUMB_B = 0x04,
        FORE_F = 0x05,
        RING_F = 0x06
    } FingerTypeDef;

    typedef enum
    {
        NONE,
        PARSE_STRING,
        PARSE_LONG_LONG,
        PARSE_FLOAT,
        PARSE_UINT8,
        PARSE_LONG
    } ParseTypeDef;

    class DhCls
    {
    private:
        int isInit = 1;
        int dh_socket;
        struct sockaddr_in left_ctrl_addr, left_fdb_addr, right_ctrl_addr, right_fdb_addr, recv_addr;
        socklen_t sockaddr_len = sizeof(struct sockaddr_in);
        uint8_t send_msg[BUFFSIZE], recv_msg[BUFFSIZE];

    public:
    private:
        int init();
        int communicaiton(std::string ip, int port, int sendsize);
        int encode(uint8_t *en_msg, uint8_t msg_size);
        int decode(ParseTypeDef FdbType, void *retmsg);

    public:
        DhCls(/* args */);
        ~DhCls();

        int do_ctrl(HandTypeDef HandType, uint8_t *word, uint8_t msg_size);
        int do_fdb(HandTypeDef HandType, GetFdbControlWordTypeDef controlword, ParseTypeDef FdbType, void *fdbmsg);
        void obj2uint8arr(auto param, uint8_t *ret_arr, uint8_t arr_size);
    };

    /*****the hand of controller's interfaces*****/
    int calibration();
    int calibration(HandTypeDef HandType);

    int get_mechanical_limit();
    int get_mechanical_limit(HandTypeDef HandType);

    int emergency_stop();
    int emergency_stop(HandTypeDef HandType);
    /*****set the hand of controller's parameter*****/
    int set_pid(HandTypeDef HandType, LoopTypeDef tar_loop, FingerTypeDef fingerid, float _p, float _i, float _d);
    int set_target(HandTypeDef HandType, LoopTypeDef tar_loop, FingerTypeDef fingerid, float _target);
    int set_finger_limited(HandTypeDef HandType, LoopTypeDef tar_loop, FingerTypeDef fingerid, float minValue, float maxValue);

    /*****get the hand of controller's feedback*****/
    long long get_cnt(HandTypeDef HandType, FingerTypeDef fingetid);
    float get_angle(HandTypeDef HandType, FingerTypeDef fingetid);
    float get_speed(HandTypeDef HandType, FingerTypeDef fingetid);
    float get_current(HandTypeDef HandType, FingerTypeDef fingetid);
    uint8_t get_status(HandTypeDef HandType, FingerTypeDef fingetid);
    long get_errorcode(HandTypeDef HandType, FingerTypeDef fingetid);
    uint8_t get_control_type(HandTypeDef HandType, FingerTypeDef fingetid);

    float get_p(HandTypeDef HandType, FingerTypeDef fingetid);
    float get_i(HandTypeDef HandType, FingerTypeDef fingetid);
    float get_d(HandTypeDef HandType, FingerTypeDef fingetid);

    float get_angle_limited(HandTypeDef HandType, FingerTypeDef fingetid);
    float get_speed_limited(HandTypeDef HandType, FingerTypeDef fingetid);
    float get_current_limited(HandTypeDef HandType, FingerTypeDef fingetid);

    std::string get_ip(HandTypeDef HandType);
    std::string get_version(HandTypeDef HandType);
}

#endif // !_DH_H_