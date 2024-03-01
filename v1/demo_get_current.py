import dh
from dh_logger import logger

def main():
    # current = dh.get_current(1)
    # print(current)

    current1, current2, current3, current4, current5, current6 = dh.get_current(0)
    print(current1, current2, current3, current4, current5, current6)


if __name__ == '__main__':
    main()
