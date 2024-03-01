import dh
from dh_logger import logger

def main():
    # angle = dh.get_angle(1)
    # print(angle)

    angle1, angle2, angle3, angle4, angle5, angle6 = dh.get_angle(0)
    print(angle1, angle2, angle3, angle4, angle5, angle6)

if __name__ == '__main__':
    main()
