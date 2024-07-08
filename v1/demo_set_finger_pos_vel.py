import dh
from dh_logger import logger
import time

def main():
    
    val = -10000
    dh.calibration()
    time.sleep(1);

    for i in range(1, 7):
        dh.set_target_angle(i, val);
    
    time.sleep(1)
    
    dh.calibration()
    time.sleep(1);
    dh.calibration()
    time.sleep(1);
    
    while True:
        target = input("tar: ")
        pos = [target, 7]
        dh.set_new_angle(6, pos)
        for i in range(0, 300):
            dh.get_angle()
            time.sleep(0.01)


if __name__ == '__main__':
    main()