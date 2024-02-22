#include "LongNumber.h"
#include "string"
#include "iostream"

namespace PI {
    LongMath::LongNumber pi(int precision) {
        LongMath::LongNumber pi{0, precision};

        LongMath::LongNumber n0{1, precision};
        LongMath::LongNumber n = 16_ln;

        LongMath::LongNumber a0{4, precision};
        LongMath::LongNumber b0{2, precision};
        LongMath::LongNumber c0{1, precision};
        LongMath::LongNumber d0{1, precision};

        LongMath::LongNumber a = 1_ln;
        LongMath::LongNumber b = 4_ln;
        LongMath::LongNumber c = 5_ln;
        LongMath::LongNumber d = 6_ln;

        for (auto k = 0; k <= precision; ++k) {
            pi += n0*(a0 / a - b0 / b - c0 / c - d0 / d);
            n0 /= n;
            a += 8_ln;
            b += 8_ln;
            c += 8_ln;
            d += 8_ln;
        }

        return pi;
    }
}