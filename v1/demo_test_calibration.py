import dh
import time
from dh_logger import logger

def main():

    forward = input("-1 or 1: ")
    pwm = 2500 * int(forward)
    dh.debug_motor_set_pwm(0, pwm)
    # dh.debug_motor_set_pwm(6, pwm)
    time.sleep(1)
    dh.debug_motor_stop(0)

if __name__ == '__main__':
    main()