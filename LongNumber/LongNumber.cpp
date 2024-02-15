#include "LongNumber.h"
#include <vector>
#include <sstream>
#include <iostream>

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

    LongNumber operator ""_ln(unsigned long long number) {
        return LongNumber(number);
    }

    std::ostream &operator<<(std::ostream &os, const LongNumber &number) {
        return os << number.toString();
    }

    LongNumber LongNumber::operator-() const {
        LongNumber inverse(*this);
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


        int i = x.digits.size() - 1;
        int j = y.digits.size() - 1;
        while (i >= 0 && j >= 0) {
            if (x.digits[i] != y.digits[j]) {
                return x.digits[i] < y.digits[j];
            }
            --i;
            --j;
        }

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
            precision_diff = -precision_diff;
        }


        short carry = 0;
        int j;
        for (auto i = 0; i < b.digits.size() || carry != 0; ++i) {
            j = i + precision_diff;

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

    LongNumber LongNumber::operator+=(const LongNumber &other) {
        return *this = *this + other;
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
            a.point -= precisionDiff;
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

    LongNumber LongNumber::operator-=(const LongNumber &other) {
        return *this = *this - other;
    }

    LongNumber operator*(const LongNumber &x, const LongNumber &y) {
        if (x.isZero() || y.isZero()) return 0_ln;

        LongNumber c = 0_ln;
        c.sign = (x.sign != y.sign);
        c.point = x.point + y.point;

        short carry;
        for (auto i = 0; i <= x.digits.size(); ++i) {
            carry = 0;
            for (auto j = 0; j <= y.digits.size() || carry != 0; ++j) {
                if (i + j >= c.digits.size()) {
                    c.digits.push_back(0);
                }
                auto n = c.digits[i + j] + x.digits[i] * y.digits[j] + carry;

                c.digits[i + j] = n % 10;

                carry = n / 10;
            }
        }

        c.deleteZeros();

        return c;
    }

    LongNumber LongNumber::operator*=(const LongNumber &other) {
        return *this = *this * other;
    }

    LongNumber operator/(const LongNumber &x, const LongNumber &y) {
        LongNumber a{x}, b{y};

        if (b.isZero()) throw std::overflow_error("division by 0");

        LongNumber c = 0_ln;

        c.sign = (a.sign != b.sign);
        a.sign = false;
        b.sign = false;

        if (b >= a) {
            c.digits.pop_back();
        }

        int precision = fmax(10, fmax(a.point, b.point));
        int magnitude = a.magnitude() - b.magnitude();

        while (a.digits.back() == 0 && b.digits.back() == 0) {
            a.digits.pop_back();
            b.digits.pop_back();
        }


        LongNumber bd;
        short digit;
        while (!a.isZero() && c.digits.size() <= precision + magnitude) {
            if (a < b) {
                c.digits.insert(c.digits.begin(), 0);
                a *= 10_ln;
            }

            digit = 1;
            bd = b;
            while (bd + b <= a && digit < 9) {
                std::cout << digit << ':' << bd << ' ' << b << std::endl;
                bd += b;
                digit++;
            }

            c.digits.insert(c.digits.begin(), digit);
            a -= bd;
            a *= 10_ln;

        }

        c.point = precision;
        c.deleteZeros();

        return c;
    }

    LongNumber LongNumber::operator/=(const LongNumber &other) {
        return *this = *this / other;
    }
}

