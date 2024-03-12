#include <iostream>
#include "dh.h"

using namespace DH;
using namespace Predefine;
using namespace Utils;

int main()
{
    Logger::get_instance()->print_trace("p: %f\n", get_p(RIGHT_HAND, FORE_F));
    Logger::get_instance()->print_trace("i: %f\n", get_i(RIGHT_HAND, FORE_F));
    Logger::get_instance()->print_trace("d: %f\n", get_d(RIGHT_HAND, FORE_F));
    return 0;
}