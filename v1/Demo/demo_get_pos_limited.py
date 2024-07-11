import sys, os
sys.path.append(os.path.join(os.path.dirname(__file__), "../"))
from Hand_Sdk.HandSocket import *
from Hand_Sdk.Handapi import *

def main():
    ip_left = "192.168.137.39" # lefthand
    # ip_right = "192.168.137.19" # righthand
    api = API(ip_left)
    pos_limited = api.get_pos_limited()

    if len(pos_limited) != 12:
        logger.print_trace_error("get pos_limited failed")
    else:
        logger.print_trace("get pos_limited success", pos_limited)

if __name__ == "__main__":
    main()


