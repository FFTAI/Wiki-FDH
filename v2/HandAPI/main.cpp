#include "include/Handapi.h"
#include "../HandSocket/include/HandSocket.h"
#include "include/HandapiFunctionResult.h"

using namespace HandProtocol;

int main()
{
    Handapi api;
    api.init("192.168.137.39");

    std::string version_ = "", ip = "";
    // if (api.get_firmware_version(version_) != APIResultCode::SUCCESS)
    // {
    //     std::cerr << "GET POSITION FAILED" << std::endl;
    //     return 0;
    // }
    // std::cout << "software version: " << version_ << std::endl;

    // if (api.get_ip(ip) != APIResultCode::SUCCESS)
    // {
    //     std::cerr << "GET POSITION FAILED" << std::endl;
    //     return 0;
    // }
    // std::cout << "ip: " << ip << std::endl;

    // if (api.calibration() != APIResultCode::SUCCESS)
    // {
    //     std::cerr << "CALIBRATION FAILED" << std::endl;
    //     return 0;
    // }
    // for (int i = 1; i < 7; i++)
    // {
    //     if (api.set_current(i, -100) != APIResultCode::SUCCESS)
    //     {
    //         std::cerr << "SET CURRENT FAILED" << std::endl;
    //     }
    // }
    // sleep(2);

    // for (int i = 1; i < 7; i++)
    // {
    //     if (api.set_current(i, 0) != APIResultCode::SUCCESS)
    //     {
    //         std::cerr << "SET CURRENT FAILED" << std::endl;
    //     }
    // }
    // sleep(1);
    // if (api.calibration() != APIResultCode::SUCCESS)
    // {
    //     std::cerr << "CALIBRATION FAILED" << std::endl;
    //     return 0;
    // }
    // sleep(1);

    // std::vector<long> cur_cnt;
    // if (api.get_cnt(cur_cnt) != APIResultCode::SUCCESS)
    // {
    //     std::cerr << "GET POSITION FAILED" << std::endl;
    //     return 0;
    // }
    // std::cout << "cur_cnt: ";
    // for (float ele : cur_cnt)
    // {
    //     std::cout << ele << " ";
    // }
    // std::cout << std::endl;
    // std::vector<float> cur_pos;
    // if (api.get_pos(cur_pos) != APIResultCode::SUCCESS)
    // {
    //     std::cerr << "GET POSITION FAILED" << std::endl;
    //     return 0;
    // }
    // std::cout << "cur_pos: ";
    // for (float ele : cur_pos)
    // {
    //     std::cout << ele << " ";
    // }
    // std::cout << std::endl;

    // std::vector<float> cur_cur;
    // if (api.get_current(cur_cur) != APIResultCode::SUCCESS)
    // {
    //     std::cerr << "GET POSITION FAILED" << std::endl;
    //     return 0;
    // }
    // std::cout << "cur_cur: ";
    // for (float ele : cur_cur)
    // {
    //     std::cout << ele << " ";
    // }
    // std::cout << std::endl;

    // std::vector<float> cur_vel;
    // if (api.get_velocity(cur_vel) != APIResultCode::SUCCESS)
    // {
    //     std::cerr << "GET POSITION FAILED" << std::endl;
    //     return 0;
    // }
    // std::cout << "cur_vel: ";
    // for (float ele : cur_vel)
    // {
    //     std::cout << ele << " ";
    // }
    // std::cout << std::endl;

    // std::vector<uint8_t> cur_status;
    // if (api.get_status(cur_status) != APIResultCode::SUCCESS)
    // {
    //     std::cerr << "GET POSITION FAILED" << std::endl;
    //     return 0;
    // }
    // std::cout << "cur_status: ";
    // for (float ele : cur_status)
    // {
    //     std::cout << ele << " ";
    // }
    // std::cout << std::endl;

    // std::vector<long> cur_errorcode;
    // if (api.get_errorcode(cur_errorcode) != APIResultCode::SUCCESS)
    // {
    //     std::cerr << "GET POSITION FAILED" << std::endl;
    //     return 0;
    // }
    // std::cout << "cur_errorcode: ";
    // for (float ele : cur_errorcode)
    // {
    //     std::cout << ele << " ";
    // }
    // std::cout << std::endl;

    // std::vector<float> cur_pos_limit;
    // if (api.get_pos_limited(cur_pos_limit) != APIResultCode::SUCCESS)
    // {
    //     std::cerr << "GET POSITION FAILED" << std::endl;
    //     return 0;
    // }
    // std::cout << "cur_pos_limit: ";
    // for (float ele : cur_pos_limit)
    // {
    //     std::cout << ele << " ";
    // }
    // std::cout << std::endl;

    // std::vector<float> cur_vel_limit;
    // if (api.get_velocity_limited(cur_vel_limit) != APIResultCode::SUCCESS)
    // {
    //     std::cerr << "GET POSITION FAILED" << std::endl;
    //     return 0;
    // }
    // std::cout << "cur_vel_limit: ";
    // for (float ele : cur_vel_limit)
    // {
    //     std::cout << ele << " ";
    // }
    // std::cout << std::endl;

    // std::vector<float> cur_cur_limit;
    // if (api.get_current_limited(cur_cur_limit) != APIResultCode::SUCCESS)
    // {
    //     std::cerr << "GET POSITION FAILED" << std::endl;
    //     return 0;
    // }
    // std::cout << "cur_cur_limit: ";
    // for (float ele : cur_cur_limit)
    // {
    //     std::cout << ele << " ";
    // }
    // std::cout << std::endl;

    // std::vector<float> cur_vel_pid;
    // if (api.get_velocity_pid(cur_vel_pid) != APIResultCode::SUCCESS)
    // {
    //     std::cerr << "GET POSITION FAILED" << std::endl;
    //     return 0;
    // }
    // std::cout << "cur_vel_pid: ";
    // for (float ele : cur_vel_pid)
    // {
    //     std::cout << ele << " ";
    // }
    // std::cout << std::endl;

    // std::vector<float> cur_cur_pid;
    // if (api.get_current_pid(cur_cur_pid) != APIResultCode::SUCCESS)
    // {
    //     std::cerr << "GET POSITION FAILED" << std::endl;
    //     return 0;
    // }
    // std::cout << "cur_cur_pid: ";
    // for (float ele : cur_cur_pid)
    // {
    //     std::cout << ele << " ";
    // }
    // std::cout << std::endl;

    // if (api.get_firmware_version(version_) != APIResultCode::SUCCESS)
    // {
    //     std::cerr << "GET POSITION FAILED" << std::endl;
    //     return 0;
    // }
    // std::cout << "software version: " << version_ << std::endl;

    // if (api.get_ip(ip) != APIResultCode::SUCCESS)
    // {
    //     std::cerr << "GET POSITION FAILED" << std::endl;
    //     return 0;
    // }
    // std::cout << "ip: " << ip << std::endl;

    /***********pos************/

    // set
    float set_position = 80;
    std::vector<float> _forward, _back;
    for (int i = 0; i < 6; i++)
    {
        _forward.push_back(set_position);
        _back.push_back(-set_position);
    }
    
    while (1)
    {
        api.set_pwm(_forward);
        usleep(500000);
        api.set_pwm(_back);
        usleep(500000);
    }

    // std::cout << std::endl;
    // std::vector<float> cur_pos;
    // if (api.get_pos(cur_pos) != APIResultCode::SUCCESS)
    // {
    //     std::cerr << "GET POSITION FAILED" << std::endl;
    //     return 0;
    // }
    // std::cout << "cur_pos: ";
    // for (float ele : cur_pos)
    // {
    //     std::cout << ele << " ";
    // }
    // std::cout << std::endl;

    // std::vector<float> _pid;
    // _pid.push_back(199);
    // _pid.push_back(11);
    // _pid.push_back(0.2);
    // for (int i = 1; i < 7; i++)
    // {
    //     if (api.set_pos_pid(i, _pid) != APIResultCode::SUCCESS)
    //     {
    //         std::cerr << "SET POSITION FAILED" << std::endl;
    //     }
    //     sleep(1);
    // }

    // std::vector<float> cur_pos_pid;
    // if (api.get_pos_pid(cur_pos_pid) != APIResultCode::SUCCESS)
    // {
    //     std::cerr << "GET POSITION FAILED" << std::endl;
    //     return 0;
    // }
    // std::cout << "cur_pos_pid: ";
    // for (float ele : cur_pos_pid)
    // {
    //     std::cout << ele << " ";
    // }
    // std::cout << std::endl;

    // for (int i = 1; i < 7; i++)
    // {
    //     if (api.set_pos_limited(i, 1.1, 9.1) != APIResultCode::SUCCESS)
    //     {
    //         std::cerr << "SET POSITION FAILED" << std::endl;
    //     }
    // }

    // int read_counts = 5;
    // while (read_counts--)
    // {
    //     std::vector<float> cur_pos_limit;
    //     if (api.get_pos_limited(cur_pos_limit) != APIResultCode::SUCCESS)
    //     {
    //         std::cerr << "GET POSITION FAILED" << std::endl;
    //         return 0;
    //     }
    //     std::cout << "cur_pos_limit: ";
    //     for (float ele : cur_pos_limit)
    //     {
    //         std::cout << ele << " ";
    //     }
    //     std::cout << std::endl;
    // }

    /***********current************/
    // if (api.set_current(1, -0) != APIResultCode::SUCCESS)
    // {
    //     std::cerr << "SET CURRENT FAILED" << std::endl;
    // }

    // std::vector<float> s_pwm, e_pwm;
    // for (int i = 0; i < 6; i++)
    // {
    //     s_pwm.push_back(100.0);
    //     e_pwm.push_back(0.0);
    // }
    // api.set_pwm(s_pwm);

    // sleep(1);
    // api.set_pwm(e_pwm);
    
}