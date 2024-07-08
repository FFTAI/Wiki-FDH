import dh
import time
from dh_logger import logger

#   id      up     dowm
#   1       400     400

def main():

    dh.debug_motor_stop(0)
    time.sleep(1)
    open_hand = -1
    pwm = 2500 * open_hand
    
    if open_hand == 1:
        dh.debug_motor_set_pwm(1, -pwm)
        time.sleep(1)
        dh.debug_motor_set_pwm(1, pwm)
        dh.debug_motor_set_pwm(2, pwm)
        dh.debug_motor_set_pwm(3, pwm)
        dh.debug_motor_set_pwm(4, pwm+500)
        dh.debug_motor_set_pwm(5, pwm)
        dh.debug_motor_set_pwm(6, pwm)
        time.sleep(4)
        dh.debug_motor_set_pwm(1, pwm)
        time.sleep(1)
    elif open_hand == -1:
        dh.debug_motor_set_pwm(1, pwm)
        dh.debug_motor_set_pwm(2, pwm)
        dh.debug_motor_set_pwm(3, pwm)
        dh.debug_motor_set_pwm(4, pwm-500)
        dh.debug_motor_set_pwm(5, pwm)
        dh.debug_motor_set_pwm(6, pwm)
        time.sleep(1)
        dh.debug_motor_set_pwm(1, 0)
        time.sleep(0.5)
        dh.debug_motor_set_pwm(1, -pwm)
        time.sleep(1)

    dh.debug_motor_stop(0)

    # dh.debug_motor_set_pwm(0, pwm)
    # dh.debug_motor_set_pwm(4, -pwm)
    # dh.debug_motor_set_pwm(5, -pwm)
    # dh.debug_motor_set_pwm(1, 1000)
    # time.sleep(3)
    # dh.debug_motor_set_pwm(0, pwm)
    # dh.debug_motor_set_pwm(1, 3000)
    # time.sleep(1)
    
    # for i in range(500, 3000):
    #     dh.debug_motor_set_pwm(1, i)
    #     print(i)
    #     dh.debug_motor_set_pwm(i, -pwm)
    #     time.sleep(4)
    #     dh.debug_motor_set_pwm(i, pwm)
    #     time.sleep(4)
    #     dh.debug_motor_set_pwm(i, -pwm)
    #     time.sleep(4)
     
    # dh.debug_motor_stop(0)
    # while True:
    # dh.get_fdb()
   


if __name__ == '__main__':
    main()
