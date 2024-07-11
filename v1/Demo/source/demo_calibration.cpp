#include "../include/Handapi.h"

using namespace HandProtocol;

int main()
{
    Handapi api;
    api.init(LEFT_IP);

    if (api.calibration() == ResultCode::FAIL)
    {
        Logger::get_instance()->print_trace_error("calibration failed\n");
        return ResultCode::FAIL;
    }

    Logger::get_instance()->print_trace("calibration success\n");

    
    return 0;
}