#include "../include/Handapi.h"

using namespace HandProtocol;

int main()
{
    Handapi api;
    api.init(LEFT_IP);
    api.calibration();
    usleep(1000000);


    vector<float> pos = api.get_pos();

    if (pos.size() != 6)
    {
        Logger::get_instance()->print_trace_error("get position failed\n");
        return ResultCode::FAIL;
    }
    
    std::cout<<"get position success : ";
    for (int i = 0; i < pos.size(); ++i) {
        std::cout << pos[i] << " ";
    }
    std::cout << std::endl;


    return 0;
}