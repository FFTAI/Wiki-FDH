import dh
import time
from dh_logger import logger

def main():
    while True:
        angle = dh.get_angle()
        # for ele in angle:
        #     print(ele)
        # time.sleep(0.5)
    

if __name__ == '__main__':
    main()
