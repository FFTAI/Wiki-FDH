"""
Copyright (C) [2024] [Fourier Intelligence Ltd.]
2024.7.4
Gedit by fourier intelligent
this code for config of HandSocket, include config parameters, send and receive commands.

"""

import socket
import time
import struct
import json
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

default_dh_timeout = 0.01
default_dh_port_ctrl = 2333
default_dh_port_comm = 2334
default_dh_port_pt = 10000
default_dh_port_debug = 8888
default_dh_network = "192.168.137.39" # righthand
recvfromsize = 1024

dh_timeout = 0
dh_port_ctrl = 0
dh_port_comm = 0
dh_port_pt = 0
dh_port_debug = 0
dh_network = ""
dh_debug = True

dh_timeout = default_dh_timeout
dh_port_ctrl = default_dh_port_ctrl
dh_port_comm = default_dh_port_comm
dh_port_pt = default_dh_port_pt
dh_port_debug = default_dh_port_debug
dh_network = default_dh_network

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.settimeout(dh_timeout)
s.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

logger.print_trace("DH start listening for broadcast...")


# get sensor params function 
def SendData(send_data, dh_network, dh_port):
    ret = s.sendto(send_data, (dh_network, dh_port))
    # print(ret)
    if ret < 0:
        return SocketResult.SOCKET_SEND_FAILED
    if ret != len(send_data):
        return SocketResult.SOCKET_SEND_SIZE_WRONG
    return FunctionResult.SUCCESS

# set config params function.
def ReceiveData():
    data, address = s.recvfrom(recvfromsize)
    if data:
        # logger.print_trace("Received from {}:{}".format(address, data.decode("utf-8")))
        return data, address
    else:
        return None




# string to int/float function
def string2int(val):
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

def string2float(val):
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