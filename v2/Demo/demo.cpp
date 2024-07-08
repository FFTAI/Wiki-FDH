#include <iostream>
#include <vector>
#include <cstdint>
#include <cstring>
#include <mutex>
#include <cmath>

#include "../HandAPI/include/Handapi.h"
#include "../HandSocket/include/HandSocket.h"
#include "../HandAPI/include/HandapiFunctionResult.h"


#define LEFT_IP "192.168.137.39"
#define RIGHT_IP "192.168.137.19"

using namespace HandProtocol;

/**
 * @brief 重置校准
 *
 * 通过给定的 Handapi 对象进行重置校准操作。
 *
 * @param api Handapi 对象引用
 *
 * @return 返回校准结果，成功返回 APIResultCode::SUCCESS，失败返回 APIResultCode::FAIL
 */
int reset_calibrate(Handapi &api){
    std::vector<float> _back1{-200, -200, -200, -200, -200, -200}, _forward{200, 200, 200, 200, 200, 200}, _stop{0, 0, 0, 0, 0, 0};
    std::vector<long> m_last_cnt;
    for (int i = 0; i < 10; i++)
    {
        if (api.get_cnt(m_last_cnt) != 0)
        {
            std::cerr << "CALIBRATION COMMUNICATION FAILED, TRY AGAIN ..." << std::endl;
            if (i == 9)
            {
                std::cerr << "CALIBRATION FAILED" << std::endl;
                return APIResultCode::FAIL;
            }
            continue;
        }
        std::cout << "CALIBRAION START" << std::endl;
        break;
    }
    int go_back_counts = 0;
    api.set_pwm(_back1);
    usleep(2000000);
    for (int i = 0; i < 100; i++)
    {
        std::vector<long> m_cur_cnt;
        if (api.get_cnt(m_cur_cnt) != 0)
        {
            continue;
        }
        if (m_cur_cnt == m_last_cnt)
        {
            go_back_counts++;
            if (go_back_counts > 5)
            {
                api.calibration();
                usleep(100000);

                std::cout << "CALIBRATION SUCCESS" << std::endl;
                return APIResultCode::SUCCESS;
            }
            api.set_pwm(_forward);
        }
        else
        {
            api.set_pwm(_back1);
        }
        m_last_cnt = m_cur_cnt;
        usleep(10000);
    }
    api.set_pwm(_stop);
    usleep(10000);
    std::cerr << "CALIBRATION FAILED" << std::endl;
    return APIResultCode::FAIL;
}

/**
 * @brief 正弦运动
 *
 * 根据给定的 Handapi 对象，执行正弦运动控制。
 *
 * @param api Handapi 对象引用，用于设置位置和控制参数
 */
void sin_move(Handapi &api){
    for (int i = 0; i < 1500; i++)
            {
                for (int j = 1; j < 7; j++)
                {
                    float tar = 4 * (1 + sin(i * M_PI / 50 + j * M_PI / 2));
                    // std::cout<<tar<<std::endl;
                    if (i > 1200)
                    {
                        tar = 0;
                    }
                    api.set_pd_control(j, tar, 7.00);
                }
                usleep(10000);
            }
    std::vector<float> _pos{0, 0, 0, 0, 0, 0};
    api.set_pos(_pos);
    sleep(1);
}

/**
 * @brief 执行定义的移动
 *
 * 根据用户输入的id，调用Handapi对象执行相应的移动操作。
 *
 * @param api Handapi引用对象，用于控制移动
 */
void do_defined_move(Handapi &api)
{
    std::vector<float> defined_pos;
    std::vector<float> _back1{-20, -20, -20, -20, -20, -20};
    std::vector<float> defined_pos1{2.8, 3.9, 4.2, 4.6, 8.0, 6.6}, defined_pos2{9, 9, 9, 9, 9, 4}, defined_pos3{2, 2, 2, 2, 5, 0};

    std::vector<float> _stop{0, 0, 0, 0, 0, 0};

    int action_id;

    while (1)
    {
        std::cout << "input id from 1-3(move) or 4(quit) :  ";
        std::cin >> action_id;

        api.calibration();
        usleep(10000);

        if (action_id < 1 || action_id > 4)
        {
            std::cout << "action id error" << std::endl;
            continue;;
        }
        else if(action_id == 1){
            defined_pos = defined_pos1;
        }
        else if(action_id == 2){
            defined_pos = defined_pos2;
        }
        else if(action_id == 3){
            defined_pos = defined_pos3;
        }
        else if(action_id == 4){
            break;
        }    
        api.set_pos(defined_pos);
        usleep(2000000);
        api.set_pos(_back1);
        usleep(2000000);
        api.set_pwm(_stop);
        usleep(10000);    
    }
    return;
}


void do_defined_pwm(Handapi &api){
    std::vector<float> _back{-200, -200, -200, -200, -200, -200}, _forward{200, 200, 200, 200, 200, 200}, _stop{0, 0, 0, 0, 0, 0};

    api.set_pwm(_forward);
    usleep(2000000);
    api.set_pwm(_back);
    usleep(2000000);
    api.set_pwm(_stop);
    usleep(10000);   

}


int main()
{
    Handapi api;
    api.init(LEFT_IP); // RIGHT_IP

    reset_calibrate(api);

    sin_move(api);

    do_defined_move(api);

    do_defined_pwm(api);
    
}