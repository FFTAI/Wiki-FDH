import socket
import time
import struct
# import numpy as np

from dh_logger import logger


class DHFunctionResult:
    SUCCESS = 0
    FAIL = -1
    RUNNING = 1
    PREPARE = 2
    EXECUTE = 3
    NOT_EXECUTE = 4
    TIMEOUT = 5


class DHFlagState:
    CLEAR = 0
    SET = 1


default_dh_timeout = 0.01
default_dh_port_ctrl = 2333
default_dh_port_comm = 2334
default_dh_port_pt = 10000
default_dh_port_debug = 8888
default_dh_network = "192.168.137.19"
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

def string2float(val):
    ret_list = []
    str_data = str(val)
    str_data = str_data[2:]
    while True:
        index = str_data.find('*')
        if index != -1:
            ele = float(str_data[:index])
            ret_list.append(float(ele))
            str_data = str_data[index+1:]
        else:
            return ret_list
        
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

# 
def calibration():
    tx_messages = struct.pack('>BB', 0x01, 0x01)
    s.sendto(tx_messages, (dh_network, dh_port_ctrl))

def calibration_test():
    tx_messages = struct.pack('>BB', 0x01, 0x01)
    s.sendto(tx_messages, ("192.168.137.19", dh_port_ctrl))
    time.sleep(0.01)
    s.sendto(tx_messages, ("192.168.137.39", dh_port_ctrl))
    time.sleep(0.01)


def set_target_angle_test(id, target):
    tx_messages = struct.pack('>BBBBf', 0x01, 0x02, 0x00, int(id), float(target))
    s.sendto(tx_messages, ("192.168.137.19", dh_port_ctrl))
    try:
        data, address = s.recvfrom(recvfromsize)
        logger.print_trace("Received from {}:{}".format(address, data.decode("utf-8")))

    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")
  


def emergency():
    tx_messages = struct.pack('>BB', 0x01, 0x0b)
    s.sendto(tx_messages, (dh_network, dh_port_ctrl))

# 
def set_target_angle(id, target):
    tx_messages = struct.pack('>BBBBf', 0x01, 0x02, 0x00, int(id), float(target))
    s.sendto(tx_messages, (dh_network, dh_port_ctrl))


def set_target_position_all(target):
    tx_messages = struct.pack('>BBBBffffff', 0x01, 0x11, 0x00, 0x00, float(target[0]), float(target[1]), float(target[2]), float(target[3]), float(target[4]), float(target[5]))
    s.sendto(tx_messages, (dh_network, dh_port_ctrl))
    

def set_target_omega(id, target):
    tx_messages = struct.pack('>BBBBf', 0x01, 0x03, 0x00, id, float(target))
    s.sendto(tx_messages, (dh_network, dh_port_ctrl))

# 
def set_target_current(id, target):
    if int(id) == 5 or int(id) == 6:
        target = -float(target)
    tx_messages = struct.pack('>BBBBf', 0x01, 0x04, 0x00, int(id), float(target))
    s.sendto(tx_messages, (dh_network, dh_port_ctrl))

# 
def set_pid_angle(id, pid):
    tx_messages = struct.pack('>BBBBfff', 0x01, 0x05, 0x00, id, float(pid[0]), float(pid[1]), float(pid[2]))
    s.sendto(tx_messages, (dh_network, dh_port_ctrl))


def set_pid_omega(id, pid):
    tx_messages = struct.pack('>BBBBfff', 0x01, 0x06, 0x00, id, float(pid[0]), float(pid[1]), float(pid[2]))
    s.sendto(tx_messages, (dh_network, dh_port_ctrl))


def set_pid_current(id, pid):
    tx_messages = struct.pack('>BBBBfff', 0x01, 0x07, 0x00, id, float(pid[0]), float(pid[1]), float(pid[2]))
    s.sendto(tx_messages, (dh_network, dh_port_ctrl))

# 
def set_limit_angle(id, limit):
    tx_messages = struct.pack('>BBBBf', 0x01, 0x08, 0x00, id, float(limit))
    s.sendto(tx_messages, (dh_network, dh_port_ctrl))

# 
def set_limit_omega(id, limit):
    tx_messages = struct.pack('>BBBBf', 0x01, 0x09, 0x00, id, float(limit))
    s.sendto(tx_messages, (dh_network, dh_port_ctrl))

# 
def set_limit_current(id, limit):
    tx_messages = struct.pack('>BBBBf', 0x01, 0x0a, 0x00, id, float(limit))
    s.sendto(tx_messages, (dh_network, dh_port_ctrl))
    
# 
def get_cnt():
    tx_messages = struct.pack('>B', 0x01)
    s.sendto(tx_messages, (dh_network, dh_port_comm))
    try:
        data, address = s.recvfrom(recvfromsize)
        # logger.print_trace("Received from {}:{}".format(address, data.decode("utf-8")))

        float_arr = string2int(data)  
        return float_arr         
        
    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")

# 
def get_angle():
    tx_messages = struct.pack('>B', 0x02)
    s.sendto(tx_messages, (dh_network, 2334))
    try:
        data, address = s.recvfrom(recvfromsize)
        logger.print_trace("Received from {}:{}".format(address, data.decode("utf-8")))
        # data_list = string2float(data)
        # data_list[4] = -data_list[4]
        # data_list[5] = -data_list[5]
        # return data_list

    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")

# 
def get_anglular_speed():
    tx_messages = struct.pack('>B', 0x03)
    s.sendto(tx_messages, (dh_network, dh_port_comm))
    try:
        data, address = s.recvfrom(recvfromsize)
        logger.print_trace("Received from {}:{}".format(address, data))
        data_list = string2float(data)
        return data_list

    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")

# 
def get_current():
    tx_messages = struct.pack('>B', 0x04)
    s.sendto(tx_messages, (dh_network, dh_port_comm))
    try:
        data, address = s.recvfrom(recvfromsize)
        logger.print_trace("Received from {}:{}".format(address, data))
        data_list = string2float(data)
        return data_list

    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")

# 
def get_status():
    tx_messages = struct.pack('>B', 0x05)
    s.sendto(tx_messages, (dh_network, dh_port_comm))
    try:
        data, address = s.recvfrom(1024)
        logger.print_trace("Received from {}:{}".format(address, data.decode("utf-8")))
        data_list = string2int(data)
        return data_list

    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")

# 
def get_errorcode():
    tx_messages = struct.pack('>B', 0x06)
    s.sendto(tx_messages, (dh_network, dh_port_comm))
    try:
        data, address = s.recvfrom(recvfromsize)
        logger.print_trace("Received from {}:{}".format(address, data))
        data_list = string2int(data)
        return data_list

    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")

# 
def get_controltype():
    tx_messages = struct.pack('>B', 0x07)
    s.sendto(tx_messages, (dh_network, dh_port_comm))
    try:
        data, address = s.recvfrom(recvfromsize)
        logger.print_trace("Received from {}:{}".format(address, data))
        data_list = string2int(data)
        return data_list

    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")

# 
def get_p():
    tx_messages = struct.pack('>B', 0x08)
    s.sendto(tx_messages, (dh_network, dh_port_comm))
    try:
        data, address = s.recvfrom(recvfromsize)
        logger.print_trace("Received from {}:{}".format(address, data))
        data_list = string2float(data)
        return data_list

    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")

# 
def get_i():
    tx_messages = struct.pack('>B', 0x09)
    s.sendto(tx_messages, (dh_network, dh_port_comm))
    try:
        data, address = s.recvfrom(recvfromsize)
        logger.print_trace("Received from {}:{}".format(address, data))
        data_list = string2float(data)
        return data_list

    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")

# 
def get_d():
    tx_messages = struct.pack('>B', 0x0a)
    s.sendto(tx_messages, (dh_network, dh_port_comm))
    try:
        data, address = s.recvfrom(recvfromsize)
        logger.print_trace("Received from {}:{}".format(address, data))
        data_list = string2float(data)
        return data_list

    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")

# 
def get_angle_limited():

    tx_messages = struct.pack('>B', 0x0b)
    s.sendto(tx_messages, (dh_network, dh_port_comm))
    try:
        data, address = s.recvfrom(recvfromsize)
        logger.print_trace("Received from {}:{}".format(address, data.decode("utf-8")))

        float_arr = string2float(data)  
        float_arr[4] = float_arr[4]          
        float_arr[5] = float_arr[5] 
        return float_arr         
        
    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")

# 
def get_omega_limited():

    tx_messages = struct.pack('>B', 0x0c)
    s.sendto(tx_messages, (dh_network, dh_port_comm))
    try:
        data, address = s.recvfrom(recvfromsize)
        logger.print_trace("Received from {}:{}".format(address, data.decode("utf-8")))

        float_arr = string2float(data)  
        return float_arr         
        
    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")

# 
def get_current_limited():

    tx_messages = struct.pack('>B', 0x0d)
    s.sendto(tx_messages, (dh_network, dh_port_comm))
    try:
        data, address = s.recvfrom(recvfromsize)
        logger.print_trace("Received from {}:{}".format(address, data.decode("utf-8")))

        float_arr = string2float(data)  
        return float_arr         
        
    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")

# 
def get_version():
    tx_messages = struct.pack('>B', 0x0e)
    s.sendto(tx_messages, (dh_network, dh_port_comm))
    try:
        data, address = s.recvfrom(recvfromsize)
        logger.print_trace("Received from {}:{}".format(address, data))
        return str(data[0:len(data)-1])

    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")

# 
def get_ip():
    tx_messages = struct.pack('>B', 0x0f)
    s.sendto(tx_messages, (dh_network, dh_port_comm))
    try:
        data, address = s.recvfrom(recvfromsize)
        logger.print_trace("Received from {}:{}".format(address, data))
        return str(data[0:len(data)-1])

    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
        return " "
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")
        return " "


def loop_angle(target1, target2, target3, target4, target5, target6, cur_angle):
    tar1 = target1[0]
    flg = 0
    
    # if (target4[0] != cur_angle[3]) and (cur_angle[0] > -100) and (float(target4[0] > 500 or cur_angle[3] > 500)):
    #     target1[0] = -500
    #     flg = 1


    # if ((target3[0] > 800) or (float(cur_angle[2]) > 800) or (target5[0] > 650) or (float(cur_angle[4]) > 650)) and (float(target1[0]) > 700):
    #     target1[0] = -500
    #     flg = 1

    if (float(target4[0]) > 500) or (float(cur_angle[3] > 500)):
        if ((float(target1[0]) > -500) or (float(cur_angle[0] > -500))):
            target1[0] = -500
            flg = 1  

    if flg:
        tx_messages = struct.pack('>BBBBffffffffffffffffffffffff', 0x01, 0x02, 0x00, 0x00, target1[0], target1[1], target1[2], target1[3], target2[0], target2[1], target2[2], target2[3], target3[0], target3[1], target3[2], target3[3], target4[0], target4[1], target4[2], target4[3], target5[0], target5[1], target5[2], target5[3], target6[0], target6[1], target6[2], target6[3])
        s.sendto(tx_messages, (dh_network, dh_port_comm))
        time.sleep(0.8)
        target1[0] = tar1
    
    tx_messages = struct.pack('>BBBBffffffffffffffffffffffff', 0x01, 0x02, 0x00, 0x00, target1[0], target1[1], target1[2], target1[3], target2[0], target2[1], target2[2], target2[3], target3[0], target3[1], target3[2], target3[3], target4[0], target4[1], target4[2], target4[3], target5[0], target5[1], target5[2], target5[3], target6[0], target6[1], target6[2], target6[3])
    s.sendto(tx_messages, (dh_network, dh_port_comm))


