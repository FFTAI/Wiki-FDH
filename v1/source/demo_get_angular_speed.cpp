#include <iostream>
#include "dh.h"

using namespace DH;
using namespace Predefine;
using namespace Utils;

int main()
{
    Logger::get_instance()->print_trace("angular speed: %f\n", get_omega(LEFT_HAND, THUMB_A));
    return 0;
}