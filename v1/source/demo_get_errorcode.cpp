#include <iostream>
#include "dh.h"

using namespace DH;
using namespace Predefine;
using namespace Utils;

int main()
{
    Logger::get_instance()->print_trace("error code: %d\n", get_errorcode(LEFT_HAND, INDEX_F));
    return 0;
}