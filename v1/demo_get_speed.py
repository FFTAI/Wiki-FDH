import dh
from dh_logger import logger
import time
import math

def main():
    
    data = dh.get_anglular_speed()
    A = 3
    W  = 0.1
    i = 0
    while True:
        target_pos = A * math.cos(W*i) + 3
        dh.set_target_angle(2, target_pos)
        i = i + 1
        time.sleep(0.001)
        
    for ele in data:
        print(ele)

if __name__ == '__main__':
    main()