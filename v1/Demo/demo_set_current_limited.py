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
    current = 200.0
    if api.set_current_limited(id, current) == FunctionResult.FAIL:
        logger.print_trace_error("set_current_limited failed")
    time.sleep(0.01)

    # verify
    current_limited = api.get_current_limited()
    if len(current_limited) != 6:
        logger.print_trace_error("set_current_limited failed")
    else:
        logger.print_trace("set_current_limited success", current_limited)



if __name__ == "__main__":
    main()


