import dh
import time
from dh_logger import logger

def main():
    target_angle = [0, 0, 0, 0, 0, 0]
    data_limit = []
    data_fdb = []
    logger.print_trace("id取值-> calibration:0, get jont limit:-1, get fdb: -2, 1,2,3,4,5,6操作关节id, set 6 target: 7")
    logger.print_trace("action id: reset: 20 OK: 21")
    while True:
        id = input("id : ")
        if int(id) == 0:
            dh.calibration()
            continue
        if int(id) == -1:
            data_limit = dh.get_angle_limited()
            for ele in data_limit:
                logger.print_trace("finger limit: {}".format(ele))
            continue
        if int(id) == -2:
            data_fdb = dh.get_fdb()
            if data_fdb == None:
                logger.print_trace("get data failed")
                continue
            for i in range(0, 6):
                logger.print_trace("angle: {}, status: {}, errorcode: {}, controller: {}".format(data_fdb[i][0], data_fdb[i][1], data_fdb[i][2], data_fdb[i][3]))
            continue
        # if data_limit != None:
        #     logger.print_trace("\nid:1   limit: {}~0\nid:2   limit: 0~{}\nid:3   limit: 0~{}\nid:4   limit: 0~{}\nid:5   limit: 0~{}\nid:6   limit: 0~{}".format(data_limit[0], data_limit[1], data_limit[2], data_limit[3], data_limit[4], data_limit[5]))
        # else:
        #     logger.print_trace("please run id = -2, get limit")
        #     continue
        id_int = int(id)
        
        if id_int == 7:
            for i in range(0, 6):
                target_angle[i] = input("id: {}, target: ".format(i))
        elif id_int == 1 or id_int == 2 or id_int == 3 or id_int == 4 or id_int == 5 or id_int == 6:
            target_angle[int(id) -1] = int(input("id: {}, input target is: ".format(id)))
        elif id_int == 21:
            target_angle = [-500, 150, 500, 990, 800, 350]
        elif id_int == 20:
            target_angle = [-0, 0, 0, 0, 0, 0]
        else:
            logger.print_trace("id error")

        finger1 = [ target_angle[0],   100.1,  0.4,  0.01]     # 1  -800~0
        finger2 = [ target_angle[1],   200.1,  0.61,  0.01]     #1 2   0~1100
        finger3 = [ target_angle[2],   100.1,  0.0,  0.00]     # 3  0~1100  
        finger4 = [ target_angle[3],   100.1,  0.51,  0.001]     # 4  0~1000 error
        finger5 = [ target_angle[4],   100.1,  0.00,  0.00]     # 5 errror
        finger6 = [ target_angle[5],   100.1,  0.0,  0.00]     # 6
        dh.loop_angle(finger1, finger2, finger3, finger4, finger5, finger6)
        # target_angle = [0, 0, 0, 0, 0, 0]
    # 1 6 4 2 3 5
    # time.sleep(2)

    #           angle, p,  i,    d
    # finger1 = [ -700,   20.1,  0.81,  0.021]     # 1  -800~0
    # finger2 = [ 1100,   10.1,  0.51,  0.081]     # 2   0~1100
    # finger3 = [ 1200,   10.1,  0.81,  0.001]     # 3  0~1100
    # finger4 = [ 0,   10.1,  0.51,  0.001]     # 4  0~1000
    # finger5 = [ -1100,   10.1,  0.51,  0.001]    # 5 -1100~0 
    # finger6 = [ -1100,   10.1,  0.51,  0.001]     # 6 -1100~0    
    
    # dh.loop_angle(finger1, finger2, finger3, finger4, finger5, finger6)
    # # 1 6 4 2 3 5
    # time.sleep(2)

    # finger1 = [ -700,   20.1,  0.81,  0.021]     # 1  -800~0
    # finger2 = [ 1100,   10.1,  0.51,  0.081]     # 2   0~1100
    # finger3 = [ 1200,   10.1,  0.81,  0.001]     # 3  0~1100
    # finger4 = [ 1000,   10.1,  0.51,  0.001]     # 4  0~1000
    # finger5 = [ -1100,   10.1,  0.51,  0.001]    # 5 -1100~0 
    # finger6 = [ -1100,   10.1,  0.51,  0.001]     # 6 -1100~0

    # dh.loop_angle(finger1, finger2, finger3, finger4, finger5, finger6)

    # time.sleep(2)

    # finger1 = [ -0,   20.1,  0.81,  0.021]     # 1  -800~0
    # finger2 = [ 1100,   10.1,  0.51,  0.081]     # 2   0~1100
    # finger3 = [ 1200,   10.1,  0.81,  0.001]     # 3  0~1100
    # finger4 = [ 1000,   10.1,  0.51,  0.001]     # 4  0~1000
    # finger5 = [ -1100,   10.1,  0.51,  0.001]    # 5 -1100~0 
    # finger6 = [ -1100,   10.1,  0.51,  0.001]     # 6 -1100~0

    # dh.loop_angle(finger1, finger2, finger3, finger4, finger5, finger6)

if __name__ == '__main__':
    main()
