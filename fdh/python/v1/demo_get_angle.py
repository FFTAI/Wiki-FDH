import dh
from dh_logger import logger

def main():
    angle = dh.get_angle()
    for ele in angle:
        print(ele)
    

if __name__ == '__main__':
    main()
