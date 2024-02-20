#ifndef LONGMATH_LONGNUMBER_H
#define LONGMATH_LONGNUMBER_H

#include <vector>
#include <string>

namespace LongMath {
    class LongNumber {
    private:
        std::vector<short> digits;
        unsigned point;
        unsigned precision;
        bool sign;

        void deleteZeros();


    public:
        LongNumber();

        explicit LongNumber(std::string);

        explicit LongNumber(int);

        LongNumber(int, int);

        std::string toString() const;
        std::string toString(int) const;

        friend std::ostream &operator<<(std::ostream &, const LongNumber &);

        bool isZero() const;

        int magnitude() const;

        LongNumber operator-() const;

        friend bool operator==(const LongNumber &, const LongNumber &);

        friend bool operator<(const LongNumber &, const LongNumber &);

        friend bool operator>(const LongNumber &, const LongNumber &);

        friend bool operator<=(const LongNumber &, const LongNumber &);

        friend bool operator>=(const LongNumber &, const LongNumber &);

        friend bool operator!=(const LongNumber &, const LongNumber &);

        friend LongNumber operator-(const LongNumber &, const LongNumber &);

        friend LongNumber operator+(const LongNumber &, const LongNumber &);

        friend LongNumber operator*(const LongNumber &, const LongNumber &);

        friend LongNumber operator/(const LongNumber &, const LongNumber &);

        LongNumber operator-=(const LongNumber &);

        LongNumber operator+=(const LongNumber &);

        LongNumber operator*=(const LongNumber &);

        LongNumber operator/=(const LongNumber &);
    };
}

LongMath::LongNumber operator ""_ln(unsigned long long);

LongMath::LongNumber operator ""_ln(long double);

#endif //LONGMATH_LONGNUMBER_H
