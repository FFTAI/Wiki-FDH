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
    if (api.set_current_pid(id, _pid) == ResultCode::FAIL)
    {
        Logger::get_instance()->print_trace_error("set set_current_pid failed\n");
    }
    OS::get_instance()->delay_s(1);

    // verify
    vector<float> current_pid = api.get_current_pid();
    if (current_pid.size() != 18)
    {
        Logger::get_instance()->print_trace_error("get current_pid failed\n");
        return ResultCode::FAIL;
    }
    
    std::cout<<"get current_pid success : ";
    for (int i = 0; i < current_pid.size(); ++i) {
        std::cout << current_pid[i] << " ";
    }
    std::cout << std::endl;

    return 0;

}