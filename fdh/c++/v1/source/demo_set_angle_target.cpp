#include <iostream>
#include "dh.h"

using namespace DH;
using namespace Predefine;
using namespace Utils;

int main()
{
    if (set_target(RIGHT_HAND, POSITION, LITTLE_F, 800) == FunctionResult::FAILURE)
    {
        Logger::get_instance()->print_trace_error("set target failed\n");
    }
    return 0;
}