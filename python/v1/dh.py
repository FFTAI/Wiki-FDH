import socket
import time
import struct
import numpy as np

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


default_dh_timeout = 10.0
default_dh_port_ctrl = 2333
default_dh_port_comm = 2334
default_dh_port_pt = 10000
default_dh_port_debug = 8888
default_dh_network = "192.168.137.19"

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

# config 2333 port , recvfrom active report message
# recv_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
# recv_socket.settimeout(dh_timeout)
# server_address = ('192.168.137.1', 8888)  
# recv_socket.bind(server_address)  
recv_socket_buff = []

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
        

def get_angle_limited():

    tx_messages = struct.pack('>B', 0x11)
    s.sendto(tx_messages, (dh_network, dh_port_ctrl))
    try:
        data, address = s.recvfrom(1024)
        float_arr = string2float(data)  
        float_arr[4] = -float_arr[4]          
        float_arr[5] = -float_arr[5] 
        return float_arr         
        
    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")


def get_angular_range():

    tx_messages = struct.pack('>BB', 0x01, 0x04)
    s.sendto(tx_messages, (dh_network, dh_port_comm))
    try:
        data, address = s.recvfrom(2048)
        float_arr = string2float(data)  
        float_arr[4] = -float_arr[4]          
        float_arr[5] = -float_arr[5] 
        return float_arr         
        
    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")
        

def lookup():
    lookup_msg = "Is DH?"
    s.sendto(bytes(lookup_msg, 'utf-8'), (dh_network, dh_port_comm))
    try:
        data, address = s.recvfrom(1024)
        logger.print_trace("Received from {}:{}".format(address, data.decode("utf-8")))

    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")

def debug_motor_stop(isALl):
    if isALl:
        tx_messages = struct.pack('>BBBB', 0x03, 0x01, 0x01, isALl)
    else:
        tx_messages = struct.pack('>BBBB', 0x03, 0x01, 0x01, 0x00)
    
    s.sendto(tx_messages, (dh_network, dh_port_comm))
    try:
        data, address = s.recvfrom(1024)
        logger.print_trace("Received from {}:{}".format(address, data.decode("utf-8")))

    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")

def debug_motor_set_pwm(id, pwmval):
    if pwmval >= 0:
        if id == 0:
            tx_messages = struct.pack('>BBBBBi', 0x03, 0x01, 0x02, 0x00, 0x00, pwmval)
        else:
            tx_messages = struct.pack('>BBBBBi', 0x03, 0x01, 0x02, id, 0x00, pwmval)
    else:
        if id == 0:
            tx_messages = struct.pack('>BBBBBi', 0x03, 0x01, 0x02, 0x00, 0x01, abs(pwmval))
        else:
            tx_messages = struct.pack('>BBBBBi', 0x03, 0x01, 0x02, id, 0x01, abs(pwmval))
    
    
    s.sendto(tx_messages, (dh_network, dh_port_comm))
    try:
        data, address = s.recvfrom(1024)
        logger.print_trace("Received from {}:{}".format(address, data.decode("utf-8")))

    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")

def get_angle():
    tx_messages = struct.pack('>B', 0x02)
    s.sendto(tx_messages, (dh_network, dh_port_ctrl))
    try:
        data, address = s.recvfrom(1024)
        logger.print_trace("Received from {}:{}".format(address, data.decode("utf-8")))
        data_list = string2float(data)
        data_list[4] = -data_list[4]
        data_list[5] = -data_list[5]
        return data_list

    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")

def get_angulat_speed():
    tx_messages = struct.pack('>B', 0x03)
    s.sendto(tx_messages, (dh_network, dh_port_ctrl))
    try:
        data, address = s.recvfrom(1024)
        logger.print_trace("Received from {}:{}".format(address, data.decode("utf-8")))
        data_list = string2float(data)
        # data_list[4] = -data_list[4]
        # data_list[5] = -data_list[5]
        return data_list

    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")


def get_status():
    tx_messages = struct.pack('>B', 0x05)
    s.sendto(tx_messages, (dh_network, dh_port_ctrl))
    try:
        data, address = s.recvfrom(1024)
        logger.print_trace("Received from {}:{}".format(address, data.decode("utf-8")))
        data_list = string2float(data)
        # data_list[4] = -data_list[4]
        # data_list[5] = -data_list[5]
        return data_list

    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")


def get_anglular_speed(id):
    tx_messages = struct.pack('>BBBB', 0x03, 0x02, 0x02, id)
    s.sendto(tx_messages, (dh_network, dh_port_comm))
    try:
        data, address = s.recvfrom(1024)
        logger.print_trace("Received from {}:{}".format(address, data))
        if id == 0:
            angular_speed1, angular_speed2, angular_speed3, angular_speed4, angular_speed5, angular_speed6 = struct.unpack('>ffffff', data[0:4 + 4 + 4 + 4 + 4 + 4])
            return angular_speed1, angular_speed2, angular_speed3, angular_speed4, angular_speed5, angular_speed6
        else:
            angular_speed = struct.unpack('>f', data[0:4])
            return angular_speed

    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")

def get_current():
    tx_messages = struct.pack('>B', 0x04)
    s.sendto(tx_messages, (dh_network, dh_port_ctrl))
    try:
        data, address = s.recvfrom(1024)
        logger.print_trace("Received from {}:{}".format(address, data))
        data_list = string2float(data)
        return data_list

    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")


def get_errorcode():
    tx_messages = struct.pack('>B', 0x06)
    s.sendto(tx_messages, (dh_network, dh_port_ctrl))
    try:
        data, address = s.recvfrom(1024)
        logger.print_trace("Received from {}:{}".format(address, data))
        data_list = string2float(data)
        return data_list

    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")


def get_version():
    tx_messages = struct.pack('>B', 0x14)
    s.sendto(tx_messages, (dh_network, dh_port_ctrl))
    try:
        data, address = s.recvfrom(1024)
        logger.print_trace("Received from {}:{}".format(address, data))
        return str(data)

    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")


def get_ip():
    tx_messages = struct.pack('>B', 0x15)
    s.sendto(tx_messages, (dh_network, dh_port_ctrl))
    try:
        data, address = s.recvfrom(1024)
        logger.print_trace("Received from {}:{}".format(address, data))
        return str(data)

    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")


def get_pid():
    msg = 0x08
    ret_pid = []
    while True:
        tx_messages = struct.pack('>B', msg)
        s.sendto(tx_messages, (dh_network, dh_port_ctrl))
        try:
            data, address = s.recvfrom(1024)
            logger.print_trace("Received from {}:{}".format(address, data))
            data_list = string2float(data)
            ret_pid.append(data_list)
            if msg == 0x10:
                return ret_pid
            msg = msg + 1

        except socket.timeout:  # fail after 1 second of no activity
            logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
        except:
            logger.print_trace_warning(dh_network + " fi_dh.get_root() except")


def comm_get_cnt(isALl):

    tx_messages = struct.pack('>BBBB', 0x03, 0x04, 0x00, isALl)
    s.sendto(tx_messages, (dh_network, dh_port_comm))
    try:
        data, address = s.recvfrom(1024)
        cnt = struct.unpack('>L', data[0:32])
        logger.print_trace("Received from {}:{}".format(address, cnt))
        
    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")
        

def calibration():
    tx_messages = struct.pack('>BB', 0x01, 0x01)
    s.sendto(tx_messages, (dh_network, dh_port_comm))
    try:
        data, address = s.recvfrom(1024)
        logger.print_trace("Received from {}:{}".format(address, data.decode('utf-8')))
        
    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")


def get_fdb():
    tx_messages = struct.pack('>BB', 0x01, 0x03)
    s.sendto(tx_messages, (dh_network, dh_port_comm))
    
    try:
        data, address = s.recvfrom(2048)
        data_list = string2float(data)
        arr = np.array(data_list)
        split_arr = np.reshape(arr, (6, 4))
        split_list = split_arr.tolist()
        split_list[4][0] = -split_list[4][0]
        split_list[5][0] = -split_list[5][0]
        return split_list
    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")


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


def pid_param(target1, target2, target3, target4, target5, target6):

    tx_messages = struct.pack('>BBBBffffffffffffffffffffffff', 0x01, 0x02, 0x00, 0x00, target1[0], target1[1], target1[2], target1[3], target2[0], target2[1], target2[2], target2[3], target3[0], target3[1], target3[2], target3[3], target4[0], target4[1], target4[2], target4[3], target5[0], target5[1], target5[2], target5[3], target6[0], target6[1], target6[2], target6[3])
    s.sendto(tx_messages, (dh_network, dh_port_comm))
    


def test_report():
    s.sendto(bytes("test", 'utf-8'), (dh_network, dh_port_comm))
    try:
        data, address = s.recvfrom(2048)

        logger.print_trace("Received from {}:{}".format(address, data.decode('utf-8')))
        strdata = str(data)
        print(strdata)
        # index = strdata.find('a')
        # print(float(data[0:index-2]))
        # substr = strdata[index+1: ]
        # print(substr)
        # index = substr.find('a')
        # print(index)
        # if index == -1:
        #     print(substr[index+1:len(substr)])
        #     print(int(substr[index+1:len(substr)-1]))
        # for i in range(0, len(data)):
        #     if str(data[i]) == 'a':
        #         print(int(str(data[0:i-1])))
        #         break
        #     print(str(data[i]))
        
    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")




def recvfrom_hand():
    try:
        data, address = recv_socket.recvfrom(2048)
        data_list = string2float(data)
        arr = np.array(data_list)
        split_arr = np.reshape(arr, (6, 4))
        recv_socket_buff = split_arr.tolist()
        recv_socket_buff[4][0] = -recv_socket_buff[4][0]
        recv_socket_buff[5][0] = -recv_socket_buff[5][0]
        logger.print_trace("{}".format(address))
        return recv_socket_buff
    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")