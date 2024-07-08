import dh
import time
import sys
from dh_logger import Logger
import math

def new_calibration():
    go_home = [-200, -200, -200, -200, -200, -200]
    back = [200, 200, 200, 200, 200, 200]
    stop = [0, 0, 0, 0, 0, 0]

    last_cnt = []
    for i in range(10):
        last_cnt = dh.get_cnt()
        if last_cnt[0] == 0:
            print("communication error, check ip or line")
            continue
    
    dh.set_target_pwm_all(go_home)
    go_back_counts = 0
    time.sleep(0.1)
    for i in range(100):
        cnt = dh.get_cnt()
        if cnt == last_cnt:
            go_back_counts += 1
            if go_back_counts > 5:
                dh.calibration()
                time.sleep(0.1)
                default_pos = [2.8, 3.9, 4.2, 4.6, 8.0, 6.6]
                dh.set_target_position_all(default_pos)
                time.sleep(0.1)
                print("calibration done")
                return True
            dh.set_target_pwm_all(back)
        else:
            dh.set_target_pwm_all(go_home)
        last_cnt = cnt
        time.sleep(0.01)
    dh.set_target_pwm_all(stop)
    time.sleep(0.1)
    print("calibration failed")
    return False 



def main():
    if new_calibration():
        pass
    else:
        print("calibration failed")
        return
    time.sleep(1)
    counts = 0
    w_f = [5,5,5,5,0.5,5]
    while True:
        
        for i in range(1,7):
            tar =  counts * w_f[i-1]
            if i == 5 and counts < 3:
                tar = 0
            dh.set_target_pd_pos(i, tar, 7)
            time.sleep(0.001)
        time.sleep(0.1)
        if counts > 10:
            counts = 0
            break

        counts += 1

if __name__ == '__main__':
    main()