#include "fraction.h"

#include <string>

int gcd(int a, int b)
{
    if (a == 0) return b;
    if (b == 0) return a;
    while (a ^= b ^= a ^= b %= a);//一行GCD神教原教旨主义者的神秘咒语
    return b;
}

int lcm(int a, int b)
{
    return a * b / gcd(a, b);
}

Fraction::Fraction() {
    //默认的构造函数生成分数0
    this->numerator = 0;
    this->denominator = 1;
}

Fraction::Fraction(int numerator, int denominator) {
    //根据指定的分子分母生成分数
    this->numerator = numerator;
    this->denominator = denominator;
    contract();//通分
}

Fraction::Fraction(std::string str) {
    int mix = 0;//带分数的整数部分
    numerator = -1;//带分数的分子部分
    denominator = 0;//带分数的分母部分
    unsigned pre = 0;
    for (unsigned int i = 0; str[i]; ++i)
    {
        if (str[i] == '\'') {
            while (pre < i) {
                mix *= 10;
                mix += static_cast<int>(str[pre++] - '0');
            }
            pre++;
        }
        else if (str[i] == '/') {
            numerator = 0;
            while (pre < i) {
                numerator *= 10;
                numerator += static_cast<int>(str[pre++] - '0');
            }
            pre++;
        }
    }
    //如果分子等于-1,说明带分数只有整数部分,那么未处理的部分就是他的整数部分
    //否则他就是分母部分
    if (numerator != -1) {
        while (str[pre]) {
            denominator *= 10;
            denominator += static_cast<int>(str[pre++] - '0');
        }
        numerator += mix * denominator;
        contract();
    }
    else {
        while (str[pre]) {
            mix *= 10;
            mix += static_cast<int>(str[pre++] - '0');
        }
        numerator = mix;
        denominator = 1;
    }

}

//以下为通分和重载操作符加减乘除的部分
//小学四年级必修课程内容,十分浅显易见

void Fraction::contract() {
    int theGcd = gcd(numerator, denominator);
    numerator /= theGcd;
    denominator /= theGcd;
}

Fraction Fraction::operator+(const Fraction& o) {
    int theGcd = gcd(denominator, o.denominator);
    int theLcm = denominator * o.denominator / theGcd;
    Fraction ret(numerator * theLcm / denominator + o.numerator * theLcm / o.denominator, theLcm);
    ret.contract();
    return ret;
}

Fraction Fraction::operator-(const Fraction& o) {
    int theGcd = gcd(denominator, o.denominator);
    int theLcm = denominator * o.denominator / theGcd;
    Fraction ret(numerator * theLcm / denominator - o.numerator * theLcm / o.denominator, theLcm);
    ret.contract();
    return ret;
}

Fraction Fraction::operator*(const Fraction& o) {
    Fraction ret(numerator * o.numerator, denominator * o.denominator);
    ret.contract();
    return ret;
}

Fraction Fraction::operator/(const Fraction& o) {
    Fraction ret(numerator * o.denominator, denominator * o.numerator);
    ret.contract();
    return ret;
}

void Fraction::operator=(const Fraction& o) {
    numerator = o.numerator;
    denominator = o.denominator;
}

bool Fraction::operator<(const Fraction& o) {
    int theGcd = gcd(denominator, o.denominator);
    if (numerator * o.denominator / theGcd < o.numerator * denominator / theGcd)
        return true;
    else
        return false;
}

bool Fraction::operator>(const Fraction& o) {
    int theGcd = gcd(denominator, o.denominator);
    if (numerator * o.denominator / theGcd > o.numerator * denominator / theGcd)
        return true;
    else
        return false;
}

bool Fraction::operator==(const Fraction& o) {
    if (numerator == o.numerator && denominator == o.denominator)
        return true;
    else
        return false;
}

bool Fraction::operator<=(const Fraction& o) {
    if (operator<(o) || operator==(o))
        return true;
    else
        return false;
}

bool Fraction::operator>=(const Fraction& o) {
    if (operator>(o) || operator==(o))
        return true;
    else
        return false;
}

bool Fraction::operator!=(const Fraction& o) {
    if (!(numerator == o.numerator && denominator == o.denominator))
        return true;
    else
        return false;
}

//把分数转换为字符串,以便输出
std::string Fraction::toString() {
    std::string ret = "";
    if (numerator >= denominator) {
        ret += std::to_string(numerator/denominator);
    }
    if (numerator % denominator) {
        if(numerator >= denominator) ret += "'";
        ret += std::to_string(numerator%denominator);
        ret += "/";
        ret += std::to_string(denominator);
    }
    if (numerator == 0) ret += "0";
    return ret;
}

bool Fraction::inRange(int range)
{
    return denominator < range && numerator/denominator < range && numerator >= 0 && denominator > 0;
}
