#include "../include/Handapi.h"

using namespace HandProtocol;

int main()
{
    Handapi api;
    api.init(LEFT_IP);
    api.calibration();
    usleep(1000000);

    vector<float> velocity_limited = api.get_velocity_limited();
    if (velocity_limited.size() != 6)
    {
        Logger::get_instance()->print_trace_error("get velocity_limited failed\n");
        return ResultCode::FAIL;
    }
    
    std::cout<<"get velocity_limited success : ";
    for (int i = 0; i < velocity_limited.size(); ++i) {
        std::cout << velocity_limited[i] << " ";
    }
    std::cout << std::endl;


    return 0;
}