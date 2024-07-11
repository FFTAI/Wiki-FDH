#include "../include/Handapi.h"

using namespace HandProtocol;

int main()
{
    Handapi api;
    api.init(LEFT_IP);
    api.calibration();
    usleep(1000000);

    vector<float> pos_pid = api.get_pos_pid();
    if (pos_pid.size() != 18)
    {
        Logger::get_instance()->print_trace_error("get pos_pid failed\n");
        return ResultCode::FAIL;
    }
    
    std::cout<<"get pos_pid success : ";
    for (int i = 0; i < pos_pid.size(); ++i) {
        std::cout << pos_pid[i] << " ";
    }
    std::cout << std::endl;


    return 0;
}