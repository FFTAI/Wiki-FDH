import dh
from dh_logger import logger

def main():
    # angular_speed = dh.get_angular_speed(1)
    # print(angular_speed)

    angular_speed1, angular_speed2, angular_speed3, angular_speed4, angular_speed5, angular_speed6 = dh.get_angle(0)
    print(angular_speed1, angular_speed2, angular_speed3, angular_speed4, angular_speed5, angular_speed6)


if __name__ == '__main__':
    main()
