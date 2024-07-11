#include "../include/Handapi.h"

using namespace HandProtocol;

int main()
{
    Handapi api;
    api.init(LEFT_IP);
    vector<long> errorcode = api.get_errorcode();

    if (errorcode.size() != 6)
    {
        Logger::get_instance()->print_trace_error("get errorcode failed\n");
        return ResultCode::FAIL;
    }
    
    std::cout<<"get errorcode success : ";
    for (int i = 0; i < errorcode.size(); ++i) {
        std::cout << errorcode[i] << " ";
    }
    std::cout << std::endl;


    return 0;
}