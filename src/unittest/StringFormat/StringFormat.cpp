
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>

#include "TiActor/utils/StringUtils.h"

using namespace TiActor;

int main(int argn, char * argv[])
{
    std::cout << "Function StringFormat() Test..." << std::endl << std::endl;

    int a, b, c;
    a = 1;
    b = 2;
    c = 3;
    const char * text = StringUtils::format(128, "a = %d, b = %d, c = %d.\n", a, b, c);
    std::cout << text << std::endl;

    text = StringUtils::format(128, "c = %d, b = %d, a = %d.\n", c, b, a);
    std::cout << text << std::endl;

    ::system("pause");
    return 0;
}
