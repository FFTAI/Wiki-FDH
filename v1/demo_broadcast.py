import dh
from dh_logger import logger
import time

def main():
    while True:
        dh.broadcast()
        time.sleep(0.001)

if __name__ == '__main__':
    main()