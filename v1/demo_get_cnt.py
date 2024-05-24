import dh
from dh_logger import logger
import time


def main():
    while True:
        data = dh.get_cnt()
        # for ele in data:
        print(data[5])
        time.sleep(0.01)


if __name__ == '__main__':
    main()
