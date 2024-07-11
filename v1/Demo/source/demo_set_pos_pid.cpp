#include "../include/Handapi.h"

using namespace HandProtocol;

int main()
{
    Handapi api;
    api.init(LEFT_IP);
    api.calibration();
        
    // set
    uint8_t id = 1;
    vector<float> _pid {4.0, 2.0, 0.0};
    if (api.set_pos_pid(id, _pid) == ResultCode::FAIL)
    {
        Logger::get_instance()->print_trace_error("set_pos_pid failed\n");
    }
    OS::get_instance()->delay_s(1);
    Logger::get_instance()->print_trace("set_pos_pid success");
    std::cout<<std::endl;

    // verify
    vector<float> pos_pid = api.get_pos_pid();
    if (pos_pid.size() != 18)
    {
        Logger::get_instance()->print_trace_error("get pos_pid failed\n");
        return ResultCode::FAIL;
    }
    
    std::cout<<"get pos_pid success : ";
    for (int i = 0; i < pos_pid.size(); ++i) {
        std::cout << pos_pid[i] << " ";
    }
    std::cout << std::endl;

    // reset position
    std::vector<float> _back{-200, -200, -200, -200, -200, -200}, _forward{200, 200, 200, 200, 200, 200}, _stop{0, 0, 0, 0, 0, 0};
    api.set_pwm(_back);
    usleep(2000000);
    api.set_pwm(_stop);
    usleep(10000); 
    return 0;

}