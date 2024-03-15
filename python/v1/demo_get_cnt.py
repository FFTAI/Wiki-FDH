import dh
from dh_logger import logger

def main():
    
    data = dh.get_cnt()
    for ele in data:
        print(ele)

if __name__ == '__main__':
    main()
