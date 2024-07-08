import dh
import time
import math
from dh_logger import logger

def main():
   
    val = -10000

    # dh.calibration()
    # time.sleep(1);

    # for i in range(1, 7):
    #     dh.set_target_angle(i, val);
    
    # time.sleep(1)
    
    # dh.calibration()
    # time.sleep(1);
    # dh.calibration()
    # time.sleep(1);

    # while True:
    #     dh.set_target_angle(id, 0)
    #     # dh.set_target_angle(2, 800)
    #     # dh.set_target_angle(6, -800)
    #     # dh.set_target_angle(3, 800)
    #     # dh.set_target_angle(4, -800)
    #     time.sleep(1.5)
    #     # dh.set_target_angle(5, 0);
    #     # dh.set_target_angle(2, 0);
    #     # dh.set_target_angle(6, 0);  
    #     dh.set_target_angle(id, val)
    #     # dh.set_target_angle(3, 0);
    #     time.sleep(1.5)
        
    dh.set_target_angle(3, 5);
    # dh.set_target_angle(4, 0);

    # dh.set_target_angle(3, 8);
    # dh.set_target_angle(2, 1100);
    # target_all = [0,0,0,0,0,0]
    # dh.set_target_position_all(target_all)
    # dh.set_target_angle(5, 1100);
    # dh.set_target_angle(5, 4);
    # pid = [800, 0, 0.10]
    # dh.set_pid_angle(2, pid)
    
    
    # for i in range(0, 10000000):
    # #     w = 0.01
    # #     pos = 5 * math.cos(w * i) + 5
    # #     print(pos)
    #     pos = 5;
    #     dh.set_target_angle_test(5, pos);
    #     dh.set_target_angle_test(6, pos);
    #     dh.set_target_angle_test(2, pos);
    #     dh.set_target_angle_test(3, pos);
    #     dh.set_target_angle_test(4, pos);
    # #     # dh.set_target_angle(1, pos/2);
    #     time.sleep(2);
    #     pos = 10
    #     dh.set_target_angle_test(5, pos);
    #     dh.set_target_angle_test(6, pos);
    #     dh.set_target_angle_test(4, pos);
    #     dh.set_target_angle_test(3, pos);
    #     dh.set_target_angle_test(2, pos);
    #     time.sleep(2)
    #     dh.set_target_angle(1, pos);
    #     time.sleep(0.0004 * pos);
        # pos = 0;
        # dh.set_target_angle(1, pos);
        # time.sleep(1);
        # dh.set_target_angle(5, pos);
        # dh.set_target_angle(4, pos);
        # dh.set_target_angle(3, pos);
        # dh.set_target_angle(2, pos);
        # dh.set_target_angle(6, pos);
        # time.sleep(2)


        
    
   

if __name__ == '__main__':
    main()