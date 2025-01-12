#include "../include/Handapi.h"

using namespace HandProtocol;

int main()
{
    Handapi api;
    api.init(LEFT_IP);
    api.calibration();
    usleep(1000000);

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