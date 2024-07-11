import sys, os
sys.path.append(os.path.join(os.path.dirname(__file__), "../"))
from Hand_Sdk.HandSocket import *
from Hand_Sdk.Handapi import *


def main():
    ip_left = "192.168.137.39" # lefthand
    # ip_right = "192.168.137.19" # righthand
    api = API(ip_left)

    current_pid = api.get_current_pid()

    if len(current_pid) != 18:
        logger.print_trace_error("get current_pid failed")
    else:
        logger.print_trace("get current_pid success :", current_pid)




if __name__ == "__main__":
    main()