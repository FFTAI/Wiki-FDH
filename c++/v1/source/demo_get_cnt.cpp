#include <iostream>
#include "dh.h"

using namespace DH;
using namespace Predefine;
using namespace Utils;

int main()
{
    Logger::get_instance()->print_trace("cnt: %lld\n", get_cnt(RIGHT_HAND, THUMB_A));
    return 0;
}