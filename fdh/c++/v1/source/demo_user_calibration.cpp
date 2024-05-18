#include <iostream>
#include "dh.h"

using namespace DH;
using namespace Predefine;
using namespace Utils;


int main()
{
    if (calibration(RIGHT_HAND) == FunctionResult::FAILURE)
    {
        Logger::get_instance()->print_trace_error("calibration failed\n");
        return FunctionResult::FAILURE;
    }
    return 0;
}