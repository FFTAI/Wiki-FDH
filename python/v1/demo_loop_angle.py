import dh
import time
from dh_logger import logger

def main():
    target_angle = [0, 0, 0, 0, 0, 0]
    data_limit = []
    data_fdb = []
    
    finger1 = [ 0,   450.0,  0.6,  0.3]     # 1  -800~0
    finger2 = [ 0,   450.0,  0.6,  0.3]     #1 2   0~1100
    finger3 = [ 0,   450.0,  0.6,  0.3]     # 3  0~1100  
    finger4 = [ 0,   450.0,  0.6,  0.3]     # 4  0~1000 error
    finger5 = [ 0,   450.0,  0.6,  0.3]     # 5 errror
    finger6 = [ 0,   450.0,  0.6,  0.3]     # 6
    hand = [finger1, finger2, finger3, finger4, finger5, finger6]

    logger.print_trace("id取值-> calibration:0, get jont limit:-1, get fdb: -2, 1,2,3,4,5,6操作关节id, set 6 target: 7")
    logger.print_trace("action id: reset: 20 OK: 21")
    while True:
        angle = dh.get_angle()
        for ele in angle:
            print(ele)
        id = input("id : ")
        if int(id) == 0:
            dh.calibration()
            continue
        if int(id) == -1:
            data_limit = dh.get_angular_range()
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
                set_target = input("id: {}, target: ".format(i))
                hand[i][0] = int(set_target)
        elif id_int == 1 or id_int == 2 or id_int == 3 or id_int == 4 or id_int == 5 or id_int == 6:
            set_target = int(input("id: {}, input target is: ".format(id)))
            hand[int(id)-1][0] = int(set_target)
        elif id_int == 21:
            hand[0][0] = -350
            hand[1][0] = 150
            hand[2][0] = 500
            hand[3][0] = 800
            hand[4][0] = 850
            hand[5][0] = 350

        elif id_int == 22:
            hand[0][0] = -900
            hand[1][0] = 1100
            hand[2][0] = 1100
            hand[3][0] = 0
            hand[4][0] = 1100
            hand[5][0] = 1100

        elif id_int == 23:
            hand[0][0] = -0
            hand[1][0] = 1100
            hand[2][0] = 0
            hand[3][0] = 0
            hand[4][0] = 0
            hand[5][0] = 1100

        elif id_int == 24:
            hand[0][0] = -0
            hand[1][0] = 1100
            hand[2][0] = 1100
            hand[3][0] = 900
            hand[4][0] = 990
            hand[5][0] = 1100

        elif id_int == 25:
            while (id_int - 10) > 0:
                hand[0][0] = -0
                hand[1][0] = 0
                hand[2][0] = 500
                hand[3][0] = 0
                hand[4][0] = 500
                hand[5][0] = 0
                dh.loop_angle(hand[0], hand[1], hand[2], hand[3], hand[4], hand[5], angle)
                time.sleep(0.5)
                hand[0][0] = -500
                hand[1][0] = 0
                hand[2][0] = 0
                hand[3][0] = 500
                hand[4][0] = 0
                hand[5][0] = 500
                dh.loop_angle(hand[0], hand[1], hand[2], hand[3], hand[4], hand[5], angle)
                id_int = id_int -1
            continue

        elif id_int == 20:
            hand[0][0] = -0
            hand[1][0] = 0
            hand[2][0] = 0
            hand[3][0] = 0
            hand[4][0] = 0
            hand[5][0] = 0

        elif id_int == 999:
            hand[0][0] = -0
            hand[1][0] = 1100
            hand[2][0] = 0
            hand[3][0] = 900
            hand[4][0] = 990
            hand[5][0] = 1100

        else:
            logger.print_trace("id error")
        
        dh.loop_angle(hand[0], hand[1], hand[2], hand[3], hand[4], hand[5], angle)
        # target_angle = [0, 0, 0, 0, 0, 0]
    

if __name__ == '__main__':
    main()
