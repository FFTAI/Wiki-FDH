import dh
import time

def fore_thumb():
    for i in range(2, 7):
        dh.set_target_angle(int(i), 0) 
    dh.set_target_angle(1, -200)
    time.sleep(1)
    
    dh.set_target_angle(4, 950)
    dh.set_target_angle(1, -400)
    dh.set_target_angle(5, 700)
    
    time.sleep(0.8)
    dh.set_target_current(1, 1000)
    dh.set_target_current(5, 1000)
    time.sleep(0.5)
    
    for i in range(2, 7):
        dh.set_target_angle(int(i), 0) 
    dh.set_target_angle(1, -200)
    time.sleep(1) 


def max_limit():
    for i in range(2, 7):
        dh.set_target_angle(int(i), 0) 
    dh.set_target_angle(1, -200)
    time.sleep(1)
    
    dh.set_target_angle(4, 1100)
    dh.set_target_angle(1, -400)
    dh.set_target_angle(3, 700)
    # dh.set_target_angle(5, 700)
    
    


def main():
    fore_thumb()
    max_limit()
    

if __name__ == '__main__':
    main()