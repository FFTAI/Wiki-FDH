import sys, os
sys.path.append(os.path.join(os.path.dirname(__file__), "../"))
from Hand_Sdk.HandSocket import *
from Hand_Sdk.Handapi import *

def main():
    ip_left = "192.168.137.39" # lefthand
    # ip_right = "192.168.137.19" # righthand
    api = API(ip_left)
    velocity_pid = api.get_velocity_pid()

    if len(velocity_pid) != 18:
        logger.print_trace_error("velocity_pid failed")
    else:
        logger.print_trace("velocity_pid success", velocity_pid)

if __name__ == "__main__":
    main()

