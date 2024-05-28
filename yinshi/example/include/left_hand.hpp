#ifndef UDP_HAND_API_H_left
#define UDP_HAND_API_H_left

#include <iostream>
#include <chrono>
#include <fstream>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <fcntl.h>
#include <cerrno>
#include <thread>
#include <string>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#define kSend_Frame_Head1 0xEB
#define kSend_Frame_Head2 0x90

#define kRcv_Frame_Head1 0x90
#define kRcv_Frame_Head2 0xEB

#define kCmd_Handg3_Read 0x11
#define kCmd_Handg3_Write 0x12

namespace left_hand_api
{

    struct UDPData_left
    {
        uint8_t m_send_array[1024];
        size_t m_tx_len;
        uint8_t m_rec_array[128];
    };

    class left_hand
    {
    private:
        static int call_count_left;

        uint8_t robotId;
        uint16_t jointAngles[6];
        uint16_t jointForces[6];
        uint16_t jointCurrents[6];
        uint8_t errorCodes[6];
        uint8_t statuses[6];
        char ipAddress[16];

        struct sockaddr_in serverAddr;
        int sockfd;
        UDPData_left UDP_Data;

        void setIpAddress(const char *ip);
        const char *getIpAddress() const;
        void setRobotId(uint8_t id);
        uint8_t getRobotId();
        void setJointCurrent(int jointNumber, uint16_t current);
        void setJointAngle(int jointNumber, uint16_t angle);
        void setJointForce(int jointNumber, uint16_t force);
        void setJointErrorCode(int jointNumber, uint8_t code);
        void setJointStatus(int jointNumber, uint8_t statusInfo);

        void SenderThread(double time_g);
        int Action_do(int act_number);
        int sin_do();
        int Action_SEQ_index(uint8_t ID, int index);
        int Action_SEQ_run(uint8_t ID);

    public:
        left_hand();

        /// @brief initialize
        int left_hand_init();

        /// @brief Set the speed of each degree of freedom
        /// @param ID Hand ID, default to 1
        /// @param val1 Pinky finger speed setting value, ranging from 1 to 1000.
        /// @param val2 Ring finger speed setting value, ranging from 1 to 1000
        /// @param val3 Middle finger speed setting value, ranging from 1 to 1000
        /// @param val4 Index finger speed setting value, ranging from 0 to 1000.
        /// @param val5 Thumb bending speed setting value, ranging from 0 to 1000
        /// @param val6 Thumb rotation speed setting value, ranging from 1 to 1000
        int Speed_Set(uint8_t ID, uint16_t val1, uint16_t val2, uint16_t val3, uint16_t val4, uint16_t val5, uint16_t val6);

        /// @brief Get error message
        /// @param ID Hand ID, default to 1
        /// @param time_g Instruction transmission speed
        int Error_Get(uint8_t ID, double time_g);

        /// @brief Received hand's return value
        void ReceiverThread();

        /// @brief Perform specified action
        /// @param key_number
        int key_do(int key_number);

        /// @brief Set angle
        /// @param ID Hand ID, default to 1
        /// @param val1 Pinky Angle setting, ranging from 1 to 1000
        /// @param val2 Ring finger Angle setting value, range 1-1000
        /// @param val3 Middle finger Angle setting value, range 1-1000
        /// @param val4 Index finger Angle setting value, range 1-1000
        /// @param val5 Thumb bend Angle Set value. The value ranges from 1 to 1000
        /// @param val6 Thumb rotation Angle setting value, range 1-1000
        /// @param time_g Instruction transmission speed
        int Angle_Set(uint8_t ID, uint16_t val1, uint16_t val2, uint16_t val3, uint16_t val4, uint16_t val5, uint16_t val6, double time_g);

        /// @brief Set angle
        /// @param ID Hand ID, default to 1
        /// @param val1 Pinky Angle setting, ranging from 1 to 1000
        /// @param val2 Ring finger Angle setting value, range 1-1000
        /// @param val3 Middle finger Angle setting value, range 1-1000
        /// @param val4 Index finger Angle setting value, range 1-1000
        /// @param val5 Thumb bend Angle Set value. The value ranges from 1 to 1000
        /// @param val6 Thumb rotation Angle setting value, range 1-1000
        /// @param time_g Instruction transmission speed
        /// @param _force set max force, range 1-1000，Modifying this value will modify the maximum limit of trapezoidal control algorithm and reduce the stutter effect caused by real-time control
        int Angle_Set(uint8_t ID, uint16_t val1, uint16_t val2, uint16_t val3, uint16_t val4, uint16_t val5, uint16_t val6, double time_g, uint16_t _force);

        /// @brief Set the force threshold for each degree of freedom
        /// @param ID Hand ID, default to 1
        /// @param val1 Pinky force setting value, ranging from 1 to 1000
        /// @param val2 Ring finger force setting value, range 1-1000
        /// @param val3 Force control setting value, range 1-1000
        /// @param val4 Index finger force control setting value, range 1-1000
        /// @param val5 Thumb flex force control setting, ranging from 1 to 1000
        /// @param val6 Thumb rotation force setting value, range 1-1000
        int Force_Set(uint8_t ID, uint16_t val1, uint16_t val2, uint16_t val3, uint16_t val4, uint16_t val5, uint16_t val6);

        /// @brief Force sensor calibration
        /// @param ID Hand ID, default to 1
        int Gesture_Force_Clb_Set(uint8_t ID);

        /// @brief Clear error message
        /// @param ID Hand ID, default to 1
        int Clean_error_Set(uint8_t ID);

        /// @brief Set the current protection value
        /// @param ID Hand ID, default to 1
        /// @param val1 Pinkie current protection value, range 1-1500
        /// @param val2 Ring finger current protection value, range 1-1500
        /// @param val3 Middle finger current protection value, range 1-1500
        /// @param val4 Index finger current protection value, range 1-1500
        /// @param val5 Thumb bend current protection value, range 1-1500
        /// @param val6 Thumb rotation current protection value, range 1-1500
        int Current_Limit_Set(uint8_t ID, uint16_t val1, uint16_t val2, uint16_t val3, uint16_t val4, uint16_t val5, uint16_t val6);

        /// @brief Get the Angle of each degree of freedom
        /// @param ID Hand ID, default to 1
        /// @param time_g Instruction transmission speed
        int Angle_Get(uint8_t ID, double time_g);

        /// @brief Get currents for each degree of freedom
        /// @param ID Hand ID, default to 1
        /// @param time_g Instruction transmission speed
        int Current_Get(uint8_t ID, double time_g);

        /// @brief The forces of each degree of freedom are obtained
        /// @param ID Hand ID, default to 1
        /// @param time_g Instruction transmission speed
        int Force_Get(uint8_t ID, double time_g);

        /// @brief Obtain state information for each degree of freedom
        /// @param ID Hand ID, default to 1
        /// @param time_g Instruction transmission speed
        int Status_Get(uint8_t ID, double time_g);

        /// @brief The current of the corresponding joint is obtained
        /// @param jointNumber
        /// @return The current corresponding to the joint
        uint16_t getJointCurrent(int jointNumber);

        /// @brief The current of the corresponding joint is obtained
        /// @param jointNumber
        /// @return The current corresponding to the joint
        uint16_t getJointAngle(int jointNumber);

        /// @brief The corresponding joint force sensor data were obtained
        /// @param jointNumber
        /// @return Corresponding to joint force sensor data
        uint16_t getJointForce(int jointNumber);

        /// @brief The error code of the corresponding joint is obtained
        /// @param jointNumber
        /// @return The error code of the corresponding joint
        uint8_t getJointErrorCode(int jointNumber);

        /// @brief The status code of the corresponding joint is obtained
        /// @param jointNumber
        /// @return The status code of the corresponding joint
        uint8_t getJointStatus(int jointNumber);
    };

    unsigned short combineTo16Bit(unsigned char highByte, unsigned char lowByte);
    uint16_t Crc16(uint16_t f_u16PloyVal, uint16_t f_u16InitVal, uint16_t f_u16XorOut, const void *f_pvBuf, uint16_t f_u16Len);

}
#endif