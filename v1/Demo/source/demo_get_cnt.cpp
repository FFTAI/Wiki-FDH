#include "../include/Handapi.h"

using namespace HandProtocol;

int main()
{
    Handapi api;
    api.init(LEFT_IP);
    vector<long> cnt = api.get_cnt();

    if (cnt.size() != 6)
    {
        Logger::get_instance()->print_trace_error("get count failed\n");
        return ResultCode::FAIL;
    }

    Logger::get_instance()->print_trace("get count success\n");
    
    
    return 0;
}