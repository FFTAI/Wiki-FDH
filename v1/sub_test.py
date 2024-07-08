import dh
import time
import sys
from dh_logger import Logger

# fd = open('log/log.txt', 'w')
# old_stdout = sys.stdout
# sys.stdout = fd

# class LogTest(dh_logger.Logger):
#     def print_trace(self, *objects, sep=' ', end='\n', file=fd, flush=False):
#         if self.state == dh_logger.Logger.STATE_ON:
#             if self.level <= dh_logger.Logger.LEVEL_TRANCE:
#                 time_now = str(
#                             "{:02d}_{:02d}_{:02d}_{:02d}.{:02d}.{:02d}".format(time.localtime().tm_year, time.localtime().tm_mon,
#                                                                                 time.localtime().tm_mday, time.localtime().tm_hour,
#                                                                                 time.localtime().tm_min, time.localtime().tm_sec))
#                 print("[" + time_now + "] ", end=' ')
#                 print(*objects, sep=sep, end=end, file=file, flush=flush)
    
#     def print_variable(self, *objects, sep=' ', end='\n', file=fd, flush=False):
#         print(*objects, end= end)

# logtest = LogTest()


def is_arrive():
    pass


def test_calibration():
    print("calibration start")
    val = -10000
    dh.calibration()
    time.sleep(1);

    for i in range(1, 7):
        dh.set_target_angle(i, val);
    
    time.sleep(2)
    
    dh.calibration()
    time.sleep(1);
    dh.calibration()
    time.sleep(1);
    # target_all = [0,0,0,0,0,0]
    # dh.set_target_position_all(target_all)
    # time.sleep(1);
    print("calibration finished")


def fatigue_testing():
    counts = input("Please input cycle times: ")
    print(counts)
    for i in range(1, 7):
        dh.set_target_angle(i, 0);
    time.sleep(1)
    
    for i in range(0, int(counts)):
        dh.set_target_angle(6, 9);
        dh.set_target_angle(1, 10);
        dh.set_target_angle(2, 10);
        dh.set_target_angle(3, 10);
        dh.set_target_angle(4, 10);
        time.sleep(0.8)
        dh.set_target_angle(5, 6);
        time.sleep(1)

        dh.set_target_angle(5, 0);
        time.sleep(0.5)
        dh.set_target_angle(6, 0);
        dh.set_target_angle(1, 0);
        dh.set_target_angle(2, 0);
        dh.set_target_angle(3, 0);
        dh.set_target_angle(4, 0);
        time.sleep(1)
        msg = "times: " + str(i)
        print(msg)
    print("Fatigue Testing successfully")

        
def try_connection():
    
    dh.set_target_pwm_all([200, 200, 200, 200, 140, 0])
    time.sleep(5)

    dh.set_target_pwm_all([0, 0, 0, 0, 0, 0])
    time.sleep(1)

            

def angle_controller():
    print("Angle Controller")
    
    issingle = input("Whether to operate with only one finger(yes/no):")
    print(str(issingle))
    
    if issingle == "yes":
        while True:
            id = input("Please enter the operating finger id(1~6): ")
            id = int(id)
            print(id)
            if id != 1 and id != 2 and id != 3 and id != 4 and id != 5 and id != 6:
                continue
            
            target = input("Please enter the operating finger{} target: ".format(id))
            target = float(target)
            print(target)

            if target < 0 or target > 11:
                print("Angle set failed, please check limit")
                continue
            counts =  input("Please enter the times: ")
            
            for j in range(0, int(counts)):
                dh.set_target_angle(id, target)
                time.sleep(1)
                dh.set_target_angle(id, 0)
                time.sleep(1)
                print(j+1)
            break
    elif issingle == "no":
        opr_id = []
        opr_target = []
        
        while True:
            while True:
                temp = input("Please input id('q' will exit): ")
                if temp == 'q':
                    print(str(temp))
                    break
                print(int(temp))
                opr_id.append(temp)
            
            for i in opr_id:
                temp_target = input("id:{}, target: ".format(i))
                opr_target.append(temp_target)
                print(float(temp_target))
            
            counts = input("Please enter the times: ")
            print(int(counts))

            for i in range(0, int(counts)):
                target_index = 0
                for id in opr_id:
                    dh.set_target_angle(id, opr_target[target_index])
                    target_index += 1
                time.sleep(1)
                for id in opr_id:
                    dh.set_target_angle(id, 0)
                time.sleep(1)
                msg = "times: " + str(i)
                print(msg)
            return
               

# 400 700 950
def backhome():
    print("back home ...")
    for i in range(1, 7):
        dh.set_target_angle(i, 0)
    time.sleep(1)   
    print("back home finished")

def grip_test():
    print("grip ...")
    for i in range(1, 7):
        dh.set_target_angle(6, 9);
        time.sleep(1)
        dh.set_target_angle(1, 10);
        dh.set_target_angle(2, 10);
        dh.set_target_angle(3, 10);
        dh.set_target_angle(4, 10);
        time.sleep(0.6)
        dh.set_target_angle(5, 6);
        time.sleep(1)
    time.sleep(1)   
    print("The motor is in gridlock ...")
     
def set_position():
    print("set position ...")
    set_list = []
    for i in range(1, 7):
        target = input("Please input id: {} , target: ".format(i))
        print(float(target))
        set_list.append(float(target))

    for i in range(1, 7):
        dh.set_target_angle(i, set_list[i-1])
    
    time.sleep(2)
    
   
switch_dict = {  
    0: try_connection,  
    1: test_calibration,  
    2: fatigue_testing,  
    3: angle_controller,
    4: set_position,
    5: backhome,
    6: grip_test
} 

def switch_function(value):  
    func = switch_dict.get(value)  
    return func()  

def main():
    # fd.close()
    print("COMMAND-> " + "Connection: 0, " + "Calibration: 1, " + "Fatigue Testing: 2, " + "Agnle Controller: 3, " + "set_position: 4, " + "backhome: 5, " 
                    + "grip: 6")

    
    while True:
        state = input("Please input command: ")
        print(state)
        switch_function(int(state))

if __name__ == '__main__':
    main()