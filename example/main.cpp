#include "left_hand.hpp"
#include "right_hand.hpp"
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
        left_hand_01.key_do(key_number);
        right_hand_01.key_do(key_number);

    }
    return 0;
}