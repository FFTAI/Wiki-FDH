#include <iostream>
#include "dh.h"

using namespace DH;
using namespace Predefine;
using namespace Utils;

int main()
{
    if (set_pid(LEFT_HAND, CURRENT, INDEX_F, 3, 0, 0) == FunctionResult::FAILURE)// DEFAULT 3 0 0
    {
        Logger::get_instance()->print_trace_error("set pid failed\n");
    }
    OS::get_instance()->delay_s(1);
    get_pid(LEFT_HAND, CURRENT, INDEX_F);
    return 0;
}