#include <iostream>
#include "dh.h"

using namespace DH;
using namespace Predefine;
using namespace Utils;

int main()
{
    if (set_pid(RIGHT_HAND, POSITION, FORE_F, 0, 0, 0) == FunctionResult::FAILURE)
    {
        Logger::get_instance()->print_trace_error("set pid failed\n");
    }
    return 0;
}