#include <iostream>
#include "dh.h"

using namespace DH;
using namespace Predefine;
using namespace Utils;

int main()
{
    Logger::get_instance()->print_trace("status: %d\n", get_status(RIGHT_HAND, FORE_F));
    return 0;
}