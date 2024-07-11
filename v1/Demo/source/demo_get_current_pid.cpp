#include "../include/Handapi.h"

using namespace HandProtocol;

int main()
{
    Handapi api;
    api.init(LEFT_IP);
    vector<float> current_pid = api.get_current_pid();
    if (current_pid.size() != 18)
    {
        Logger::get_instance()->print_trace_error("get current_pid failed\n");
        return ResultCode::FAIL;
    }
    
    std::cout<<"get current_pid success : ";
    for (int i = 0; i < current_pid.size(); ++i) {
        std::cout << current_pid[i] << " ";
    }
    std::cout << std::endl;


    return 0;
}