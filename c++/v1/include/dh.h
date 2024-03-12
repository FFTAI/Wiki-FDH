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
        GET_ANGLE = 0x02,
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
        int communicaiton(std::string ip, int port);
        int encode(uint8_t *en_msg, uint8_t msg_size);
        int decode(uint8_t *de_msg);

    public:
        DhCls(/* args */);
        ~DhCls();

        int do_ctrl(HandTypeDef HandType, uint8_t *word, uint8_t msg_size);
        int do_fdb(HandTypeDef HandType, GetFdbControlWordTypeDef controlword, void *fdbmsg);
    };

    /*****the hand of controller's interfaces*****/
    int calibration();
    int calibration(HandTypeDef HandType);

    int set_pid(LoopTypeDef tar_loop, float _p, float _i, float _d);
    int set_target(LoopTypeDef tar_loop, float _target);
    int set_finger_limited(FingerTypeDef fingerid, float minValue, float maxValue);

    /*****get the hand of controller's feedback*****/
    std::string get_ip();
    long long get_cnt();
    float get_angle(HandTypeDef HandType);
    float get_speed();
    float get_current();
    uint8_t get_status();
    long get_errorcode();
    uint8_t get_control_type();

}

#endif // !_DH_H_