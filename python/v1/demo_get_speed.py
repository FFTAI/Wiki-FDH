import dh
from dh_logger import logger

def main():
    data = dh.get_anglular_speed()
    for ele in data:
        print(ele)

if __name__ == '__main__':
    main()