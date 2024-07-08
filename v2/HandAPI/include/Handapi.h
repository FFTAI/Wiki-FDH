/**
 *  2024.7.4
 * Gedit by fourier intelligent
 *
 */

#pragma once

#include <iostream>
#include <memory>
#include <chrono>
#include <cstring>
#include <vector>

#include "../../HandSocket/include/HandSocket.h"

using namespace HandSocket;

namespace HandProtocol
{

    class Handapi
    {
    /**
    * @brief this namespace for config of Dexterous HandSocket, include config parameters, send and receive commands.
    */

    private:
    /**
    * @brief flags config.
    */
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
    /**
    * @brief control and feedback socket config and time count config.
    */
        std::shared_ptr<Transmit::UDPSocket> ctrl_udp_socket;
        std::shared_ptr<Transmit::UDPSocket> comm_udp_socket;

        std::chrono::steady_clock::time_point begin;
        std::chrono::steady_clock::time_point end;
        std::chrono::milliseconds int_ms;

    public:
    /**
    * @brief get sensor params function and set config params function.
    */
        void init(const std::string &ip);
        /**
         * @fn InitPort
         * @brief set control and feedback port
         * @details init control port:2333 and feedback port: 2334
         * @return return result code, find in HandapiFunctionResult.h
         */
        int calibration();
        /**
         * @fn HandCalibration
         * @brief hand calibration
         * @details set current posotion as initial position, parameters reset
         * @return return result code, find in HandapiFunctionResult.h
         */

        // get sensor params
        int get_cnt(std::vector<long> &fdb);
        /**
         * @fn GetCountParams
         * @brief get encoder count params
         * @details receive 6 fingers count params : [index, middle, ring, little, thumb-1, thumb-2]
         * @return return result code, find in HandapiFunctionResult.h
         */
        int get_pos(std::vector<float> &fdb);
        /**
         * @fn GetHandPostion
         * @brief get hand motor move position params, not joint angle
         * @details receive 6 fingers motor position params: [index, middle, ring, little, thumb-1, thumb-2], defaut position is -0.5
         * @return return result code, find in HandapiFunctionResult.h
         */        
        int get_current(std::vector<float> &fdb);
        /**
         * @fn GetHandCurrent
         * @brief get hand motor current params
         * @details receive 6 fingers motor current params: [index, middle, ring, little, thumb-1, thumb-2]
         * @return return result code, find in HandapiFunctionResult.h
         */  
        int get_velocity(std::vector<float> &fdb);
        /**
         * @fn GetHandVelocity
         * @brief get hand motor velocity params
         * @details receive 6 fingers motor velocity params: [index, middle, ring, little, thumb-1, thumb-2]
         * @return return result code, find in HandapiFunctionResult.h
         */  
        int get_errorcode(std::vector<long> &fdb);
        /**
         * @fn GetHandError
         * @brief determine hand motor error, 0 means no error
         * @details receive 6 fingers error code : [index, middle, ring, little, thumb-1, thumb-2]
         * @return return result code, find in HandapiFunctionResult.h
         */  
        int get_status(std::vector<uint8_t> &fdb);
        /**
         * @fn GetHandStatus
         * @brief get hand motor status
         * @details receive 6 fingers status params : [index, middle, ring, little, thumb-1, thumb-2], 
         * @details status 0:before calibration/start, １:after calibration, 2:finish move , 3:move, 4:error
         * @return return result code, find in HandapiFunctionResult.h
         */ 
        int get_pos_limited(std::vector<float> &fdb);
        /**
         * @fn GetHandLimited (Position mode)
         * @brief get hand position limited bound, low is 0.0, high is 12.0
         * @details receive 6 fingers position high bound params : [index_low, index_high, middle_low, middle_high, ring_low, ring_high, little_low, little_high, thumb-1_low, thumb-1_high, thumb-2_low, thumb-2_high], 
         * @return return result code, find in HandapiFunctionResult.h
         */ 
        int get_velocity_limited(std::vector<float> &fdb);
        /**
         * @fn GetHandLimited (Velocity mode)
         * @brief get hand velocity limited bound, high bound is 10000.0
         * @details receive 6 fingers velocity params : [index, middle, ring, little, thumb-1, thumb-2], 
         * @return return result code, find in HandapiFunctionResult.h
         */ 
        int get_current_limited(std::vector<float> &fdb);
        /**
         * @fn GetHandLimited (Current mode)
         * @brief get hand current limited bound, high bound is 1000.0
         * @details receive 6 fingers current params : [index, middle, ring, little, thumb-1, thumb-2], 
         * @return return result code, find in HandapiFunctionResult.h
         */ 
        int get_ip(std::string &_ip);
        /**
         * @fn GetHandIPConfig
         * @brief get hand ip address
         * @details receive hand ip string, left: 192.168.137.39, right: 192.168.137.19 
         * @return return result code, find in HandapiFunctionResult.h
         */ 
        int get_firmware_version(std::string &ver);
        /**
         * @fn GetHandFirmwareVersion
         * @brief get hand firmware version 
         * @details receive hand version string 
         * @return return result code, find in HandapiFunctionResult.h
         */ 
        int get_pos_pid(std::vector<float> &fdb);
        /**
         * @fn GetPIDParams (Position mode)
         * @brief read position mode pid params 
         * @details read position mode pid default params : [p, i, d] 
         * @return return result code, find in HandapiFunctionResult.h
         */ 
        int get_velocity_pid(std::vector<float> &fdb);
        /**
         * @fn GetPIDParams (Velocity mode)
         * @brief read velocity mode pid params 
         * @details read velocity mode pid default params: [p, i, d] 
         * @return return result code, find in HandapiFunctionResult.h
         */ 
        int get_current_pid(std::vector<float> &fdb);
        /**
         * @fn GetPIDParams (Current mode)
         * @brief read current mode pid params 
         * @details read current mode pid default params : [p, i, d] 
         * @return return result code, find in HandapiFunctionResult.h
         */ 

        // set config params
        int set_velocity_limited(uint8_t id, float max_speed);
        /**
         * @fn SetLimitedParams (Velocity mode)
         * @brief set velocity control config params 
         * @details input one finger id : [1: index, 2: middle, 3: ring, 4: little, 5: thumb-1, 6: thumb-2] and max_speed
         * @return return result code, find in HandapiFunctionResult.h
         */ 
        int set_pos_limited(uint8_t id, float start_angel, float end_angle);
        /**
         * @fn SetLimitedParams (Position mode)
         * @brief set position control config params 
         * @details input one finger id : [1: index, 2: middle, 3: ring, 4: little, 5: thumb-1, 6: thumb-2], angle_low and angle_high
         * @return return result code, find in HandapiFunctionResult.h
         */ 
        int set_current_limited(uint8_t id, float max_current);
        /**
         * @fn SetLimitedParams (Current mode)
         * @brief set Current control config params 
         * @details input one finger id : [1: index, 2: middle, 3: ring, 4: little, 5: thumb-1, 6: thumb-2] and max_current
         * @return return result code, find in HandapiFunctionResult.h
         */ 
        int set_pos_pid(uint8_t id, std::vector<float> _pid);
        /**
         * @fn SetPIDParams (Position mode)
         * @brief set PID Position control config params 
         * @details input one finger id : [1: index, 2: middle, 3: ring, 4: little, 5: thumb-1, 6: thumb-2] and PID Params : [p, i, d]
         * @return return result code, find in HandapiFunctionResult.h
         */ 
        int set_velocity_pid(uint8_t id, std::vector<float> _pid);
        /**
         * @fn SetPIDParams (Velocity mode)
         * @brief set PID Velocity control config params 
         * @details input one finger id : [1: index, 2: middle, 3: ring, 4: little, 5: thumb-1, 6: thumb-2] and PID Params : [p, i, d]
         * @return return result code, find in HandapiFunctionResult.h
         */ 
        int set_current_pid(uint8_t id, std::vector<float> _pid);
        /**
         * @fn SetPIDParams (Current mode)
         * @brief set PID Current control config params 
         * @details input one finger id : [1: index, 2: middle, 3: ring, 4: little, 5: thumb-1, 6: thumb-2] and PID Params : [p, i, d]
         * @return return result code, find in HandapiFunctionResult.h
         */ 
        int set_pos(uint8_t id, float angel);
        /**
         * @fn SetControlConfig (Position mode)
         * @brief set Position move for one finger 
         * @details input one finger id : [1: index, 2: middle, 3: ring, 4: little, 5: thumb-1, 6: thumb-2] and position Params : pos
         * @return return result code, find in HandapiFunctionResult.h
         */ 
        int set_pos(std::vector<float> _cmd);
        /**
         * @fn SetControlConfig (Position mode)
         * @brief set Position move for all fingers 
         * @details input 6 fingers Position Params [index_pos, middle_pos, ring_pos, little_pos, thumb-1_pos, thumb-2_pos]
         * @return return result code, find in HandapiFunctionResult.h
         */ 
        int set_velocity(uint8_t id, float speed);
        /**
         * @fn SetControlConfig (Velocity mode)
         * @brief set Velocity move for one finger 
         * @details input one finger id : [1: index, 2: middle, 3: ring, 4: little, 5: thumb-1, 6: thumb-2] and Velocity Params : vel
         * @return return result code, find in HandapiFunctionResult.h
         */ 
        int set_velocity(std::vector<float> _cmd);
        /**
         * @fn SetControlConfig (Velocity mode)
         * @brief set Velocity move for all fingers 
         * @details input 6 fingers Velocity Params [index_vel, middle_vel, ring_vel, little_vel, thumb-1_vel, thumb-2_vel]
         * @return return result code, find in HandapiFunctionResult.h
         */ 
        int set_current(uint8_t id, float current);
        /**
         * @fn SetControlConfig (Current mode)
         * @brief set Current move for one finger 
         * @details input one finger id : [1: index, 2: middle, 3: ring, 4: little, 5: thumb-1, 6: thumb-2] and Current Params : cur
         * @return return result code, find in HandapiFunctionResult.h
         */ 
        int set_current(std::vector<float> _cmd);
        /**
         * @fn SetControlConfig (Current mode)
         * @brief set Current move for all fingers 
         * @details input 6 fingers Current Params [index_cur, middle_cur, ring_cur, little_cur, thumb-1_cur, thumb-2_cur]
         * @return return result code, find in HandapiFunctionResult.h
         */ 
        int set_pwm(uint8_t id, float current);
        /**
         * @fn SetControlConfig (PWM mode)
         * @brief set PWM move for one finger 
         * @details input one finger id : [1: index, 2: middle, 3: ring, 4: little, 5: thumb-1, 6: thumb-2] and PWM Params : pwm
         * @return return result code, find in HandapiFunctionResult.h
         */ 
        int set_pwm(std::vector<float> _cmd);
        /**
         * @fn SetControlConfig (PWM mode)
         * @brief set PWM move for all fingers 
         * @details input 6 fingers PWM Params [index_pwm, middle_pwm, ring_pwm, little_pwm, thumb-1_pwm, thumb-2_pwm]
         * @return return result code, find in HandapiFunctionResult.h
         */ 
        int set_force(uint8_t id, float current);
        /**
         * in progress
         */
        int set_force(std::vector<float> _cmd);
        /**
         * in progress
         */
        int set_pd_control(uint8_t id, float angel, float w);
        /**
         * @fn SetControlConfig (PD control mode)
         * @brief set PD control move for one finger 
         * @details input one finger id : [1: index, 2: middle, 3: ring, 4: little, 5: thumb-1, 6: thumb-2], position : position and omega : w 
         * @return return result code, find in HandapiFunctionResult.h
         */ 
    };
}