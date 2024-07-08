import dh
import time
from dh_logger import logger

def main():
    # dh.set_target_angle(1, -10000)
    dh.set_target_pwm_all([80, 100, 150, 200, 150, 0])
    while True:
        data = dh.get_current()
        for ele in data:
            print(ele)
        time.sleep(0.005)
        # angle = dh.get_angle()
        # for ele in angle:
        #     print(ele)
if __name__ == '__main__':
    main()
