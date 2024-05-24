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
                print("[" + time_now + "] ", end=' ')
                print(*objects, sep=sep, end=end, file=file, flush=flush)
    
    def print_variable(self, *objects, sep=' ', end='\n', file=fd, flush=False):
        print(*objects, end= end)

logtest = LogTest()


def is_arrive():
    pass


def test_calibration():
    logtest.print_trace("calibration start")
    val = -10000
    dh.calibration()
    time.sleep(1);

    for i in range(1, 7):
        dh.set_target_angle(i, val);
    
    time.sleep(1)
    
    dh.calibration()
    time.sleep(1);
    dh.calibration()
    time.sleep(1);
    # target_all = [0,0,0,0,0,0]
    # dh.set_target_position_all(target_all)
    # time.sleep(1);
    logtest.print_trace("calibration finished")


def fatigue_testing():
    counts = input("Please input cycle times: ")
    logtest.print_variable(counts)
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
    
    issingle = input("Whether to operate with only one finger(yes/no):")
    logtest.print_variable(str(issingle))
    
    if issingle == "yes":
        while True:
            id = input("Please enter the operating finger id(1~6): ")
            id = int(id)
            logtest.print_variable(id)
            if id != 1 and id != 2 and id != 3 and id != 4 and id != 5 and id != 6:
                continue
            
            target = input("Please enter the operating finger{} target: ".format(id))
            target = float(target)
            logtest.print_variable(target)

            if target < 0 or target > 11:
                logtest.print_trace("Angle set failed, please check limit")
                continue
            counts =  input("Please enter the times: ")
            logtest.print_variable(int(counts))
            
            for j in range(0, int(counts)):
                dh.set_target_angle(id, target)
                time.sleep(3)
                dh.set_target_angle(id, 0)
                time.sleep(3)
                msg = "times: " + str(j)
                logtest.print_trace(msg)
            break
    elif issingle == "no":
        opr_id = []
        opr_target = []
        
        while True:
            while True:
                temp = input("Please input id('q' will exit): ")
                if temp == 'q':
                    logtest.print_variable(str(temp))
                    break
                logtest.print_variable(int(temp))
                opr_id.append(temp)
            
            for i in opr_id:
                temp_target = input("id:{}, target: ".format(i))
                opr_target.append(temp_target)
                logtest.print_variable(float(temp_target))
            
            counts = input("Please enter the times: ")
            logtest.print_variable(int(counts))

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
                logtest.print_trace(msg)
            return
               

# 400 700 950
def backhome():
    logtest.print_trace("back home ...")
    for i in range(1, 7):
        dh.set_target_angle(i, 0)
    time.sleep(1)   
    logtest.print_trace("back home finished")

def grip_test():
    logtest.print_trace("grip ...")
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
    logtest.print_trace("The motor is in gridlock ...")
     
def set_position():
    logtest.print_trace("set position ...")
    set_list = []
    for i in range(1, 7):
        target = input("Please input id: {} , target: ".format(i))
        logtest.print_variable(float(target))
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
    logtest.print_trace("COMMAND-> " + "Connection: 0, " + "Calibration: 1, " + "Fatigue Testing: 2, " + "Agnle Controller: 3, " + "set_position: 4, " + "backhome: 5, " 
                    + "grip: 6")

    
    while True:
        state = input("Please input command: ")
        logtest.print_variable(state)
        switch_function(int(state))

if __name__ == '__main__':
    main()