#include "LongNumber.h"
#include <vector>
#include <sstream>

namespace LongMath {
    LongNumber::LongNumber() {
        sign = false;
        point = 0;
        digits.push_back(0);
    }

    LongNumber::LongNumber(int input) {
        point = 0;

        sign = false;

        if (input == 0) {
            digits.push_back(0);
            return;
        }

        if (input < 0) {
            sign = true;
            input = -input;
        }

        while (input > 0) {
            digits.push_back(input % 10);
            input /= 10;
        }
    }

    LongNumber::LongNumber(std::string input) {
        if (input[0] == '-') {
            sign = true;
            input.erase(input.begin());
        } else {
            sign = false;
        }

        auto separator = input.find('.');

        if (separator < std::string::npos) {
            point = input.length() - separator - 1;
            input.erase(input.begin() + separator);
        } else {
            separator = input.find(',');
            if (separator < std::string::npos) {
                point = input.length() - separator - 1;
                input.erase(input.begin() + separator);
            } else {
                point = 0;
            }
        }

        auto iter = input.end();
        while (iter != input.begin()) {
            iter--;
            digits.push_back(*iter - '0');
        }

        deleteZeros();
    }

    bool LongNumber::isZero() const {
        return digits.size() == 1 && digits[0] == 0;
    }

    int LongNumber::magnitude() const {
        return digits.size() - point;
    }

    void LongNumber::deleteZeros() {

        while (point > 0 && digits.front() == 0) {
            digits.erase(digits.begin());
            --point;
        }

        while (digits.size() > point + 1 && digits.back() == 0) {
            digits.pop_back();
        }
    }

    std::string LongNumber::toString() const {
        std::string number;

        if (sign) number += '-';

        for (int i = digits.size() - 1; i >= 0; --i) {

            number += static_cast<char>(digits[i] + '0');

            if (i == point) {
                number += '.';
            }
        }

        return number + '0';
    }

    LongNumber operator ""_bf(unsigned long long number) {
        return LongNumber(number);
    }

    std::ostream &operator<<(std::ostream &os, const LongNumber &number) {
        return os << number.toString();
    }

    LongNumber LongNumber::operator-() const {
        auto inverse(*this);
        inverse.sign = !sign;
        return inverse;
    }

    bool operator==(const LongNumber &x, const LongNumber &y) {
        if (x.isZero() && y.isZero()) return true;

        if (y.sign != x.sign || y.point != x.point || x.digits.size() != y.digits.size()) return false;

        for (auto i = 0; i < x.digits.size(); ++i)
            if (x.digits[i] != y.digits[i]) return false;

        return true;
    }

    bool operator<(const LongNumber &x, const LongNumber &y) {
        if (x.isZero()) {
            if (y.isZero()) {
                return false;
            }
            return y.sign;
        } else if (y.isZero()) {
            return !x.sign;
        }

        if (y.sign && x.sign) {
            return -y < -x;
        }

        if (y.sign != x.sign) {
            return y.sign;
        }

        if (y.magnitude() != x.magnitude()) return x.magnitude() < y.magnitude();

        for (int i = x.digits.size() - 1; i >= 0; ++i)
            if (x.digits[i] != y.digits[i]) return x.digits[i] < y.digits[i];

        return x.point < y.point;
    }

    std::strong_ordering operator<=>(const LongNumber &x, const LongNumber &y) {
        if (x == y) {
            return std::strong_ordering::equal;
        } else if (x < y) {
            return std::strong_ordering::less;
        }
        return std::strong_ordering::greater;

    }

    LongNumber operator+(const LongNumber &x, const LongNumber &y) {
        if (x.sign != y.sign) {
            if (y.sign) return x - (-y);
            return y - (-x);
        }

        LongNumber a, b;
        int precision_diff = static_cast<int>(x.point - y.point);
        if (precision_diff > 0) {
            a = x;
            b = y;
        } else {
            a = y;
            b = x;
        }

        auto carry = 0;
        for (auto i = 0; i < a.digits.size() || carry != 0; ++i) {
            auto j = i + precision_diff;

            if (j == a.digits.size()) {
                a.digits.push_back(b.digits[i] + carry);
            } else {
                a.digits[j] += b.digits[i] + carry;
            }

            if (a.digits[j] >= 10) {
                a.digits[j] -= 10;
                carry = 1;
            } else {
                carry = 0;
            }

        }

        a.deleteZeros();

        return a;
    }

    LongNumber operator-(const LongNumber &x, const LongNumber &y) {


        if (y.sign) return x + (-y);
        else if (x.sign) return -(-x + y);
        else if (x < y) return -(y - x);

        LongNumber a{x}, b{y};
        int precisionDiff = static_cast<int>(x.point - y.point);

        if (precisionDiff > 0) {
            b.digits.insert(b.digits.begin(), precisionDiff, 0);
        } else if (precisionDiff != 0) {
            a.digits.insert(a.digits.begin(), -precisionDiff, 0);
        }


        short carry = 0;
        for (auto i = 0; i < a.digits.size() || carry != 0; ++i) {
            a.digits[i] -= carry;
            if (i < b.digits.size()) {
                a.digits[i] -= b.digits[i];
            }

            if (a.digits[i] < 0) {
                a.digits[i] += 10;
                carry = 1;
            } else {
                carry = 0;
            }

        }

        a.deleteZeros();

        return a;
    }
}