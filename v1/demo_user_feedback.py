import dh
import numpy as np
from dh_logger import logger

def main():
    data = dh.get_fdb()
    for i in range(0, 6):
        logger.print_trace("angle: {}, status: {}, errorcode: {}, controller: {}".format(data[i][0], data[i][1], data[i][2], data[i][3]))


if __name__ == '__main__':
    main()