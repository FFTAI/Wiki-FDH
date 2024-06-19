#include <iostream>
#include "dh.h"

using namespace DH;
using namespace Predefine;
using namespace Utils;

int main()
{
    if (set_target(LEFT_HAND, CURRENT, INDEX_F, 0) == FunctionResult::FAILURE)
    {
        Logger::get_instance()->print_trace_error("set target failed\n");
    }
    OS::get_instance()->delay_s(1);
    Logger::get_instance()->print_trace("current: %f\n", get_current(LEFT_HAND, INDEX_F));
    return 0;
}