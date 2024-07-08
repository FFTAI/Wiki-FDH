import HandSocket
from Handapi import API
import time, struct, math

def calibration_test(api):
    tx_messages = struct.pack('>BB', 0x01, 0x01)
    print("calibration start")
    val = -10000
    api.calibration()
    time.sleep(1)

    for i in range(1, 7):
        api.set_pos(i, val)
    

    api.calibration()
    time.sleep(1)
    api.set_pwm([-200,-200,-200,-200,-200,-200])
    print("calibration finished")
    HandSocket.SendData(tx_messages, api.dh_network, api.dh_port_ctrl)

def sin_move(api):
    for i in range(1500):
        for j in range(1, 7):
            tar = 4 * (1 + math.sin(i * math.pi / 50 + j * math.pi / 2))
            if i > 1200:
                tar = 0
            api.set_pd_control(j, tar, 7.00)
        time.sleep(0.01)  

    _pos = [0, 0, 0, 0, 0, 0]
    api.set_pos_all(_pos)
    time.sleep(1)  

def do_defined_move(api):
    defined_pos = []
    _back1 = [-20, -20, -20, -20, -20, -20]
    defined_pos1 = [2.8, 3.9, 4.2, 4.6, 8.0, 6.6]
    defined_pos2 = [9, 9, 9, 9, 9, 4]
    defined_pos3 = [2, 2, 2, 2, 5, 0]
    _stop = [0, 0, 0, 0, 0, 0]

    while True:
        action_id = int(input("input id from 1-3(move) or 4(quit): "))

        api.calibration()
        time.sleep(0.01)  

        if action_id < 1 or action_id > 4:
            print("action id error")
            continue
        elif action_id == 1:
            defined_pos = defined_pos1
        elif action_id == 2:
            defined_pos = defined_pos2
        elif action_id == 3:
            defined_pos = defined_pos3
        elif action_id == 4:
            break

        api.set_pos_all(defined_pos)
        time.sleep(2)  
        api.set_pos_all(_back1)
        time.sleep(2)  
        api.set_pwm(_stop)
        time.sleep(0.01)  
        
def do_defined_pwm(api):
    _back = [-200, -200, -200, -200, -200, -200]
    _forward = [200, 200, 200, 200, 200, 200]
    _stop = [0, 0, 0, 0, 0, 0]
    api.set_pwm(_forward)
    time.sleep(2)
    api.set_pwm(_back)
    time.sleep(2)
    api.set_pwm(_stop)
    time.sleep(2)


if __name__ == '__main__':
    ip_left = "192.168.137.39" # lefthand
    # ip_right = "192.168.137.19" # righthand
    api = API(ip_left, HandSocket.dh_port_ctrl, HandSocket.dh_port_comm)

    calibration_test(api)

    do_defined_move(api)

    do_defined_pwm(api)



