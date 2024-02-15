#include <iostream>
#include "LongNumber.h"

int main() {
    auto a = LongMath::LongNumber(123);
    auto b = LongMath::LongNumber("12345");
    auto c = LongMath::LongNumber("-12345.123");
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    return 0;
}
