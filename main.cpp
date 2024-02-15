#include <iostream>
#include "LongNumber.h"

int main() {
    auto a = LongMath::LongNumber(123);
    auto b = LongMath::LongNumber("-2345.78991276129");
    auto c = LongMath::LongNumber("12345.5126456125");
    std::cout << (a < b) << std::endl;
    std::cout << (b+c) << std::endl;
    std::cout << c << std::endl;
    return 0;
}
