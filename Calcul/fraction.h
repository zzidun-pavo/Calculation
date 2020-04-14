#ifndef FRACTION_H
#define FRACTION_H

#include <string>

//计算最大公因数
int gcd(int a, int b);

//计算最小公倍数
int lcm(int a, int b);

//分数类
class Fraction {
public:
    //分子分母
    int numerator, denominator;

    //构造方法
    Fraction();
    Fraction(int numerator, int denomiator);
    Fraction(std::string str);//根据字符串初始化分数

    void contract();//通分
    Fraction operator+(const Fraction& o);//重载加法运算符
    Fraction operator-(const Fraction& o);//重载减法运算符
    Fraction operator*(const Fraction& o);//重载乘法运算符
    Fraction operator/(const Fraction& o);//重载除法运算符
    void operator=(const Fraction& o);//重载赋值运算符
    bool operator<(const Fraction& o);//重载小于运算符
    bool operator>(const Fraction& o);//重载大于运算符
    bool operator==(const Fraction& o);//重载等于运算符
    bool operator<=(const Fraction& o);//重载小于等于运算符
    bool operator>=(const Fraction& o);//重载大于等于运算符
    bool operator!=(const Fraction& o);//重载不等于运算符
    std::string toString();//将分数类转换成字符串
    bool inRange(int range);//判断分数是否符合条件
};

#endif // FRACTION_H
