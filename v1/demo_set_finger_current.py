import dh
from dh_logger import logger
import time

def main():
    id = 2
    target = -100
    dh.set_target_current(id, target)
    time.sleep(1)
    # dh.set_target_current(id, 0)

if __name__ == '__main__':
    main()