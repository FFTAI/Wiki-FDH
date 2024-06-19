#pragma once

#include <iostream>
#include <memory>
#include <chrono>
#include <cstring>
#include <vector>

#include "../../HandSocket/include/HandSocket.h"

#define DH_VERSION "v2.0.0.1"


using namespace HandSocket;
namespace HandProtocol
{
    class Handapi
    {
    private:
        std::string ip_;

        int calibration_flg = 0;
        int get_cnt_flg = 0;
        int get_pos_flg = 0;
        int get_current_flg = 0;
        int get_velocity_flg = 0;
        int get_errorcode_flg = 0;
        int get_status_flg = 0;
        int get_pos_limited_flg = 0;
        int get_velocity_limited_flg = 0;
        int get_current_limited_flg = 0;
        int get_ip_flg = 0;
        int get_pos_pid_flg = 0;
        int get_vel_pid_flg = 0;
        int get_cur_pid_flg = 0;
        int get_firmware_version_flg = 0;
        int get_software_version_flg = 0;
        int set_pos_limited_flg = 0;
        int set_velocity_limited_flg = 0;
        int set_current_limited_flg = 0;
        int set_pos_pid_flg = 0;
        int set_velocity_pid_flg = 0;
        int set_current_pid_flg = 0;
        int set_pos_flg = 0;
        int set_velocity_flg = 0;
        int set_current_flg = 0;
        int set_pd_control_flg = 0;

        int set_position_all = 0;
        int set_pwm_all = 0;

        uint32_t wait_replt_counts_max = 100000;

    public:
        std::shared_ptr<Transmit::UDPSocket> ctrl_udp_socket;
        std::shared_ptr<Transmit::UDPSocket> comm_udp_socket;

        std::chrono::steady_clock::time_point begin;
        std::chrono::steady_clock::time_point end;
        std::chrono::milliseconds int_ms;

    public:
        void init(const std::string &ip);
        int calibration();

        // get sensor data
        int get_cnt(std::vector<long> &fdb);
        int get_pos(std::vector<float> &fdb);
        int get_current(std::vector<float> &fdb);
        int get_velocity(std::vector<float> &fdb);

        int get_errorcode(std::vector<long> &fdb);
        int get_status(std::vector<uint8_t> &fdb);

        int get_pos_limited(std::vector<float> &fdb);
        int get_velocity_limited(std::vector<float> &fdb);
        int get_current_limited(std::vector<float> &fdb);

        int get_ip(std::string &_ip);
        int get_firmware_version(std::string &ver);

        int get_pos_pid(std::vector<float> &fdb);
        int get_velocity_pid(std::vector<float> &fdb);
        int get_current_pid(std::vector<float> &fdb);

        // set config params
        int set_velocity_limited(uint8_t id, float max_speed);
        int set_pos_limited(uint8_t id, float start_angel, float end_angle);
        int set_current_limited(uint8_t id, float max_current);

        int set_pos_pid(uint8_t id, std::vector<float> _pid);
        int set_velocity_pid(uint8_t id, std::vector<float> _pid);
        int set_current_pid(uint8_t id, std::vector<float> _pid);

        int set_pos(uint8_t id, float angel);
        int set_pos(std::vector<float> _cmd);

        int set_velocity(uint8_t id, float speed);
        int set_velocity(std::vector<float> _cmd);

        int set_current(uint8_t id, float current);
        int set_current(std::vector<float> _cmd);

        int set_pwm(uint8_t id, float current);
        int set_pwm(std::vector<float> _cmd);

        int set_force(uint8_t id, float current);
        int set_force(std::vector<float> _cmd);

        int set_pd_control(uint8_t id, float angel, float w);
    };
}