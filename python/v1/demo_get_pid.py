import dh
from dh_logger import logger

def main():
    pid_p = dh.get_p()
    pid_i = dh.get_i()
    pid_d = dh.get_d()

    for i in range(0, 6):
        logger.print_trace("id: {}, p: {}, i: {}, d: {}".format(i, pid_p[i], pid_i[i], pid_d[i]))



if __name__ == '__main__':
    main()