#include "../../upbody/ArmControl/include/global_variable.h"

#include "left_hand.hpp"
#include "right_hand.hpp"

using namespace left_hand_api;
using namespace right_hand_api;

using namespace std;

right_hand right_hand_01;
left_hand left_hand_01;



void hand_key_do() {
    int previous_hand_mode = -1;     
    int *hand_mode_ptr = &hand_mode; 
    std::cout << "key_do" << endl;
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        if (*hand_mode_ptr != previous_hand_mode) {
            std::cout << "key_do!" << endl;
            left_hand_01.key_do(*hand_mode_ptr);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            right_hand_01.key_do(*hand_mode_ptr);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            previous_hand_mode = *hand_mode_ptr; 
        }
    }
}

void left_hand_key_do() {
    int previous_hand_mode = -1;               
    int *left_hand_mode_ptr = &right_hand_mode; 
    std::cout << "key_do" << endl;
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        if (*left_hand_mode_ptr != previous_hand_mode) {
            std::cout << "key_do!" << endl;
            left_hand_01.key_do(*left_hand_mode_ptr);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            previous_hand_mode = *left_hand_mode_ptr; 
        }
    }
}

void right_hand_key_do() {
    int previous_hand_mode = -1;              
    int *right_hand_mode_ptr = &left_hand_mode; 
    std::cout << "key_do" << endl;
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        if (*right_hand_mode_ptr != previous_hand_mode) {
            std::cout << "key_do!" << endl;
            right_hand_01.key_do(*right_hand_mode_ptr);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            previous_hand_mode = *right_hand_mode_ptr; 
        }
    }
}

void handcontrol_init() {
    std::cout << "handcontrol_init" << std::endl;
    left_hand_01.left_hand_init();
    right_hand_01.right_hand_init();
    left_hand_01.Speed_Set(1, 1000, 1000, 1000, 1000, 1000, 1000);
    right_hand_01.Speed_Set(1, 1000, 1000, 1000, 1000, 1000, 1000);

    std::thread rec_f_key_thread(hand_key_do);
    rec_f_key_thread.detach();
}

void handcontrol_init_v2() {
    std::cout << "handcontrol_init" << std::endl;
    left_hand_01.left_hand_init();
    right_hand_01.right_hand_init();
    left_hand_01.Speed_Set(1, 1000, 1000, 1000, 1000, 1000, 1000);
    right_hand_01.Speed_Set(1, 1000, 1000, 1000, 1000, 1000, 1000);

    std::thread rec_f_key_thread_left(left_hand_key_do);
    std::thread rec_f_key_thread_right(right_hand_key_do);
    rec_f_key_thread_left.detach();
    rec_f_key_thread_right.detach();
}
