#include <iostream>
#include "dh.h"

using namespace DH;
using namespace Predefine;
using namespace Utils;

int main()
{
    Logger::get_instance()->print_trace("version: %s\n", get_version(LEFT_HAND).c_str());
    return 0;
}