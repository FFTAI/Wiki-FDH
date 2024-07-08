import dh
from dh_logger import logger

def main():
    dh.set_limit_omega(1, 9999)

    data = dh.get_omega_limited()
    if data is not None:
        for ele in data:
            print(ele)

if __name__ == '__main__':
    main()