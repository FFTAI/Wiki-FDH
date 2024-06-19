#include <iostream>
#include "dh.h"

using namespace DH;
using namespace Predefine;
using namespace Utils;

int main()
{
    if (set_limit(LEFT_HAND, POSITION, INDEX_F, 10) == FunctionResult::FAILURE)
    {
        Logger::get_instance()->print_trace_error("set limit failed\n");
    }
    OS::get_instance()->delay_s(1);
    get_limit(LEFT_HAND, POSITION, INDEX_F);
    return 0;
}