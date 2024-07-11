"""
Copyright (C) [2024] [Fourier Intelligence Ltd.]
2024.7.4
Gedit by fourier intelligent
this code for HandAPI function.
"""

import struct
from HandSocket import *
import time

class API():
    def __init__(self, dh_network):
        self.socket = HandSocket()
        self.dh_network = dh_network 
        self.dh_port_ctrl = self.socket.dh_port_ctrl
        self.dh_port_comm = self.socket.dh_port_comm

    # calibration
    def calibration(self):
        tx_messages = struct.pack('>BB', 0x01, 0x01)
        try:
            self.socket.SendData(tx_messages, self.dh_network, self.dh_port_ctrl)
            return FunctionResult.SUCCESS

        except socket.timeout:  # fail after 1 second of no activity
            logger.print_trace_error(self.dh_network + " : Didn't receive anymore data! [Timeout]")
            return FunctionResult.TIMEOUT
        except:
            logger.print_trace_warning(self.dh_network + " fi_dh.get_root() except")
            return FunctionResult.FAIL

    # emergency stop mode
    def emergency(self):
        tx_messages = struct.pack('>BB', 0x01, 0x0b)
        self.socket.SendData(tx_messages, self.dh_network, self.dh_port_ctrl)

    # get encoder count params 
    def get_cnt(self):
        tx_messages = struct.pack('>B', 0x01)
        try:
            self.socket.SendData(tx_messages, self.dh_network, self.dh_port_comm)
            data, address = self.socket.ReceiveData()       
            float_arr = self.socket.string2int(data)  
            return float_arr      
        
        except socket.timeout:  # fail after 1 second of no activity
            logger.print_trace_error(self.dh_network + " : Didn't receive anymore data! [Timeout]")
            return []
        except:
            logger.print_trace_warning(self.dh_network + " fi_dh.get_root() except")
            return []


    # get hand motor position params 
    def get_pos(self):
        tx_messages = struct.pack('>B', 0x02)
        try:
            self.socket.SendData(tx_messages, self.dh_network, self.dh_port_comm)
            data, address = self.socket.ReceiveData()      
            data_list = self.socket.string2float(data)
            return data_list
        except socket.timeout:  # fail after 1 second of no activity
            logger.print_trace_error(self.dh_network + " : Didn't receive anymore data! [Timeout]")
        except:
            logger.print_trace_warning(self.dh_network + " fi_dh.get_root() except")


    # get hand motor current params 
    def get_current(self):
        tx_messages = struct.pack('>B', 0x04)
        try:
            self.socket.SendData(tx_messages, self.dh_network, self.dh_port_comm)
            data, address = self.socket.ReceiveData()      
            data_list = self.socket.string2float(data)
            return data_list
        except socket.timeout:  # fail after 1 second of no activity
            logger.print_trace_error(self.dh_network + " : Didn't receive anymore data! [Timeout]")
        except:
            logger.print_trace_warning(self.dh_network + " fi_dh.get_root() except")


    # get hand motor velocity params 
    def get_velocity(self):
        tx_messages = struct.pack('>B', 0x03)
        try:
            self.socket.SendData(tx_messages, self.dh_network, self.dh_port_comm)
            data, address = self.socket.ReceiveData()      
            data_list = self.socket.string2float(data)
            return data_list
        except socket.timeout:  # fail after 1 second of no activity
            logger.print_trace_error(self.dh_network + " : Didn't receive anymore data! [Timeout]")
        except:
            logger.print_trace_warning(self.dh_network + " fi_dh.get_root() except")


    # determine hand motor error, 0 means no error
    def get_errorcode(self):
        tx_messages = struct.pack('>B', 0x06)
        try:
            self.socket.SendData(tx_messages, self.dh_network, self.dh_port_comm)
            data, address = self.socket.ReceiveData()       
            float_arr = self.socket.string2int(data)  
            return float_arr      
        
        except socket.timeout:  # fail after 1 second of no activity
            logger.print_trace_error(self.dh_network + " : Didn't receive anymore data! [Timeout]")
        except:
            logger.print_trace_warning(self.dh_network + " fi_dh.get_root() except")


    # get hand motor status
    # status 0:before calibration/start, １:after calibration, 2:finish move , 3:move, 4:error
    def get_status(self):
        tx_messages = struct.pack('>B', 0x05)
        try:
            self.socket.SendData(tx_messages, self.dh_network, self.dh_port_comm)
            data, address = self.socket.ReceiveData()       
            float_arr = self.socket.string2int(data)
            return float_arr      
        
        except socket.timeout:  # fail after 1 second of no activity
            logger.print_trace_error(self.dh_network + " : Didn't receive anymore data! [Timeout]")
        except:
            logger.print_trace_warning(self.dh_network + " fi_dh.get_root() except")


    # get hand position limited bound, low is 0.0, high is 12.0
    def get_pos_limited(self):
        tx_messages = struct.pack('>B', 0x0b)
        try:
            self.socket.SendData(tx_messages, self.dh_network, self.dh_port_comm)
            data, address = self.socket.ReceiveData()      
            data_list = self.socket.string2float(data)
            return data_list
        except socket.timeout:  # fail after 1 second of no activity
            logger.print_trace_error(self.dh_network + " : Didn't receive anymore data! [Timeout]")
        except:
            logger.print_trace_warning(self.dh_network + " fi_dh.get_root() except")


    # get hand velocity limited bound, high bound is 10000.0
    def get_velocity_limited(self):
        tx_messages = struct.pack('>B', 0x0c)
        try:
            self.socket.SendData(tx_messages, self.dh_network, self.dh_port_comm)
            data, address = self.socket.ReceiveData()      
            data_list = self.socket.string2float(data)
            return data_list
        except socket.timeout:  # fail after 1 second of no activity
            logger.print_trace_error(self.dh_network + " : Didn't receive anymore data! [Timeout]")
        except:
            logger.print_trace_warning(self.dh_network + " fi_dh.get_root() except")


    # get hand current limited bound, high bound is 1000.0
    def get_current_limited(self):
        tx_messages = struct.pack('>B', 0x0d)
        try:
            self.socket.SendData(tx_messages, self.dh_network, self.dh_port_comm)
            data, address = self.socket.ReceiveData()      
            data_list = self.socket.string2float(data)
            return data_list
        except socket.timeout:  # fail after 1 second of no activity
            logger.print_trace_error(self.dh_network + " : Didn't receive anymore data! [Timeout]")
        except:
            logger.print_trace_warning(self.dh_network + " fi_dh.get_root() except")


    # get hand ip address
    def get_ip(self):
        tx_messages = struct.pack('>B', 0x0f)
        try:
            self.socket.SendData(tx_messages, self.dh_network, self.dh_port_comm)
            data, address = self.socket.ReceiveData()      
            # logger.print_trace("Received from {}:{}".format(address, data))
            return str(data[0:len(data)-1])

        except socket.timeout:  # fail after 1 second of no activity
            logger.print_trace_error(self.dh_network + " : Didn't receive anymore data! [Timeout]")
            return " "
        except:
            logger.print_trace_warning(self.dh_network + " fi_dh.get_root() except")
            return " "


    # get hand firmware version
    def get_firmware_version(self):
        tx_messages = struct.pack('>B', 0x0e)
        try:
            self.socket.SendData(tx_messages, self.dh_network, self.dh_port_comm)
            data, address = self.socket.ReceiveData()      
            logger.print_trace("Received from {}:{}".format(address, data))
            return str(data[0:len(data)-1])

        except socket.timeout:  # fail after 1 second of no activity
            logger.print_trace_error(self.dh_network + " : Didn't receive anymore data! [Timeout]")
            return " "
        except:
            logger.print_trace_warning(self.dh_network + " fi_dh.get_root() except")
            return " "


    # read position mode pid params 
    def get_pos_pid(self):
        tx_messages = struct.pack('>B', 0x08)
        try:
            self.socket.SendData(tx_messages, self.dh_network, self.dh_port_comm)
            data, address = self.socket.ReceiveData()      
            data_list = self.socket.string2float(data)
            return data_list
        except socket.timeout:  # fail after 1 second of no activity
            logger.print_trace_error(self.dh_network + " : Didn't receive anymore data! [Timeout]")
        except:
            logger.print_trace_warning(self.dh_network + " fi_dh.get_root() except")


    # read velocity mode pid params 
    def get_velocity_pid(self):
        tx_messages = struct.pack('>B', 0x09)
        try:
            self.socket.SendData(tx_messages, self.dh_network, self.dh_port_comm)
            data, address = self.socket.ReceiveData()      
            data_list = self.socket.string2float(data)
            return data_list
        except socket.timeout:  # fail after 1 second of no activity
            logger.print_trace_error(self.dh_network + " : Didn't receive anymore data! [Timeout]")
        except:
            logger.print_trace_warning(self.dh_network + " fi_dh.get_root() except")


    # read current mode pid params 
    def get_current_pid(self):
        tx_messages = struct.pack('>B', 0x0a)
        try:
            self.socket.SendData(tx_messages, self.dh_network, self.dh_port_comm)
            data, address = self.socket.ReceiveData()      
            data_list = self.socket.string2float(data)
            return data_list
        except socket.timeout:  # fail after 1 second of no activity
            logger.print_trace_error(self.dh_network + " : Didn't receive anymore data! [Timeout]")
        except:
            logger.print_trace_warning(self.dh_network + " fi_dh.get_root() except")


    # set velocity control config params 
    # input one finger id : [1: index, 2: middle, 3: ring, 4: little, 5: thumb-1, 6: thumb-2] and max_speed
    def set_velocity_limited(self, id, limit):
        tx_messages = struct.pack('>BBBBf', 0x00, 0x09, 0x00, id, float(limit))
        try:
            self.socket.SendData(tx_messages, self.dh_network, self.dh_port_ctrl)
            return FunctionResult.SUCCESS
        except:
            logger.print_trace_error(self.dh_network + " : Didn't receive anymore data! [Timeout]")
            return FunctionResult.TIMEOUT


    # set position control config params 
    # input one finger id : [1: index, 2: middle, 3: ring, 4: little, 5: thumb-1, 6: thumb-2], angle_low and angle_high
    def set_pos_limited(self, id, limit):
        tx_messages = struct.pack('>BBBBff', 0x01, 0x08, 0x00, id, float(limit[0]),  float(limit[1]))
        try:
            self.socket.SendData(tx_messages, self.dh_network, self.dh_port_ctrl)
            return FunctionResult.SUCCESS
        except:
            logger.print_trace_error(self.dh_network + " : Didn't receive anymore data! [Timeout]")
            return FunctionResult.TIMEOUT
        

    # set Current control config params 
    # input one finger id : [1: index, 2: middle, 3: ring, 4: little, 5: thumb-1, 6: thumb-2] and max_current
    def set_current_limited(self, id, limit):
        tx_messages = struct.pack('>BBBBf', 0x01, 0x0a, 0x00, id, float(limit))
        try:
            self.socket.SendData(tx_messages, self.dh_network, self.dh_port_ctrl)
            return FunctionResult.SUCCESS
        except:
            logger.print_trace_error(self.dh_network + " : Didn't receive anymore data! [Timeout]")
            return FunctionResult.TIMEOUT


    # set PID Position control config params 
    # input one finger id : [1: index, 2: middle, 3: ring, 4: little, 5: thumb-1, 6: thumb-2] and PID Params : [p, i, d]
    def set_pos_pid(self, id, pid):
        tx_messages = struct.pack('>BBBBfff', 0x01, 0x05, 0x00, id, float(pid[0]), float(pid[1]), float(pid[2]))
        try:
            self.socket.SendData(tx_messages, self.dh_network, self.dh_port_ctrl)
            return FunctionResult.SUCCESS
        except:
            logger.print_trace_error(self.dh_network + " : Didn't receive anymore data! [Timeout]")
            return FunctionResult.TIMEOUT
        

    # set PID Velocity control config params
    # input one finger id : [1: index, 2: middle, 3: ring, 4: little, 5: thumb-1, 6: thumb-2] and PID Params : [p, i, d]
    def set_velocity_pid(self, id, pid):
        tx_messages = struct.pack('>BBBBfff', 0x01, 0x06, 0x00, id, float(pid[0]), float(pid[1]), float(pid[2]))
        try:
            self.socket.SendData(tx_messages, self.dh_network, self.dh_port_ctrl)
            return FunctionResult.SUCCESS
        except:
            logger.print_trace_error(self.dh_network + " : Didn't receive anymore data! [Timeout]")
            return FunctionResult.TIMEOUT
        

    # set PID Current control config params 
    # input one finger id : [1: index, 2: middle, 3: ring, 4: little, 5: thumb-1, 6: thumb-2] and PID Params : [p, i, d]
    def set_current_pid(self, id, pid):
        tx_messages = struct.pack('>BBBBfff', 0x01, 0x07, 0x00, id, float(pid[0]), float(pid[1]), float(pid[2]))
        try:
            self.socket.SendData(tx_messages, self.dh_network, self.dh_port_ctrl)
            return FunctionResult.SUCCESS
        except:
            logger.print_trace_error(self.dh_network + " : Didn't receive anymore data! [Timeout]")
            return FunctionResult.TIMEOUT
        

    # set Position move for one finger
    def set_pos(self, id, target):
        tx_messages = struct.pack('>BBBBf', 0x01, 0x02, 0x00, int(id), float(target))
        try:
            self.socket.SendData(tx_messages, self.dh_network, self.dh_port_ctrl)
            return FunctionResult.SUCCESS
        except:
            logger.print_trace_error(self.dh_network + " : Didn't receive anymore data! [Timeout]")
            return FunctionResult.TIMEOUT


    # set Position move for all fingers 
    def set_pos_all(self, target):
        tx_messages = struct.pack('>BBBBffffff', 0x01, 0x11, 0x00, 0x00, float(target[0]), float(target[1]), float(target[2]), float(target[3]), float(target[4]), float(target[5]))
        try:
            self.socket.SendData(tx_messages, self.dh_network, self.dh_port_ctrl)
            return FunctionResult.SUCCESS
        except:
            logger.print_trace_error(self.dh_network + " : Didn't receive anymore data! [Timeout]")
            return FunctionResult.TIMEOUT


    # set Current move for one finger 
    def set_current(self, id, target):
        tx_messages = struct.pack('>BBBBf', 0x01, 0x04, 0x00, int(id), float(target))
        try:
            self.socket.SendData(tx_messages, self.dh_network, self.dh_port_ctrl)
            return FunctionResult.SUCCESS
        except:
            logger.print_trace_error(self.dh_network + " : Didn't receive anymore data! [Timeout]")
            return FunctionResult.TIMEOUT
        

    ####  set PWM move for all fingers 
    #### _back1{-200, -200, -200, -200, -200, -200}, _forward{200, 200, 200, 200, 200, 200}, _stop{0, 0, 0, 0, 0, 0};
    def set_pwm(self, target):
        tx_messages = struct.pack('>BBBBffffff', 0x01, 0x14, 0x00, 0x00, float(target[0]), float(target[1]), float(target[2]), 
                                float(target[3]), float(target[4]), float(target[5]))
        try:
            self.socket.SendData(tx_messages, self.dh_network, self.dh_port_ctrl)
            return FunctionResult.SUCCESS
        except:
            logger.print_trace_error(self.dh_network + " : Didn't receive anymore data! [Timeout]")
            return FunctionResult.TIMEOUT

    # set PD control move for one finger 
    # input one finger id : [1: index, 2: middle, 3: ring, 4: little, 5: thumb-1, 6: thumb-2], position : position and omega : w 
    def set_pd_control(self, id, target, w):
        tx_messages = struct.pack('>BBBBff', 0x01, 0x21, 0x00, int(id), float(target), int(w))
        try:
            self.socket.SendData(tx_messages, self.dh_network, self.dh_port_ctrl)
            return FunctionResult.SUCCESS
        except:
            logger.print_trace_error(self.dh_network + " : Didn't receive anymore data! [Timeout]")
            return FunctionResult.TIMEOUT
       