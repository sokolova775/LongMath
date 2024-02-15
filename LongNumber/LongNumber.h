#ifndef LONGMATH_LONGNUMBER_H
#define LONGMATH_LONGNUMBER_H

#include <vector>

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
    };

}

#endif //LONGMATH_LONGNUMBER_H
