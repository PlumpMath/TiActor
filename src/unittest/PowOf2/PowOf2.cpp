

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>

#include <TiActor/utils/PowOf2.h>
#include <TiActor/basic/static_link.h>

int main(int argn, char * argv[])
{
    std::cout << "Template round_up_to_pow2<N> Test..." << std::endl << std::endl;

    int isPow2;
    isPow2 = TiActor::math::is_pow_of_2<0>::value;
    std::cout << "isPow2(0) = " << isPow2 << std::endl;

    isPow2 = TiActor::math::is_pow_of_2<1>::value;
    std::cout << "isPow2(1) = " << isPow2 << std::endl;

    isPow2 = TiActor::math::is_pow_of_2<2>::value;
    std::cout << "isPow2(2) = " << isPow2 << std::endl;

    isPow2 = TiActor::math::is_pow_of_2<3>::value;
    std::cout << "isPow2(3) = " << isPow2 << std::endl;

    isPow2 = TiActor::math::is_pow_of_2<4>::value;
    std::cout << "isPow2(4) = " << isPow2 << std::endl;

    isPow2 = TiActor::math::is_pow_of_2<121>::value;
    std::cout << "isPow2(121) = " << isPow2 << std::endl;

    isPow2 = TiActor::math::is_pow_of_2<128>::value;
    std::cout << "isPow2(128) = " << isPow2 << std::endl;

    std::cout << std::endl;

    {
        size_t pow2_0 = TiActor::math::round_up_to_pow2<0>::value;
        std::cout << "pow2_up(0) = " << pow2_0 << std::endl;

        size_t pow2_1 = TiActor::math::round_up_to_pow2<1>::value;
        std::cout << "pow2_up(1) = " << pow2_1 << std::endl;

        size_t pow2_2 = TiActor::math::round_up_to_pow2<2>::value;
        std::cout << "pow2_up(2) = " << pow2_2 << std::endl;

        size_t pow2_3 = TiActor::math::round_up_to_pow2<3>::value;
        std::cout << "pow2_up(3) = " << pow2_3 << std::endl;

        size_t pow2_a = TiActor::math::round_up_to_pow2<33>::value;
        std::cout << "pow2_up(33) = " << pow2_a << std::endl;

        size_t pow2_b = TiActor::math::round_up_to_pow2<213>::value;
        std::cout << "pow2_up(213) = " << pow2_b << std::endl;

        size_t pow2_c = TiActor::math::round_up_to_pow2<256>::value;
        std::cout << "pow2_up(256) = " << pow2_c << std::endl;
    }

    std::cout << std::endl;

    {
        size_t pow2_0 = TiActor::math::round_down_to_pow2<0>::value;
        std::cout << "pow2_down(0) = " << pow2_0 << std::endl;

        size_t pow2_1 = TiActor::math::round_down_to_pow2<1>::value;
        std::cout << "pow2_down(1) = " << pow2_1 << std::endl;

        size_t pow2_2 = TiActor::math::round_down_to_pow2<2>::value;
        std::cout << "pow2_down(2) = " << pow2_2 << std::endl;

        size_t pow2_3 = TiActor::math::round_down_to_pow2<3>::value;
        std::cout << "pow2_down(3) = " << pow2_3 << std::endl;

        size_t pow2_a = TiActor::math::round_down_to_pow2<33>::value;
        std::cout << "pow2_down(33) = " << pow2_a << std::endl;

        size_t pow2_b = TiActor::math::round_down_to_pow2<213>::value;
        std::cout << "pow2_down(213) = " << pow2_b << std::endl;

        size_t pow2_c = TiActor::math::round_down_to_pow2<256>::value;
        std::cout << "pow2_down(256) = " << pow2_c << std::endl;
    }

    std::cout << std::endl;
    ::system("pause");
    return 0;
}
