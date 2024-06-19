#include <iostream>
#include "dh.h"

using namespace DH;
using namespace Predefine;
using namespace Utils;

int main()
{
    if (set_pid(LEFT_HAND, OMEGA, INDEX_F, 5, 0, 0) == FunctionResult::FAILURE) //DEFAULT 5 0 0
    {
        Logger::get_instance()->print_trace_error("set pid failed\n");
    }
    OS::get_instance()->delay_s(1);
    get_pid(LEFT_HAND, OMEGA, INDEX_F);
    return 0;
}