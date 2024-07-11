import sys, os
sys.path.append(os.path.join(os.path.dirname(__file__), "../"))
from Hand_Sdk.HandSocket import *
from Hand_Sdk.Handapi import *
import time, math


def main():
    ip_left = "192.168.137.39" # lefthand
    # ip_right = "192.168.137.19" # righthand
    api = API(ip_left)
    api.calibration()
    time.sleep(1)

    # set
    id = 1
    angle = 4.0
    omega = 7.0
    if api.set_pd_control(id, angle, omega) == FunctionResult.FAIL:
        logger.print_trace_error("set_pd_control failed")
    else:    
        logger.print_trace("set_pd_control success")
    time.sleep(1)

    # verify
    pos = api.get_pos()
    if len(pos) != 6:
        logger.print_trace_error("get pos failed")
    else:
        logger.print_trace("get pos success", pos)

    # reset position
    _back, _stop = [-200, -200, -200, -200, -200, -200], [0, 0, 0, 0, 0, 0]
    api.set_pwm(_back)
    time.sleep(2)
    api.set_pwm(_stop)
    time.sleep(0.01)

if __name__ == "__main__":
    main()


