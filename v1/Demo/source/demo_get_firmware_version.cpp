#include "../include/Handapi.h"

using namespace HandProtocol;

int main()
{
    Handapi api;
    api.init(LEFT_IP);
    std::string version = api.get_firmware_version();

    if (version == "")
    {
        Logger::get_instance()->print_trace_error("get version failed\n");
        return ResultCode::FAIL;
    }

    Logger::get_instance()->print_trace("get version success: %s\n", version.c_str());

    
    return 0;
}