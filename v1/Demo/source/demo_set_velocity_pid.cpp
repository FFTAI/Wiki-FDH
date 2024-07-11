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
    if (api.set_velocity_pid(id, _pid) == ResultCode::FAIL)
    {
        Logger::get_instance()->print_trace_error("set_velocity_pid failed\n");
    }
    OS::get_instance()->delay_s(1);
    Logger::get_instance()->print_trace("set_velocity_pid success");
    std::cout<<std::endl;

    // verify
    vector<float> velocity_pid = api.get_velocity_pid();
    if (velocity_pid.size() != 18)
    {
        Logger::get_instance()->print_trace_error("get velocity_pid failed\n");
        return ResultCode::FAIL;
    }
    
    std::cout<<"get velocity_pid success : ";
    for (int i = 0; i < velocity_pid.size(); ++i) {
        std::cout << velocity_pid[i] << " ";
    }
    std::cout << std::endl;
    return 0;

}