#include <iostream>
#include "dh.h"

using namespace DH;
using namespace Predefine;
using namespace Utils;

int main()
{
    if (set_target(RIGHT_HAND, CURRENT, FORE_F, 0) == FunctionResult::FAILURE)
    {
        Logger::get_instance()->print_trace_error("set target failed\n");
    }
    return 0;
}