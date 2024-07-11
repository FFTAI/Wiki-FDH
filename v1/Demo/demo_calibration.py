import sys, os
sys.path.append(os.path.join(os.path.dirname(__file__), "../"))
from Hand_Sdk.HandSocket import *
from Hand_Sdk.Handapi import *

def main():
    ip_left = "192.168.137.39" # lefthand
    # ip_right = "192.168.137.19" # righthand
    api = API(ip_left)
    result_code = api.calibration()

    if api.calibration() == FunctionResult.FAIL:
        logger.print_trace_error("calibration failed")
    else:
        logger.print_trace("calibration success")

if __name__ == "__main__":
    main()

