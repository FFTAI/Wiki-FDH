#include "../include/Handapi.h"

using namespace HandProtocol;

int main()
{
    Handapi api;
    api.init(LEFT_IP);
    api.calibration();
    usleep(1000000); 
 
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