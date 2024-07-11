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
    start_angel = 2.0
    end_angle = 10.0
    if api.set_pos_limited(id, [start_angel, end_angle]) == FunctionResult.FAIL:
        logger.print_trace_error("set_pos_limited failed")
    else:    
        logger.print_trace("set_pos_limited success")
    time.sleep(1)

    # verify
    pos_limited = api.get_pos_limited()
    if len(pos_limited) != 12:
        logger.print_trace_error("get pos_limited failed")
    else:
        logger.print_trace("get pos_limited success", pos_limited)

    # reset position
    _back, _stop = [-200, -200, -200, -200, -200, -200], [0, 0, 0, 0, 0, 0]
    api.set_pwm(_back)
    time.sleep(2)
    api.set_pwm(_stop)
    time.sleep(0.01)

if __name__ == "__main__":
    main()
