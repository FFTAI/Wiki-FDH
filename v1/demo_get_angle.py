import dh
import time
from dh_logger import logger
import math

def main():
    # i = 0
    # A = 3
    # W = 0.1
    # print("calibration start")
    # val = -10000
    # dh.calibration()
    # time.sleep(1);

    # for i in range(1, 7):
    #     dh.set_target_angle(i, val);
    
    # time.sleep(1)
    
    # dh.calibration()
    # time.sleep(1);
    # dh.calibration()
    # time.sleep(1);
    # print("calibration finished")
    
    # # pid = [100, 1.70, 0.8]
    # # dh.set_pid_angle(3, pid)
    # # time.sleep(1)
    
    while True:
        # target_pos = A * math.cos(W*i)
        target_pos = 6
        dh.set_target_angle(6, target_pos)
        for j in range(0, 150):
            dh.get_angle()
            time.sleep(0.001)
        target_pos = 0
        dh.set_target_angle(6, target_pos)
        for j in range(0, 150):
            dh.get_angle()
            time.sleep(0.001)
        

if __name__ == '__main__':
    main()
