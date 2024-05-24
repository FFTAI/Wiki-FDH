import dh
import time

def main():
    dh.calibration()
    time.sleep(13)
    
    while True:
        dh.set_target_angle(2, 1100.2)
        dh.set_target_angle(6, 1100.2)
        dh.set_target_angle(3, 1100.2)
        dh.set_target_angle(5, 1100.2)
        
        dh.set_target_angle(1, -800.2)
        time.sleep(0.1);
        dh.set_target_angle(4, 1000.2)
        
        
        time.sleep(1);
        
        dh.set_target_angle(2, 0)
        dh.set_target_angle(6, 0)
        dh.set_target_angle(3, 0)
        dh.set_target_angle(5, 0)
        
        dh.set_target_angle(1, -20)
        time.sleep(0.1);
        dh.set_target_angle(4, 0)
        time.sleep(1);
    

if __name__ == '__main__':
    main()