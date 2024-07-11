#include "../include/Handapi.h"

using namespace HandProtocol;

int main()
{
    Handapi api;
    api.init(LEFT_IP);
    api.calibration();
    usleep(1000000);

    vector<uint8_t> status = api.get_status();
    if (status.size() != 6)
    {
        Logger::get_instance()->print_trace_error("get status failed\n");
        return ResultCode::FAIL;
    }
    
    std::cout<<"get status success : ";
    for (int i = 0; i < status.size(); ++i) {
        std::cout << status[i] << " ";
    }
    std::cout << std::endl;


    return 0;
}