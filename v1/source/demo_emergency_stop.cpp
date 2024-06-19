#include <iostream>
#include "dh.h"

using namespace DH;
using namespace Predefine;
using namespace Utils;


int main()
{
    if (emergency_stop(LEFT_HAND) == FunctionResult::FAILURE)
    {
        Logger::get_instance()->print_trace_error("emergency stop failed\n");
        return FunctionResult::FAILURE;
    }
    return 0;
}