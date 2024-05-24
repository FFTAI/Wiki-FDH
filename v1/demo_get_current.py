import dh
import time
from dh_logger import logger

def main():
    # dh.set_target_angle(1, -10000)
    while True:
        data = dh.get_current()
        for ele in data:
            print(ele)
        angle = dh.get_angle()
        for ele in angle:
            print(ele)
if __name__ == '__main__':
    main()
