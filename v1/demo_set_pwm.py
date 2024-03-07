import dh
import time
from dh_logger import logger

#   id      up     dowm
#   1       400     400

def main():

 
    open_hand = 1
    pwm = -3000 * open_hand
    dh.debug_motor_set_pwm(1, pwm)
    time.sleep(2)
    dh.debug_motor_stop(0)
   


if __name__ == '__main__':
    main()
