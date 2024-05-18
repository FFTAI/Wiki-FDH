#include <iostream>
#include "dh.h"

using namespace DH;
using namespace Predefine;
using namespace Utils;

int main()
{
    Logger::get_instance()->print_trace("control type: %d\n", get_control_type(RIGHT_HAND, FORE_F));
    return 0;
}