#include <iostream>
#include "dh.h"

using namespace DH;
using namespace Predefine;
using namespace Utils;

int main()
{
    Logger::get_instance()->print_trace("current: %f\n", get_current(LEFT_HAND, INDEX_F));
    return 0;
}