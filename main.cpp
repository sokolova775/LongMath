#include <iostream>
#include "LongNumber.h"

int main() {
    auto a = LongMath::LongNumber(143);
    auto d = LongMath::LongNumber(12);
    auto b = LongMath::LongNumber("-2345");
    auto c = LongMath::LongNumber("12345.5126456125");
    std::cout << b << std::endl;
    std::cout << (c/b) << std::endl;
    std::cout << c << std::endl;
    return 0;
}
