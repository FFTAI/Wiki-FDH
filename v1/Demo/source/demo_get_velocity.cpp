#include "../include/Handapi.h"

using namespace HandProtocol;

int main()
{
    Handapi api;
    api.init(LEFT_IP);
    api.calibration();
    usleep(1000000);

    vector<float> velocity = api.get_velocity();

    if (velocity.size() != 6)
    {
        Logger::get_instance()->print_trace_error("get velocity failed\n");
        return ResultCode::FAIL;
    }
    
    std::cout<<"get velocity success : ";
    for (int i = 0; i < velocity.size(); ++i) {
        std::cout << velocity[i] << " ";
    }
    std::cout << std::endl;


    return 0;
}