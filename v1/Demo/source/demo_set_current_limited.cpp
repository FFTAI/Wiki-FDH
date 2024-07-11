#include "../include/Handapi.h"

using namespace HandProtocol;

int main()
{
    Handapi api;
    api.init(LEFT_IP);
    api.calibration();
      
    // set
    uint8_t id = 1;
    float current = 200.0;
    if (api.set_current_limited(id, current) == ResultCode::FAIL)
    {
        Logger::get_instance()->print_trace_error("set set_current_limited failed\n");
    }
    OS::get_instance()->delay_s(1);

    // verify
    vector<float> current_limited = api.get_current_limited();
    if (current_limited.size() != 6)
    {
        Logger::get_instance()->print_trace_error("get current_limited failed\n");
        return ResultCode::FAIL;
    }
    
    std::cout<<"get current_limited success : ";
    for (int i = 0; i < current_limited.size(); ++i) {
        std::cout << current_limited[i] << " ";
    }
    std::cout << std::endl;
    return 0;

}