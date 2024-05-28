#include "left_hand.hpp"
#include "right_hand.hpp"
#include <unistd.h>
#include <iostream>

using namespace left_hand_api;
using namespace right_hand_api;
using namespace std;

int main(){
    right_hand right_hand_01;
    left_hand left_hand_01;

    left_hand_01.left_hand_init();
    right_hand_01.right_hand_init();

    left_hand_01.Speed_Set(1,1000,1000,1000,1000,1000,1000);
    right_hand_01.Speed_Set(1,1000,1000,1000,1000,1000,1000);

    left_hand_01.Force_Set(1,500,500,500,500,500,500);
    right_hand_01.Force_Set(1,500,500,500,500,500,500);

    int key_number;
    while (true)
    {
        std::cout << "输入：" ;
        std::cin >>key_number;
        std::cout<<endl;
        if (key_number == 999)
        {
            uint16_t val = 999;
            uint16_t val_1 = 999;
            uint16_t val_force = 999;
            uint8_t id = 1;
            double time_sleep = 3;
            while (key_number--)
            {
                left_hand_01.Angle_Set(id, val, val, val, val, val, val_1, time_sleep, val_force);
                right_hand_01.Angle_Set(id, val, val, val, val, val, val_1, time_sleep, val_force);
                val--;
                // usleep(7000);
            }
            
        }
        
        left_hand_01.key_do(key_number);
        right_hand_01.key_do(key_number);

    }
    return 0;
}