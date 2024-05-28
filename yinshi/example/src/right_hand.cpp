#include <cstdio>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <cerrno>
#include <chrono>
#include <fstream>
#include <thread>
#include "../include/right_hand.hpp"
#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <arpa/inet.h>
#include <sstream>
#include <string>
#include <mutex>
#include <condition_variable>
#include <cstdint>
#include <math.h>

using namespace std;

namespace right_hand_api
{

	right_hand::right_hand()
	{
		robotId = 1;
		for (int i = 0; i < 6; i++)
		{
			jointAngles[i] = 0;
			jointCurrents[i] = 0;
			jointForces[i] = 0;
			errorCodes[i] = 0;
			statuses[i] = 0;
			strncpy(ipAddress, "192.168.137.19", sizeof(ipAddress) - 1);
			ipAddress[sizeof(ipAddress) - 1] = '\0';
		}
	}
	void right_hand::setIpAddress(const char *ip)
	{
		strncpy(ipAddress, ip, sizeof(ipAddress) - 1);
		ipAddress[sizeof(ipAddress) - 1] = '\0';
		std::cout << "NEW IP address: " << ip << std::endl;
	}

	const char *right_hand::getIpAddress() const
	{
		return ipAddress;
	}

	void right_hand::setRobotId(uint8_t id)
	{
		robotId = id;
	}

	uint8_t right_hand::getRobotId()
	{
		return robotId;
	}

	void right_hand::setJointCurrent(int jointNumber, uint16_t current)
	{
		if (jointNumber >= 0 && jointNumber < 6)
		{
			jointCurrents[jointNumber] = current;
		}
		else
		{
			std::cerr << "Invalid joint number" << std::endl;
		}
	}

	uint16_t right_hand::getJointCurrent(int jointNumber)
	{
		if (jointNumber >= 0 && jointNumber < 6)
		{
			return jointCurrents[jointNumber];
		}
		else
		{
			std::cerr << "Invalid joint number" << std::endl;
			return 0;
		}
	}

	void right_hand::setJointAngle(int jointNumber, uint16_t angle)
	{
		if (jointNumber >= 0 && jointNumber < 6)
		{
			jointAngles[jointNumber] = angle;
		}
		else
		{
			std::cerr << "Invalid joint number" << std::endl;
		}
	}

	uint16_t right_hand::getJointAngle(int jointNumber)
	{
		if (jointNumber >= 0 && jointNumber < 6)
		{
			return jointAngles[jointNumber];
		}
		else
		{
			std::cerr << "Invalid joint number" << std::endl;
			return 0;
		}
	}

	void right_hand::setJointForce(int jointNumber, uint16_t force)
	{
		if (jointNumber >= 0 && jointNumber < 6)
		{
			jointForces[jointNumber] = force;
		}
		else
		{
			std::cerr << "Invalid joint number" << std::endl;
		}
	}

	uint16_t right_hand::getJointForce(int jointNumber)
	{
		if (jointNumber >= 0 && jointNumber < 6)
		{
			return jointForces[jointNumber];
		}
		else
		{
			std::cerr << "Invalid joint number" << std::endl;
			return 0;
		}
	}

	void right_hand::setJointErrorCode(int jointNumber, uint8_t code)
	{
		if (jointNumber >= 0 && jointNumber < 6)
		{
			errorCodes[jointNumber] = code;
		}
		else
		{
			std::cerr << "Invalid joint number" << std::endl;
		}
	}

	uint8_t right_hand::getJointErrorCode(int jointNumber)
	{
		if (jointNumber >= 0 && jointNumber < 6)
		{
			return errorCodes[jointNumber];
		}
		else
		{
			std::cerr << "Invalid joint number" << std::endl;
			return 0;
		}
	}

	void right_hand::setJointStatus(int jointNumber, uint8_t statusInfo)
	{
		if (jointNumber >= 0 && jointNumber < 6)
		{
			statuses[jointNumber] = statusInfo;
		}
		else
		{
			std::cerr << "Invalid joint number" << std::endl;
		}
	}

	uint8_t right_hand::getJointStatus(int jointNumber)
	{
		if (jointNumber >= 0 && jointNumber < 6)
		{
			return statuses[jointNumber];
		}
		else
		{
			std::cerr << "Invalid joint number" << std::endl;
			return 0;
		}
	}

	int right_hand::right_hand_init()
	{
		sockfd = socket(AF_INET, SOCK_DGRAM, 0);
		if (sockfd < 0)
		{
			perror("Error in socket");
			return 1;
		}
		// Set server address
		memset(&serverAddr, 0, sizeof(serverAddr));
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons(2333);
		serverAddr.sin_addr.s_addr = inet_addr("192.168.137.19");
		std::cout << "sockfd_init:" << sockfd << endl;
		return sockfd;
	}

	void right_hand::SenderThread(double time_g)
	{
		auto start = std::chrono::system_clock::now();
		while (true)
		{
			auto duration =
				std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count();
			if (duration > time_g)
			{
				int ret = sendto(sockfd, UDP_Data.m_send_array, UDP_Data.m_tx_len, 0, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
				if (ret == -1)
				{
					perror("sendto");
					exit(EXIT_FAILURE);
				}
				break;
			}
		}
	}

	int right_hand::Angle_Set(uint8_t ID, uint16_t val1, uint16_t val2, uint16_t val3, uint16_t val4, uint16_t val5, uint16_t val6, double time_g)
	{
		uint8_t i = 0;
		uint8_t m_unChecksum = 0;
		UDP_Data.m_send_array[0] = kSend_Frame_Head1;
		UDP_Data.m_send_array[1] = kSend_Frame_Head2;
		UDP_Data.m_send_array[2] = ID;
		UDP_Data.m_send_array[3] = 0x0F;
		UDP_Data.m_send_array[4] = kCmd_Handg3_Write;
		UDP_Data.m_send_array[5] = 0xCE;
		UDP_Data.m_send_array[6] = 0x05;
		UDP_Data.m_send_array[7] = val1 & 0xFF;
		UDP_Data.m_send_array[8] = val1 >> 8;
		UDP_Data.m_send_array[9] = val2 & 0xFF;
		UDP_Data.m_send_array[10] = val2 >> 8;
		UDP_Data.m_send_array[11] = val3 & 0xFF;
		UDP_Data.m_send_array[12] = val3 >> 8;
		UDP_Data.m_send_array[13] = val4 & 0xFF;
		UDP_Data.m_send_array[14] = val4 >> 8;
		UDP_Data.m_send_array[15] = val5 & 0xFF;
		UDP_Data.m_send_array[16] = val5 >> 8;
		UDP_Data.m_send_array[17] = val6 & 0xFF;
		UDP_Data.m_send_array[18] = val6 >> 8;
		for (i = 2; i < 19; i++)
		{
			m_unChecksum += UDP_Data.m_send_array[i];
		}
		UDP_Data.m_send_array[19] = m_unChecksum & 0xFF;
		UDP_Data.m_tx_len = 20;
		SenderThread(time_g);
		return 0;
	}

	int right_hand::Angle_Set(uint8_t ID, uint16_t val1, uint16_t val2, uint16_t val3, uint16_t val4, uint16_t val5, uint16_t val6, double time_g, uint16_t _force)
	{
		uint8_t i = 0;
		uint8_t m_unChecksum = 0;
		UDP_Data.m_send_array[0] = kSend_Frame_Head1;
		UDP_Data.m_send_array[1] = kSend_Frame_Head2;
		UDP_Data.m_send_array[2] = ID;
		UDP_Data.m_send_array[3] = 0x17;
		UDP_Data.m_send_array[4] = 0x20;
		UDP_Data.m_send_array[5] = val1 & 0xFF;
		UDP_Data.m_send_array[6] = val1 >> 8;
		UDP_Data.m_send_array[7] = val2 & 0xFF;
		UDP_Data.m_send_array[8] = val2 >> 8;
		UDP_Data.m_send_array[9] = val3 & 0xFF;
		UDP_Data.m_send_array[10] = val3 >> 8;
		UDP_Data.m_send_array[11] = val4 & 0xFF;
		UDP_Data.m_send_array[12] = val4 >> 8;
		UDP_Data.m_send_array[13] = val5 & 0xFF;
		UDP_Data.m_send_array[14] = val5 >> 8;
		UDP_Data.m_send_array[15] = val6 & 0xFF;
		UDP_Data.m_send_array[16] = val6 >> 8;

		UDP_Data.m_send_array[17] = _force & 0xFF;
		UDP_Data.m_send_array[18] = _force >> 8;
		UDP_Data.m_send_array[19] = _force & 0xFF;
		UDP_Data.m_send_array[20] = _force >> 8;
		UDP_Data.m_send_array[21] = _force & 0xFF;
		UDP_Data.m_send_array[22] = _force >> 8;
		UDP_Data.m_send_array[23] = _force & 0xFF;
		UDP_Data.m_send_array[24] = _force >> 8;
		UDP_Data.m_send_array[25] = _force & 0xFF;
		UDP_Data.m_send_array[26] = _force >> 8;

		for (i = 2; i < 27; i++)
		{
			m_unChecksum += UDP_Data.m_send_array[i];
		}
		UDP_Data.m_send_array[27] = m_unChecksum & 0xFF;
		UDP_Data.m_tx_len = 28;
		SenderThread(time_g);
		return 0;
	}

	int right_hand::Force_Set(uint8_t ID, uint16_t val1, uint16_t val2, uint16_t val3, uint16_t val4, uint16_t val5, uint16_t val6)
	{
		uint8_t i = 0;
		uint8_t m_unChecksum = 0;

		if (val1 < 1 || val1 > 1000 || val2 < 1 || val2 > 1000 || val3 < 1 || val3 > 1000 ||
			val4 < 1 || val4 > 1000 || val5 < 1 || val5 > 1000 || val6 < 1 || val6 > 1000)
		{
			std::cout << "Out of range!" << endl;
			return -1;
		}
		UDP_Data.m_send_array[0] = kSend_Frame_Head1;
		UDP_Data.m_send_array[1] = kSend_Frame_Head2;
		UDP_Data.m_send_array[2] = ID;
		UDP_Data.m_send_array[3] = 0x0F;
		UDP_Data.m_send_array[4] = kCmd_Handg3_Write;
		UDP_Data.m_send_array[5] = 0x14;
		UDP_Data.m_send_array[6] = 0x04;
		UDP_Data.m_send_array[7] = val1 & 0xFF;
		UDP_Data.m_send_array[8] = val1 >> 8;
		UDP_Data.m_send_array[9] = val2 & 0xFF;
		UDP_Data.m_send_array[10] = val2 >> 8;
		UDP_Data.m_send_array[11] = val3 & 0xFF;
		UDP_Data.m_send_array[12] = val3 >> 8;
		UDP_Data.m_send_array[13] = val4 & 0xFF;
		UDP_Data.m_send_array[14] = val4 >> 8;
		UDP_Data.m_send_array[15] = val5 & 0xFF;
		UDP_Data.m_send_array[16] = val5 >> 8;
		UDP_Data.m_send_array[17] = val6 & 0xFF;
		UDP_Data.m_send_array[18] = val6 >> 8;
		for (i = 2; i < 19; i++)
		{
			m_unChecksum += UDP_Data.m_send_array[i];
		}
		UDP_Data.m_send_array[19] = m_unChecksum & 0xFF;
		UDP_Data.m_tx_len = 20;
		SenderThread(0);
		return 0;
	}

	int right_hand::Gesture_Force_Clb_Set(uint8_t ID)
	{
		uint8_t i = 0;
		uint8_t m_unChecksum = 0;
		UDP_Data.m_send_array[0] = kSend_Frame_Head1;
		UDP_Data.m_send_array[1] = kSend_Frame_Head2;
		UDP_Data.m_send_array[2] = ID;
		UDP_Data.m_send_array[3] = 0x04;
		UDP_Data.m_send_array[4] = kCmd_Handg3_Write;
		UDP_Data.m_send_array[5] = 0xF1;
		UDP_Data.m_send_array[6] = 0x03;
		UDP_Data.m_send_array[7] = 0x01;
		for (i = 2; i < 8; i++)
		{
			m_unChecksum += UDP_Data.m_send_array[i];
		}
		UDP_Data.m_send_array[8] = m_unChecksum & 0xFF;
		UDP_Data.m_tx_len = 9;
		SenderThread(0);
		return 0;
	}

	int right_hand::Speed_Set(uint8_t ID, uint16_t val1, uint16_t val2, uint16_t val3, uint16_t val4, uint16_t val5, uint16_t val6)
	{
		uint8_t i = 0;
		uint8_t m_unChecksum = 0;
		UDP_Data.m_send_array[0] = kSend_Frame_Head1;
		UDP_Data.m_send_array[1] = kSend_Frame_Head2;
		UDP_Data.m_send_array[2] = ID;
		UDP_Data.m_send_array[3] = 0x0F;
		UDP_Data.m_send_array[4] = kCmd_Handg3_Write;
		UDP_Data.m_send_array[5] = 0xF2;
		UDP_Data.m_send_array[6] = 0x05;
		UDP_Data.m_send_array[7] = val1 & 0xFF;
		UDP_Data.m_send_array[8] = val1 >> 8;
		UDP_Data.m_send_array[9] = val2 & 0xFF;
		UDP_Data.m_send_array[10] = val2 >> 8;
		UDP_Data.m_send_array[11] = val3 & 0xFF;
		UDP_Data.m_send_array[12] = val3 >> 8;
		UDP_Data.m_send_array[13] = val4 & 0xFF;
		UDP_Data.m_send_array[14] = val4 >> 8;
		UDP_Data.m_send_array[15] = val5 & 0xFF;
		UDP_Data.m_send_array[16] = val5 >> 8;
		UDP_Data.m_send_array[17] = val6 & 0xFF;
		UDP_Data.m_send_array[18] = val6 >> 8;
		for (i = 2; i < 19; i++)
		{
			m_unChecksum += UDP_Data.m_send_array[i];
		}
		UDP_Data.m_send_array[19] = m_unChecksum & 0xFF;
		UDP_Data.m_tx_len = 20;
		SenderThread(0);
		return 0;
	}

	int right_hand::Clean_error_Set(uint8_t ID)
	{
		uint8_t i = 0;
		uint8_t m_unChecksum = 0;
		UDP_Data.m_send_array[0] = kSend_Frame_Head1;
		UDP_Data.m_send_array[1] = kSend_Frame_Head2;
		UDP_Data.m_send_array[2] = ID;
		UDP_Data.m_send_array[3] = 0x04;
		UDP_Data.m_send_array[4] = kCmd_Handg3_Write;
		UDP_Data.m_send_array[5] = 0xEC;
		UDP_Data.m_send_array[6] = 0x03;
		UDP_Data.m_send_array[7] = 0x01;
		for (i = 2; i < 8; i++)
		{
			m_unChecksum += UDP_Data.m_send_array[i];
		}
		UDP_Data.m_send_array[8] = m_unChecksum & 0xFF;
		UDP_Data.m_tx_len = 9;
		SenderThread(0);
		return 0;
	}

	int right_hand::Action_SEQ_index(uint8_t ID, int index)
	{
		uint8_t i = 0;
		uint8_t m_unChecksum = 0;
		UDP_Data.m_send_array[0] = kSend_Frame_Head1;
		UDP_Data.m_send_array[1] = kSend_Frame_Head2;
		UDP_Data.m_send_array[2] = ID;
		UDP_Data.m_send_array[3] = 0x04;
		UDP_Data.m_send_array[4] = kCmd_Handg3_Write;
		UDP_Data.m_send_array[5] = 0x10;
		UDP_Data.m_send_array[6] = 0x09;
		UDP_Data.m_send_array[7] = index & 0xFF;
		for (i = 2; i < 8; i++)
		{
			m_unChecksum += UDP_Data.m_send_array[i];
		}
		UDP_Data.m_send_array[8] = m_unChecksum & 0xFF;
		UDP_Data.m_tx_len = 9;
		SenderThread(0);
		return 0;
	}

	int right_hand::Action_SEQ_run(uint8_t ID)
	{
		uint8_t i = 0;
		uint8_t m_unChecksum = 0;
		UDP_Data.m_send_array[0] = kSend_Frame_Head1;
		UDP_Data.m_send_array[1] = kSend_Frame_Head2;
		UDP_Data.m_send_array[2] = ID;
		UDP_Data.m_send_array[3] = 0x04;
		UDP_Data.m_send_array[4] = kCmd_Handg3_Write;
		UDP_Data.m_send_array[5] = 0x12;
		UDP_Data.m_send_array[6] = 0x09;
		UDP_Data.m_send_array[7] = 1;
		for (i = 2; i < 8; i++)
		{
			m_unChecksum += UDP_Data.m_send_array[i];
		}
		UDP_Data.m_send_array[8] = m_unChecksum & 0xFF;
		UDP_Data.m_tx_len = 9;
		SenderThread(0);
		return 0;
	}

	int right_hand::Current_Limit_Set(uint8_t ID, uint16_t val1, uint16_t val2, uint16_t val3, uint16_t val4, uint16_t val5, uint16_t val6)
	{
		uint8_t i = 0;
		uint8_t m_unChecksum = 0;
		if (val1 < 1 || val1 > 1500 || val2 < 1 || val2 > 1500 || val3 < 1 || val3 > 1500 ||
			val4 < 1 || val4 > 1500 || val5 < 1 || val5 > 1500 || val6 < 1 || val6 > 1500)
		{
			std::cout << "Out of range!" << endl;
			return -1;
		}
		UDP_Data.m_send_array[0] = kSend_Frame_Head1;
		UDP_Data.m_send_array[1] = kSend_Frame_Head2;
		UDP_Data.m_send_array[2] = ID;
		UDP_Data.m_send_array[3] = 0x0F;
		UDP_Data.m_send_array[4] = kCmd_Handg3_Write;
		UDP_Data.m_send_array[5] = 0xfc;
		UDP_Data.m_send_array[6] = 0x03;
		UDP_Data.m_send_array[7] = val1 & 0xFF;
		UDP_Data.m_send_array[8] = val1 >> 8;
		UDP_Data.m_send_array[9] = val2 & 0xFF;
		UDP_Data.m_send_array[10] = val2 >> 8;
		UDP_Data.m_send_array[11] = val3 & 0xFF;
		UDP_Data.m_send_array[12] = val3 >> 8;
		UDP_Data.m_send_array[13] = val4 & 0xFF;
		UDP_Data.m_send_array[14] = val4 >> 8;
		UDP_Data.m_send_array[15] = val5 & 0xFF;
		UDP_Data.m_send_array[16] = val5 >> 8;
		UDP_Data.m_send_array[17] = val6 & 0xFF;
		UDP_Data.m_send_array[18] = val6 >> 8;
		for (i = 2; i < 19; i++)
		{
			m_unChecksum += UDP_Data.m_send_array[i];
		}
		UDP_Data.m_send_array[19] = m_unChecksum & 0xFF;
		UDP_Data.m_tx_len = 20;
		SenderThread(0);
		return 0;
	}

	int right_hand::Angle_Get(uint8_t ID, double time_g)
	{
		uint8_t i = 0;
		uint8_t m_unChecksum = 0;
		UDP_Data.m_send_array[0] = kSend_Frame_Head1;
		UDP_Data.m_send_array[1] = kSend_Frame_Head2;
		UDP_Data.m_send_array[2] = ID;
		UDP_Data.m_send_array[3] = 0x04;
		UDP_Data.m_send_array[4] = kCmd_Handg3_Read;
		UDP_Data.m_send_array[5] = 0x0a;
		UDP_Data.m_send_array[6] = 0x06;
		UDP_Data.m_send_array[7] = 0x0c;
		for (i = 2; i < 8; i++)
		{
			m_unChecksum += UDP_Data.m_send_array[i];
		}
		UDP_Data.m_send_array[8] = m_unChecksum & 0xFF;
		UDP_Data.m_tx_len = 9;
		SenderThread(time_g);
		return 0;
	}

	int right_hand::Current_Get(uint8_t ID, double time_g)
	{
		uint8_t i = 0;
		uint8_t m_unChecksum = 0;
		UDP_Data.m_send_array[0] = kSend_Frame_Head1;
		UDP_Data.m_send_array[1] = kSend_Frame_Head2;
		UDP_Data.m_send_array[2] = ID;
		UDP_Data.m_send_array[3] = 0x04;
		UDP_Data.m_send_array[4] = kCmd_Handg3_Read;
		UDP_Data.m_send_array[5] = 0x3a;
		UDP_Data.m_send_array[6] = 0x06;
		UDP_Data.m_send_array[7] = 0x0c;
		for (i = 2; i < 8; i++)
		{
			m_unChecksum += UDP_Data.m_send_array[i];
		}
		UDP_Data.m_send_array[8] = m_unChecksum & 0xFF;
		UDP_Data.m_tx_len = 9;
		SenderThread(time_g);
		return 0;
	}

	int right_hand::Force_Get(uint8_t ID, double time_g)
	{
		uint8_t i = 0;
		uint8_t m_unChecksum = 0;
		UDP_Data.m_send_array[0] = kSend_Frame_Head1;
		UDP_Data.m_send_array[1] = kSend_Frame_Head2;
		UDP_Data.m_send_array[2] = ID;
		UDP_Data.m_send_array[3] = 0x04;
		UDP_Data.m_send_array[4] = kCmd_Handg3_Read;
		UDP_Data.m_send_array[5] = 0x2e;
		UDP_Data.m_send_array[6] = 0x06;
		UDP_Data.m_send_array[7] = 0x0c;
		for (i = 2; i < 8; i++)
		{
			m_unChecksum += UDP_Data.m_send_array[i];
		}
		UDP_Data.m_send_array[8] = m_unChecksum & 0xFF;
		UDP_Data.m_tx_len = 9;
		SenderThread(time_g);
		return 0;
	}

	int right_hand::Status_Get(uint8_t ID, double time_g)
	{
		uint8_t i = 0;
		uint8_t m_unChecksum = 0;
		UDP_Data.m_send_array[0] = kSend_Frame_Head1;
		UDP_Data.m_send_array[1] = kSend_Frame_Head2;
		UDP_Data.m_send_array[2] = ID;
		UDP_Data.m_send_array[3] = 0x04;
		UDP_Data.m_send_array[4] = kCmd_Handg3_Read;
		UDP_Data.m_send_array[5] = 0x4c;
		UDP_Data.m_send_array[6] = 0x06;
		UDP_Data.m_send_array[7] = 0x06;
		for (i = 2; i < 8; i++)
		{
			m_unChecksum += UDP_Data.m_send_array[i];
		}
		UDP_Data.m_send_array[8] = m_unChecksum & 0xFF;
		UDP_Data.m_tx_len = 9;
		SenderThread(time_g);
		return 0;
	}

	int right_hand::Error_Get(uint8_t ID, double time_g)
	{
		uint8_t i = 0;
		uint8_t m_unChecksum = 0;
		UDP_Data.m_send_array[0] = kSend_Frame_Head1;
		UDP_Data.m_send_array[1] = kSend_Frame_Head2;
		UDP_Data.m_send_array[2] = ID;
		UDP_Data.m_send_array[3] = 0x04;
		UDP_Data.m_send_array[4] = kCmd_Handg3_Read;
		UDP_Data.m_send_array[5] = 0x46;
		UDP_Data.m_send_array[6] = 0x06;
		UDP_Data.m_send_array[7] = 0x06;
		for (i = 2; i < 8; i++)
		{
			m_unChecksum += UDP_Data.m_send_array[i];
		}
		UDP_Data.m_send_array[8] = m_unChecksum & 0xFF;
		UDP_Data.m_tx_len = 9;
		SenderThread(time_g);
		return 0;
	}

	int right_hand::Action_do(int act_number)
	{
		Action_SEQ_index(1, act_number);
		Action_SEQ_run(1);
		return 0;
	}

	int right_hand::Hand_Get(uint8_t ID, double time_g)
	{
		uint8_t i = 0;
		uint8_t m_unChecksum = 0;
		UDP_Data.m_send_array[0] = kSend_Frame_Head1;
		UDP_Data.m_send_array[1] = kSend_Frame_Head2;
		UDP_Data.m_send_array[2] = ID;
		UDP_Data.m_send_array[3] = 0x04;
		UDP_Data.m_send_array[4] = kCmd_Handg3_Read;
		UDP_Data.m_send_array[5] = 0x0a;
		UDP_Data.m_send_array[6] = 0x06;
		UDP_Data.m_send_array[7] = 0x30;
		for (i = 2; i < 8; i++)
		{
			m_unChecksum += UDP_Data.m_send_array[i];
		}
		UDP_Data.m_send_array[8] = m_unChecksum & 0xFF;
		UDP_Data.m_tx_len = 9;
		SenderThread(time_g);
		return 0;
	}

	int right_hand::call_count_right = 0;

	int right_hand::sin_do()
	{
		for (int i = 0; i < 2000; i++)
		{
			Angle_Set(1, int(500 * (1 + sin(i * M_PI / 50 + 1 * M_PI / 2))),
					  int(500 * (1 + sin(i * M_PI / 50 + 2 * M_PI / 2))),
					  int(500 * (1 + sin(i * M_PI / 50 + 3 * M_PI / 2))),
					  int(500 * (1 + sin(i * M_PI / 50 + 5 * M_PI / 2))),
					  int(500 * (1 + sin(i * M_PI / 50 + 6 * M_PI / 2))),
					  int(500 * (1 + sin(i * M_PI / 50 + 7 * M_PI / 2))), 7);
		}
		return 0;
	}

	int right_hand::key_do(int key_number)
	{
		std::thread sin_thread;
		if (key_number == 0)
		{
			Angle_Set(1, 500, 500, 500, 500, 500, 500, 7);
			call_count_right++;
		}
		else if (key_number == 1)
		{
			Angle_Set(1, 0, 0, 0, 0, 1000, 1000, 7);
			call_count_right++;
		}
		else if (key_number == 2)
		{
			Angle_Set(1, 1000, 1000, 1000, 1000, 1000, 1000, 7);
			call_count_right++;
		}
		else if (key_number == 3)
		{
			Angle_Set(1, 800, 850, 900, 950, 800, 800, 7);
			call_count_right++;
		}
		else if (key_number == 4)
		{
			Action_do(2);
			call_count_right++;
		}
		else if (key_number == 5)
		{
			Speed_Set(1, 1000, 1000, 1000, 1000, 1000, 1000);
			sin_thread = std::thread(&right_hand::sin_do, this);
			sin_thread.detach();
			// call_count_right++;
		}
		else if (key_number == 6)
		{
			Action_do(13);
			call_count_right++;
		}
		else if (key_number == 56)
		{
			Angle_Set(1, 0, 0, 0, 1000, 0, 0, 7);
			std::this_thread::sleep_for(std::chrono::milliseconds(6000));
			Angle_Set(1, 1000, 1000, 1000, 1000, 1000, 1000, 7);
		}
		else if (key_number == 56)
		{
			std::cout << "right key number: " << key_number << std::endl;
			while (key_number--)
			{
				Angle_Set(1, key_number, key_number, key_number, key_number, key_number, 1000, 7);
				// std::this_thread::sleep_for(std::chrono::milliseconds(2));
				usleep(2000);
			}
		}
		else
		{
		}

		return 0;
	}

	void right_hand::ReceiverThread()
	{
		char response[1024];
		while (true)
		{
			int no = 1;
			ssize_t recvBytes = recvfrom(sockfd, response, sizeof(response), 0, nullptr, nullptr);
			std::cout << "Received response: ";
			for (ssize_t i = 0; i < recvBytes; ++i)
			{
				unsigned char uResponse = static_cast<unsigned char>(response[i]);
				uResponse = uResponse & 0xFFFFFF;
				std::cout << "0x" << std::hex << (int)uResponse << " ";
			}
			std::cout << std::endl;
			std::cout << std::endl;
			if (recvBytes == -1)
			{
				std::cerr << "Error: recvfrom failed." << std::endl;
				continue;
			}
			if ((int)response[2] == 1)
			{
				uint16_t combined = combineTo16Bit(response[6], response[5]);
				if (combined == 1546)
				{
					for (ssize_t i = 7; i < recvBytes - 2; i = i + 2)
					{
						uint16_t combined = combineTo16Bit(response[i + 1], response[i]);
						switch (no)
						{
						case 1:
							setJointAngle(0, combined);
							break;
						case 2:
							setJointAngle(1, combined);
							break;
						case 3:
							setJointAngle(2, combined);
							break;
						case 4:
							setJointAngle(3, combined);
							break;
						case 5:
							setJointAngle(4, combined);
							break;
						case 6:
							setJointAngle(5, combined);
							break;
						default:
							break;
						}
						no++;
					}
				}
				if (combined == 1582)
				{
					for (ssize_t i = 7; i < recvBytes - 2; i = i + 2)
					{
						uint16_t combined = combineTo16Bit(response[i + 1], response[i]);
						switch (no)
						{
						case 1:
							setJointForce(0, combined);
							break;
						case 2:
							setJointForce(1, combined);
							break;
						case 3:
							setJointForce(2, combined);
							break;
						case 4:
							setJointForce(3, combined);
							break;
						case 5:
							setJointForce(4, combined);
							break;
						case 6:
							setJointForce(5, combined);
							break;
						default:
							break;
						}
						no++;
					}
				}
				if (combined == 1594)
				{
					for (ssize_t i = 7; i < recvBytes - 2; i = i + 2)
					{
						uint16_t combined = combineTo16Bit(response[i + 1], response[i]);
						switch (no)
						{
						case 1:
							setJointCurrent(0, combined);
							break;
						case 2:
							setJointCurrent(1, combined);
							break;
						case 3:
							setJointCurrent(2, combined);
							break;
						case 4:
							setJointCurrent(3, combined);
							break;
						case 5:
							setJointCurrent(4, combined);
							break;
						case 6:
							setJointCurrent(5, combined);
							break;
						default:
							break;
						}
						no++;
					}
				}
				if (combined == 1606)
				{
					for (ssize_t i = 7; i < recvBytes - 1; i = i + 1)
					{
						uint8_t combined = response[i];
						combined = std::abs(combined);
						switch (no)
						{
						case 1:
							setJointErrorCode(0, combined);
							break;
						case 2:
							setJointErrorCode(1, combined);
							break;
						case 3:
							setJointErrorCode(2, combined);
							break;
						case 4:
							setJointErrorCode(3, combined);
							break;
						case 5:
							setJointErrorCode(4, combined);
							break;
						case 6:
							setJointErrorCode(5, combined);
							break;
						default:
							break;
						}
						no++;
					}
				}
				if (combined == 1612)
				{
					for (ssize_t i = 7; i < recvBytes - 1; i = i + 1)
					{
						uint8_t combined = response[i];
						combined = std::abs(combined);
						switch (no)
						{
						case 1:
							setJointStatus(0, combined);
							break;
						case 2:
							setJointStatus(1, combined);
							break;
						case 3:
							setJointStatus(2, combined);
							break;
						case 4:
							setJointStatus(3, combined);
							break;
						case 5:
							setJointStatus(4, combined);
							break;
						case 6:
							setJointStatus(5, combined);
							break;
						default:
							break;
						}
						no++;
					}
				}
				if (combined == 1004)
				{
					std::cout << "error cleared!" << endl;
				}
				if (combined == 1006)
				{
					std::cout << "Restored to factory settings!" << endl;
				}
				if (combined == 1009)
				{
					std::cout << "Force sensor calibrated!" << endl;
				}
				if (combined == 1020)
				{
					std::cout << "Current protection is set!" << endl;
				}
				if (combined == 1522)
				{
					std::cout << "Speed ​is set!" << endl;
				}
				if (combined == 1498)
				{
					std::cout << "Force control threshold has been set!" << endl;
				}
			}
		}
	}
	//};

	uint16_t Crc16(uint16_t f_u16PloyVal, uint16_t f_u16InitVal, uint16_t f_u16XorOut, const void *f_pvBuf, uint16_t f_u16Len)
	{
		uint8_t v_u8Idx0;

		switch (f_u16PloyVal)
		{
		case 0x8005:
			f_u16PloyVal = 0xa001;
			break;
		default:
			return f_u16InitVal ^ f_u16XorOut;
		}
		const uint8_t *buffer = static_cast<const uint8_t *>(f_pvBuf);
		while (f_u16Len--)
		{
			f_u16InitVal ^= *buffer;
			buffer++;

			for (v_u8Idx0 = 0; v_u8Idx0 < 8; ++v_u8Idx0)
			{
				if (f_u16InitVal & 0x0001)
				{
					f_u16InitVal >>= 1;
					f_u16InitVal ^= f_u16PloyVal;
				}
				else
				{
					f_u16InitVal >>= 1;
				}
			}
		}
		return f_u16InitVal ^ f_u16XorOut;
	}

	unsigned short combineTo16Bit(unsigned char highByte, unsigned char lowByte)
	{
		short result = (static_cast<unsigned short>(highByte) << 8) | lowByte;
		result = std::abs(result);
		return result;
	}

}
