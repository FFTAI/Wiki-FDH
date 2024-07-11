#include "../include/Handapi.h"

using namespace HandProtocol;

int main()
{
    Handapi api;
    api.init(LEFT_IP);
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