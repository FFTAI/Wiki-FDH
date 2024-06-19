#include <iostream>
#include "dh.h"

using namespace DH;
using namespace Predefine;
using namespace Utils;

int main()
{
    Logger::get_instance()->print_trace("ip: %s\n", get_ip(LEFT_HAND).c_str());
    return 0;
}