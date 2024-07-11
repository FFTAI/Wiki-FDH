#include "../include/Handapi.h"

using namespace HandProtocol;

int main()
{
    Handapi api;
    api.init(LEFT_IP);
    api.calibration();
        
    // set
    uint8_t id = 1;
    float start_angel = 2.0;
    float end_angle = 10.0;
    if (api.set_pos_limited(id, start_angel, end_angle) == ResultCode::FAIL)
    {
        Logger::get_instance()->print_trace_error("set_pos_limited failed\n");
    }
    OS::get_instance()->delay_s(1);
    Logger::get_instance()->print_trace("set_pos_limited success");
    std::cout<<std::endl;

    // verify
    vector<float> pos_limited = api.get_pos_limited();
    if (pos_limited.size() != 12)
    {
        Logger::get_instance()->print_trace_error("get pos_limited failed\n");
        return ResultCode::FAIL;
    }
    
    std::cout<<"get pos_limited success : ";
    for (int i = 0; i < pos_limited.size(); ++i) {
        std::cout << pos_limited[i] << " ";
    }
    std::cout << std::endl;

    return 0;

}