import dh
import time
import sys
import dh_logger

fd = open('log/log.txt', 'w')
old_stdout = sys.stdout
sys.stdout = fd

class LogTest(dh_logger.Logger):
    def print_trace(self, *objects, sep=' ', end='\n', file=fd, flush=False):
        if self.state == dh_logger.Logger.STATE_ON:
            if self.level <= dh_logger.Logger.LEVEL_TRANCE:
                time_now = str(
                            "{:02d}_{:02d}_{:02d}_{:02d}.{:02d}.{:02d}".format(time.localtime().tm_year, time.localtime().tm_mon,
                                                                                time.localtime().tm_mday, time.localtime().tm_hour,
                                                                                time.localtime().tm_min, time.localtime().tm_sec))
                print(time_now, end=' ')
                print(*objects, sep=sep, end=end, file=file, flush=flush)
    
    def print_variable(self, *objects, sep=' ', end='\n', file=fd, flush=False):
        print(*objects, end= end)

logtest = LogTest()


def is_arrive():
    pass


def test_calibration():
    logtest.print_trace("calibration start")
    dh.calibration()
    logtest.print_trace("It's calibrating ...")
    time.sleep(13)
    logtest.print_trace("calibration finished")


def fatigue_testing():
    counts = input("Please input cycle times: ")
    for i in range(0, int(counts)):
        dh.set_target_angle(2, 1100.2)
        dh.set_target_angle(6, 1100.2)
        dh.set_target_angle(3, 1100.2)
        dh.set_target_angle(5, 1100.2)
        
        dh.set_target_angle(1, -800.2)
        time.sleep(0.1)
        dh.set_target_angle(4, 1000.2)
        
        
        time.sleep(1)
        
        dh.set_target_angle(2, 0)
        dh.set_target_angle(6, 0)
        dh.set_target_angle(3, 0)
        dh.set_target_angle(5, 0)
        
        dh.set_target_angle(1, -20)
        time.sleep(0.1)
        dh.set_target_angle(4, 0)
        time.sleep(1)
        msg = "times: " + str(i)
        logtest.print_trace(msg)
    logtest.print_trace("Fatigue Testing successfully")

        
def try_connection():
    
    ip = dh.get_ip()
    logtest.print_trace("Try connect ...")
    strip = dh.get_ip()
    if strip == " ":
        logtest.print_trace("Connect failed, try again")
    else:
        logtest.print_trace("Hand Connected")
            

def angle_controller():
    logtest.print_trace("Angle Controller")
    limit_angle = dh.get_angle_limited()
    
    for i in range(0, 6):
        logtest.print_trace(str(i) + ": " + str(limit_angle[i]))
    
    issingle = input("Whether to operate with only one finger(yes/no):")
    
    if issingle == "yes":
        while True:
            id = input("Please enter the operating finger id(1~6): ")
            id = int(id)
            if id != 1 and id != 2 and id != 3 and id != 4 and id != 5 and id != 6:
                continue
            
            target = input("Please enter the operating finger{} target: ".format(id))
            target = float(target)
            if id == 1 and (target > 0 or (target < float(limit_angle[0]))):
                logtest.print_trace("Angle set failed, please check limit")
                continue
            if (target < 0 or target > float(limit_angle[id-1])) and id != 1:
                logtest.print_trace("Angle set failed, please check limit")
                continue
            counts =  input("Please enter the times: ")
            for j in range(0, int(counts)):
                dh.set_target_angle(id, target)
                # while True:
                #     angle = dh.get_angle()
                #     if abs(target - float(angle[id-1])) < 1.875:
                #         break
                time.sleep(1)
                dh.set_target_angle(id, 0)
                # while True:
                #     angle = dh.get_angle()
                #     if abs(0 - float(angle[id-1])) < 1.875:
                #         break
                time.sleep(1)
            break
    elif issingle == "no":
        opr_id = []
        opr_target = []
        
        while True:
            while True:
                temp = input("Please input id('q' will exit): ")
                if temp == 'q':
                    break
                opr_id.append(temp)
            
            for i in opr_id:
                temp_target = input("id:{}, target: ".format(i))
                opr_target.append(temp_target)
            
            counts = input("Please enter the times: ")
            
            for i in range(0, int(counts)):
                target_index = 0
                for id in opr_id:
                    dh.set_target_angle(id, opr_target[target_index])
                    target_index += 1
                for i in range(0, 500):
                    data = dh.get_angle()
                    for j in opr_id:
                        logtest.print_trace(str(j) + ":" + str(data[int(j)-1]))
                    time.sleep(0.001)
                for id in opr_id:
                    dh.set_target_angle(id, 0)
                for i in range(0, 500):
                    data = dh.get_angle()
                    for j in opr_id:
                        logtest.print_trace(str(j) + ":" + str(data[int(j)-1]))
                    time.sleep(0.001)    
            return
        
        
def current_controller():
    logtest.print_trace("current Controller")
    limit_current = dh.get_current_limited()
    
    for i in range(0, 6):
        logtest.print_trace("current limit-->" + str(i) + ": " + str(limit_current[i]))
    
    issingle = input("Whether to operate with only one finger(yes/no):")
    
    if issingle == "yes":
        while True:
            id = input("Please enter the operating finger id(1~6): ")
            id = int(id)
            if id != 1 and id != 2 and id != 3 and id != 4 and id != 5 and id != 6:
                continue
            
            target = input("Please enter the operating finger{} target: ".format(id))
            target = float(target)
            if id == 1 and (target > 0 or (abs(target) > float(limit_current[0]))):
                logtest.print_trace("Current set failed, please check limit")
                continue
            if (abs(target) > float(limit_current[id-1])) and id != 1:
                logtest.print_trace("Current set failed, please check limit")
                continue
            counts =  input("Please enter the times: ")
            for j in range(0, int(counts)):
                dh.set_target_current(id, target)
                # while True:
                #     current = dh.get_current()
                #     if abs(target - float(current[id-1])) < 1.875:
                #         break
                time.sleep(1)
                dh.set_target_current(id, -target)
                # while True:
                #     current = dh.get_current()
                #     if abs(0 - float(current[id-1])) < 1.875:
                #         break
                time.sleep(1)
            break
    elif issingle == "no":
        opr_id = []
        opr_target = []
        
        while True:
            while True:
                temp = input("Please input id('q' will exit): ")
                if temp == 'q':
                    break
                opr_id.append(temp)
            
            for i in opr_id:
                temp_target = input("id:{}, target: ".format(i))
                opr_target.append(temp_target)
            
            counts = input("Please enter the times: ")
            
            for i in range(0, int(counts)):
                target_index = 0
                for id in opr_id:
                    dh.set_target_current(id, opr_target[target_index])
                    target_index += 1
                for i in range(0, 500):
                    data = dh.get_current()
                    for j in opr_id:
                        logtest.print_trace(str(j) + ":" + str(data[int(j)-1]))
                    time.sleep(0.001)
                target_index = 0
                for id in opr_id:
                    dh.set_target_current(id, -float(opr_target[target_index]))
                    target_index += 1
                for i in range(0, 500):
                    data = dh.get_current()
                    for j in opr_id:
                        logtest.print_trace(str(j) + ":" + str(data[int(j)-1]))
                    time.sleep(0.001)    
            return


def hand_grasp():
    force = input("Set current(0~3900): ")
    hold_time = input("Holding time(s): ")
    counts = input("Repeat times: ")
    data_limit = dh.get_angle_limited()
    for count in range(0, int(counts)):
        
        dh.set_target_angle(1, float(data_limit[0]))
        for i in range(2, 7):
            dh.set_target_angle(i, 0)
        time.sleep(1)
        
        force = int(force)
        dh.set_target_current(2, force)            
        dh.set_target_current(6, force)            
        dh.set_target_current(3, force)            
        dh.set_target_current(5, force)            
        dh.set_target_current(4, force) 
        time.sleep(0.8)
        dh.set_target_current(1, force)
        time.sleep(int(hold_time)) 
        
    for i in range(1, 7):
        dh.set_target_current(i, 0) 
               

# 400 700 950
def fore_thumb():
    counts = input("Repeat times: ")
    for i in range(0, int(counts)):
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
     
    
    
   
switch_dict = {  
    0: try_connection,  
    1: test_calibration,  
    2: fatigue_testing,  
    3: angle_controller,
    4: current_controller,
    5: hand_grasp,
    6: fore_thumb
} 

def switch_function(value):  
    func = switch_dict.get(value)  
    return func()  

def main():
    # fd.close()
    logtest.print_trace("COMMAND-> " + "Connection: 0, " + "Calibration: 1, " + "Fatigue Testing: 2, " + "Agnle Controller: 3, " + "Current Controller: 4, " + "Hand Grasp: 5, " 
                    + "Fore Thumb: 6")

    
    while True:
        state = input("Please input command: ")
        logtest.print_variable(state)
        switch_function(int(state))

if __name__ == '__main__':
    main()