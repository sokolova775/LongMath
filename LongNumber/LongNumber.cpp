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

        if (input == 0){
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
        } else{
            separator = input.find(',');
            if (separator < std::string::npos) {
                point = input.length() - separator - 1;
                input.erase(input.begin() + separator);
            } else{
                point = 0;
            }
        }

        auto iter = input.end();
        while (iter != input.begin()){
            iter--;
            digits.push_back(*iter - '0');
        }

        deleteZeros();
    }

    bool LongNumber::isZero() const{
        return digits.size() == 1 && digits[0] == 0;
    }

    int LongNumber::magnitude() const {
        return digits.size() - point;
    }

    void LongNumber::deleteZeros() {

        while(point > 0 && digits.front() == 0) {
            digits.erase(digits.begin());
            --point;
        }

        while (digits.size() > point + 1 && digits.back() == 0){
            digits.pop_back();
        }
    }

    std::string LongNumber::toString() const {
        std::string number;

        if(sign) number += '-';

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


}