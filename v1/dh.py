import socket
import time
import struct

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


default_dh_timeout = 0.2
default_dh_port_ctrl = 2333
default_dh_port_comm = 2334
default_dh_port_pt = 10000
default_dh_port_debug = 8888
default_dh_network = "192.168.137.255"

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

def get_angle(id):
    tx_messages = struct.pack('>BBBB', 0x03, 0x02, 0x01, id)
    s.sendto(tx_messages, (dh_network, dh_port_comm))
    try:
        data, address = s.recvfrom(1024)
        logger.print_trace("Received from {}:{}".format(address, data))
        if id == 0:
            angle1, angle2, angle3, angle4, angle5, angle6 = struct.unpack('>ffffff', data[0:4 + 4 + 4 + 4 + 4 + 4])
            # print(ip)
            return angle1, angle2, angle3, angle4, angle5, angle6
        else:
            angel = struct.unpack('>f', data[0:4])
            return angel

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

def get_current(id):
    tx_messages = struct.pack('>BBBB', 0x03, 0x03, 0x01, id)
    s.sendto(tx_messages, (dh_network, dh_port_comm))
    try:
        data, address = s.recvfrom(1024)
        logger.print_trace("Received from {}:{}".format(address, data))
        if id == 0:
            current1, current2, current3, current4, current5, current6 = struct.unpack('>ffffff', data[0:4 + 4 + 4 + 4 + 4 + 4])
            return current1, current2, current3, current4, current5, current6
        else:
            current = struct.unpack('>f', data[0:4])
            return current

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
    

def get_fdb():
    tx_messages = struct.pack('>BB', 0x01, 0x03)
    s.sendto(tx_messages, (dh_network, dh_port_comm))
    
    try:
        data, address = s.recvfrom(1024)
        # cnt1, angle1, angular_speed1, current1, status1, errorcode1, control_type, p1, i1, d1, angle_limited1, angular_speed_limited1, current_limited1 = struct.unpack('>lfffuuuffffff', data[0:32 + 4 + 4 + 4 + 1 + 1 + 1 + 4 + 4 + 4 + 4 + 4 + 4])
        # cnt2, angle2, angular_speed2, current2, status2, errorcode2, control_type, p2, i2, d2, angle_limited2, angular_speed_limited2, current_limited2 = struct.unpack('>lfffuuuffffff', data[0:32 + 4 + 4 + 4 + 1 + 1 + 1 + 4 + 4 + 4 + 4 + 4 + 4])
        # cnt3, angle3, angular_speed3, current3, status3, errorcode3, control_type, p3, i3, d3, angle_limited3, angular_speed_limited3, current_limited3 = struct.unpack('>lfffuuuffffff', data[0:32 + 4 + 4 + 4 + 1 + 1 + 1 + 4 + 4 + 4 + 4 + 4 + 4])
        # cnt4, angle4, angular_speed4, current4, status4, errorcode4, control_type, p4, i4, d4, angle_limited4, angular_speed_limited4, current_limited4 = struct.unpack('>lfffuuuffffff', data[0:32 + 4 + 4 + 4 + 1 + 1 + 1 + 4 + 4 + 4 + 4 + 4 + 4])
        # cnt5, angle5, angular_speed5, current5, status5, errorcode5, control_type, p5, i5, d5, angle_limited5, angular_speed_limited5, current_limited5 = struct.unpack('>lfffuuuffffff', data[0:32 + 4 + 4 + 4 + 1 + 1 + 1 + 4 + 4 + 4 + 4 + 4 + 4])
        # cnt6, angle6, angular_speed6, current6, status6, errorcode6, control_type, p6, i6, d6, angle_limited6, angular_speed_limited6, current_limited6 = struct.unpack('>lfffuuuffffff', data[0:32 + 4 + 4 + 4 + 1 + 1 + 1 + 4 + 4 + 4 + 4 + 4 + 4])
        angle_2 = struct.unpack('<f', data[0:4])
        logger.print_trace("{}".format(angle_2))  
    except socket.timeout:  # fail after 1 second of no activity
        logger.print_trace_error(dh_network + " : Didn't receive anymore data! [Timeout]")
    except:
        logger.print_trace_warning(dh_network + " fi_dh.get_root() except")

def loop_angle(target1, target2, target3, target4, target5, target6):
    tx_messages = struct.pack('>BBBBffffff', 0x01, 0x02, 0x00, 0x00, target1, target2, target3, target4, target5, target6)
    s.sendto(tx_messages, (dh_network, dh_port_comm))
    