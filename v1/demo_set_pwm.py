import dh
import time
from dh_logger import logger

#   id      up     dowm
#   1       400     400

def main():

    dh.debug_motor_stop(0)
    time.sleep(1)
    
    pwm = 3000
    
    
    # dh.debug_motor_set_pwm(0, pwm)
    # dh.debug_motor_set_pwm(3, -pwm)
    # dh.debug_motor_set_pwm(4, -pwm)
    # dh.debug_motor_set_pwm(5, -pwm)
    # dh.debug_motor_set_pwm(1, 1000)
    # time.sleep(3)
    dh.debug_motor_set_pwm(2, -pwm)
    time.sleep(5);
    # dh.debug_motor_stop(0)
    
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
