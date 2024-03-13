import dh
from dh_logger import logger

def main():
    pid = [455, 0.8, 0.4]
    dh.set_pid_angle(6, pid)

if __name__ == '__main__':
    main()