import dh
from dh_logger import logger

def main():
    
    pid_debug = 1

    finger1 = [ 0,   80.1,  0.1,  0.0]     # 1  -800~0
    finger2 = [ 0,   200.1,  0.61,  0.01]     #1 2   0~1100
    finger3 = [ 0,   100.1,  0.5,  0.01]     # 3  0~1100  
    finger4 = [ 0,   60.1,  0.21,  0.001]     # 4  0~1000 error
    finger5 = [ 0,   200.1,  0.50,  0.01]     # 5 errror
    finger6 = [ 0,   150.1,  0.5,  0.01]     # 6
    hand = [finger1, finger2, finger3, finger4, finger5, finger6]

    set_target = input("target: ")
    hand[pid_debug-1][0] = float(set_target)
    dh.pid_param(hand[0], hand[1], hand[2], hand[3], hand[4], hand[5])

    while True:
        angle = dh.get_angle()
        

    

if __name__ == '__main__':
    main()
