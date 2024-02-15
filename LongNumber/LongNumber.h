#ifndef LONGMATH_LONGNUMBER_H
#define LONGMATH_LONGNUMBER_H

#include <vector>
#include <compare>

namespace LongMath {
    class LongNumber {
    private:
        std::vector<short> digits;
        unsigned point;
        bool sign;

        void deleteZeros();
    public:

        LongNumber();
        explicit LongNumber(std::string);
        explicit LongNumber(int);

        std::string toString() const;
        friend std::ostream& operator<<(std::ostream&,const LongNumber &);

        bool isZero() const;
        int magnitude() const;

        LongNumber operator-() const;

        friend bool operator==(const LongNumber &, const LongNumber &);
        friend bool operator<(const LongNumber &, const LongNumber &);
        friend std::strong_ordering operator<=>(const LongNumber &, const LongNumber &);

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

#endif //LONGMATH_LONGNUMBER_H
