#include "../include/Handapi.h"

using namespace HandProtocol;

int main()
{
    Handapi api;
    api.init(LEFT_IP);
    api.calibration();


    // set
    uint8_t id = 1;
    float cur = 200.0;
    if (api.set_current(id, cur) == ResultCode::FAIL)
    {
        Logger::get_instance()->print_trace_error("set current failed\n");
    }
    OS::get_instance()->delay_s(1);
    Logger::get_instance()->print_trace("set current success");
    std::cout<<std::endl;

    // verify
    vector<float> current = api.get_current();
    if (current.size() != 6)
    {
        Logger::get_instance()->print_trace_error("get current failed\n");
        return ResultCode::FAIL;
    }
    
    std::cout<<"get current success : ";
    for (int i = 0; i < current.size(); ++i) {
        std::cout << current[i] << " ";
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