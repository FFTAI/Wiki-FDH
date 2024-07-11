#include "../include/Handapi.h"

using namespace HandProtocol;

int main()
{
    Handapi api;
    api.init(LEFT_IP);
    api.calibration();

    // set
    vector <float> angle {2.0, 2.0, 2.0, 2.0, 2.0, 2.0};
    if (api.set_pos(angle) == ResultCode::FAIL)
    {
        Logger::get_instance()->print_trace_error("set_position failed\n");
    }
    OS::get_instance()->delay_s(1);
    Logger::get_instance()->print_trace("set_position success");
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