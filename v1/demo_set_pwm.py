import dh
import time
from dh_logger import logger

def main():

    dh.debug_motor_stop(0)
    time.sleep(1)
    dh.debug_motor_set_pwm(0, 252)


if __name__ == '__main__':
    main()
