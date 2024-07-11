"""
Copyright (C) [2024] [Fourier Intelligence Ltd.]
2024.7.4
Gedit by fourier intelligent
this code for config of HandSocket, include config parameters, send and receive commands.

"""

import socket
import sys, os
sys.path.append(os.path.dirname(__file__))
from dh_logger import logger


# control and feedback socket config and time count config.
class FunctionResult:
    SUCCESS = 0
    FAIL = -1
    RUNNING = 1
    PREPARE = 2
    EXECUTE = 3
    NOT_EXECUTE = 4
    TIMEOUT = 5

class SocketResult:
    SOCKET_SEND_FAILED = -10001,
    SOCKET_SEND_SIZE_WRONG = -10002,
    SOCKET_RECEIVE_FAILED = -10003,
    SOCKET_RECEIVE_SIZE_WRONG = -10004,

class DefaltParam:
    default_dh_timeout = 1 #0.01
    default_dh_port_ctrl = 2333
    default_dh_port_comm = 2334
    default_dh_port_pt = 10000
    default_dh_port_debug = 8888
    default_dh_network = "192.168.137.39" # righthand
    recvfromsize = 1024

class HandSocket():
    def __init__(self):
        self.dh_timeout = DefaltParam.default_dh_timeout
        self.dh_port_ctrl = DefaltParam.default_dh_port_ctrl
        self.dh_port_comm = DefaltParam.default_dh_port_comm
        self.dh_port_pt = DefaltParam.default_dh_port_pt
        self.dh_port_debug = DefaltParam.default_dh_port_debug
        self.dh_network = DefaltParam.default_dh_network

        self.s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.s.settimeout(self.dh_timeout)
        self.s.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        logger.print_trace("DH start listening for broadcast...")


    # get sensor params function 
    def SendData(self, send_data, dh_network, dh_port):
        ret = self.s.sendto(send_data, (dh_network, dh_port))
        # print(ret)
        if ret < 0:
            return SocketResult.SOCKET_SEND_FAILED
        if ret != len(send_data):
            return SocketResult.SOCKET_SEND_SIZE_WRONG
        return FunctionResult.SUCCESS

    # set config params function.
    def ReceiveData(self):
        data, address = self.s.recvfrom(DefaltParam.recvfromsize)
        if data:
            # logger.print_trace("Received from {}:{}".format(address, data.decode("utf-8")))
            return data, address
        else:
            return None


    # string to int/float function
    def string2int(self, val):
        ret_list = []
        str_data = str(val)
        str_data = str_data[2:]
        while True:
            index = str_data.find(' ')
            if index != -1:
                ele = int(str_data[:index])
                ret_list.append(int(ele))
                str_data = str_data[index+1:]
            else:
                return ret_list

    def string2float(self, val):
        ret_list = []
        str_data = str(val)
        str_data = str_data[2:]
        while True:
            index = str_data.find(' ')
            if index != -1:
                ele = float(str_data[:index])
                ret_list.append(float(ele))
                str_data = str_data[index+1:]
            else:
                return ret_list