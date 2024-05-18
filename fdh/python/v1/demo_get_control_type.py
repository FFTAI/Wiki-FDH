import dh
from dh_logger import logger

def main():
    data = dh.get_controltype()
    for i in data:
        print(i)

if __name__ == '__main__':
    main()