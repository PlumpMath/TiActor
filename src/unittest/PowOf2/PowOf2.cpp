

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>

#include "TiActor/utils/PowOf2.h"

int main(int argn, char * argv[])
{
    std::cout << "Template round_up_to_pow2<N> Test..." << std::endl << std::endl;

    int isPow2 = TiActor::math::is_pow_of_2<121>::value;
    std::cout << "isPow2(121) = " << isPow2 << std::endl;

    isPow2 = TiActor::math::is_pow_of_2<128>::value;
    std::cout << "isPow2(128) = " << isPow2 << std::endl;

    std::cout << std::endl;

    {
        size_t pow2_a = TiActor::math::round_up_to_pow2<33>::value;
        std::cout << "pow2(33) = " << pow2_a << std::endl;

        size_t pow2_b = TiActor::math::round_up_to_pow2<213>::value;
        std::cout << "pow2(213) = " << pow2_b << std::endl;

        size_t pow2_c = TiActor::math::round_up_to_pow2<256>::value;
        std::cout << "pow2(256) = " << pow2_c << std::endl;
    }

    std::cout << std::endl;

    {
        size_t pow2_a = TiActor::math::round_down_to_pow2<33>::value;
        std::cout << "pow2(33) = " << pow2_a << std::endl;

        size_t pow2_b = TiActor::math::round_down_to_pow2<213>::value;
        std::cout << "pow2(213) = " << pow2_b << std::endl;

        size_t pow2_c = TiActor::math::round_down_to_pow2<256>::value;
        std::cout << "pow2(256) = " << pow2_c << std::endl;
    }

    std::cout << std::endl;
    ::system("pause");
    return 0;
}
