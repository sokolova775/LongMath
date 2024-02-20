#include <iostream>
#include"LongNumber.h"
#include "pi.h"

int main() {
    int  n;
    std::cout << "введите точность: ";
    std::cin >> n;
    auto _pi = PI::pi(n);
    std::cout << (_pi.toString(n) == PI::PI.toString(n)) << std::endl;
    return 0;
}
