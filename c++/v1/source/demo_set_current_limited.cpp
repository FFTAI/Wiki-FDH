#include <iostream>
#include "dh.h"

using namespace DH;
using namespace Predefine;
using namespace Utils;

int main()
{
    if (set_finger_limited(RIGHT_HAND, CURRENT, FORE_F, 1000) == FunctionResult::FAILURE)
    {
        Logger::get_instance()->print_trace_error("set limit failed\n");
    }
    return 0;
}