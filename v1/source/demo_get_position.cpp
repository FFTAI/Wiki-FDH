#include <iostream>
#include "dh.h"

using namespace DH;
using namespace Predefine;
using namespace Utils;

int main()
{
    Logger::get_instance()->print_trace("position: %f\n", get_position(LEFT_HAND, PINKY_F));
    return 0;
}