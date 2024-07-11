#include "../include/Handapi.h"

using namespace HandProtocol;

int main()
{
    Handapi api;
    api.init(LEFT_IP);
    std::string _ip = api.get_ip();

    if (_ip == "")
    {
        Logger::get_instance()->print_trace_error("get ip failed\n");
        return ResultCode::FAIL;
    }

    Logger::get_instance()->print_trace("get ip success: %s\n", _ip.c_str());

    
    return 0;
}