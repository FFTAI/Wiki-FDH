#include <iostream>
#include "dh.h"

using namespace DH;
using namespace Predefine;
using namespace Utils;

int main()
{
    Logger::get_instance()->print_trace("angle: %f\n", get_angle_limited(RIGHT_HAND, FORE_F));
    return 0;
}