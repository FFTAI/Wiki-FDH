import dh
import time
from dh_logger import logger

def main():
    dh.calibration()
    time.sleep(3)
    target_angle = [0, 0, 0, 0, 0, 0]
    while True:
        # id = input("id : ")
        # target = input("target : ")
        # index = int(id) - 1
        # target_angle[index] = int(target)
        finger1 = [ target_angle[0],   100.1,  0.4,  0.01]     # 1  -800~0
        finger2 = [ target_angle[1],   200.1,  0.61,  0.01]     # 2   0~1100
        finger3 = [ target_angle[2],   100.1,  0.0,  0.00]     # 3  0~1100  
        finger4 = [ target_angle[3],   100.1,  0.51,  0.001]     # 4  0~1000 error
        finger5 = [ target_angle[4],   100.1,  0.00,  0.00]     # 5 errror
        finger6 = [ target_angle[5],   100.1,  0.0,  0.00]     # 6
        dh.loop_angle(finger1, finger2, finger3, finger4, finger5, finger6)
        target_angle = [0, 0, 0, 0, 0, 0]
    # 1 6 4 2 3 5
    # time.sleep(2)

    #           angle, p,  i,    d
    # finger1 = [ -700,   20.1,  0.81,  0.021]     # 1  -800~0
    # finger2 = [ 1100,   10.1,  0.51,  0.081]     # 2   0~1100
    # finger3 = [ 1200,   10.1,  0.81,  0.001]     # 3  0~1100
    # finger4 = [ 0,   10.1,  0.51,  0.001]     # 4  0~1000
    # finger5 = [ -1100,   10.1,  0.51,  0.001]    # 5 -1100~0 
    # finger6 = [ -1100,   10.1,  0.51,  0.001]     # 6 -1100~0    
    
    # dh.loop_angle(finger1, finger2, finger3, finger4, finger5, finger6)
    # # 1 6 4 2 3 5
    # time.sleep(2)

    # finger1 = [ -700,   20.1,  0.81,  0.021]     # 1  -800~0
    # finger2 = [ 1100,   10.1,  0.51,  0.081]     # 2   0~1100
    # finger3 = [ 1200,   10.1,  0.81,  0.001]     # 3  0~1100
    # finger4 = [ 1000,   10.1,  0.51,  0.001]     # 4  0~1000
    # finger5 = [ -1100,   10.1,  0.51,  0.001]    # 5 -1100~0 
    # finger6 = [ -1100,   10.1,  0.51,  0.001]     # 6 -1100~0

    # dh.loop_angle(finger1, finger2, finger3, finger4, finger5, finger6)

    # time.sleep(2)

    # finger1 = [ -0,   20.1,  0.81,  0.021]     # 1  -800~0
    # finger2 = [ 1100,   10.1,  0.51,  0.081]     # 2   0~1100
    # finger3 = [ 1200,   10.1,  0.81,  0.001]     # 3  0~1100
    # finger4 = [ 1000,   10.1,  0.51,  0.001]     # 4  0~1000
    # finger5 = [ -1100,   10.1,  0.51,  0.001]    # 5 -1100~0 
    # finger6 = [ -1100,   10.1,  0.51,  0.001]     # 6 -1100~0

    # dh.loop_angle(finger1, finger2, finger3, finger4, finger5, finger6)

if __name__ == '__main__':
    main()
