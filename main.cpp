#include <iostream>
#include"LongNumber.h"
#include "pi.h"

int main() {
    int  n;
    clock_t start, finish;


    std::cout << "introduce precision: ";
    std::cin >> n;
    start = clock();
    auto _pi = PI::pi(n);
    finish = clock();
    std::cout << "pi = " << _pi.toString(n) << std::endl;
    std::cout << "time: " << static_cast<double>(finish - start)/CLOCKS_PER_SEC << " sec" << std::endl;
    return 0;
}
