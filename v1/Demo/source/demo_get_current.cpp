#include "../include/Handapi.h"

using namespace HandProtocol;

int main()
{
    Handapi api;
    api.init(LEFT_IP);
    vector<float> current = api.get_current();

    if (current.size() != 6)
    {
        Logger::get_instance()->print_trace_error("get current failed\n");
        return ResultCode::FAIL;
    }
    
    std::cout<<"get get_current success : ";
    for (int i = 0; i < current.size(); ++i) {
        std::cout << current[i] << " ";
    }
    std::cout << std::endl;


    return 0;
}