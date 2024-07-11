#include "../include/Handapi.h"

using namespace HandProtocol;

int main()
{
    Handapi api;
    api.init(LEFT_IP);
    api.calibration();
    
    // set
    vector <float> _pwm {200.0, 200.0, 200.0, 200.0, 200.0, 200.0};
    if (api.set_pwm(_pwm) == ResultCode::FAIL)
    {
        Logger::get_instance()->print_trace_error("set pwm failed\n");
    }
    OS::get_instance()->delay_s(1);
    Logger::get_instance()->print_trace("set pwm success");
    std::cout<<std::endl;

    // verify
    vector<float> pos = api.get_pos();
    if (pos.size() != 6)
    {
        Logger::get_instance()->print_trace_error("get pos failed\n");
        return ResultCode::FAIL;
    }
    
    std::cout<<"get pos success : ";
    for (int i = 0; i < pos.size(); ++i) {
        std::cout << pos[i] << " ";
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