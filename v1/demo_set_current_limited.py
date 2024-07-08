import dh
from dh_logger import logger

def main():
    dh.set_limit_current(1, 3900)

    data = dh.get_current_limited()
    if data is not None:
        for ele in data:
            print(ele)

if __name__ == '__main__':
    main()