import dh
import time
from dh_logger import logger

def main():

    dh.debug_motor_stop(0)
    time.sleep(1)
    dh.debug_motor_set_pwm(0, 500)
    for i in range(1,10):
        dh.comm_get_cnt(3)
        time.sleep(0.5)
    
    dh.debug_motor_stop(0)


if __name__ == '__main__':
    main()
