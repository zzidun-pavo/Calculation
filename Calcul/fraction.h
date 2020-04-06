#pragma once

#include <iostream>

//计算最大公因数
long long gcd(long long a, long long b);

//计算最小公倍数
long long lcm(long long a, long long b);

//分数类
class Fraction {
public:
	//分子分母
	long long numerator, denominator;
	//构造方法
	Fraction();
	Fraction(long long numerator, long long denomiator);

	void contract();//通分
	Fraction operator+(const Fraction& o);//重载加法运算符
	Fraction operator-(const Fraction& o);//重载减法运算符
	Fraction operator*(const Fraction& o);//重载乘法运算符
	Fraction operator/(const Fraction& o);//重载除法运算符
	Fraction operator=(const Fraction& o);//重载赋值运算符
	bool operator<(const Fraction& o);//重载小于运算符
	bool operator>(const Fraction& o);//重载大于运算符
	bool operator==(const Fraction& o);//重载等于运算符
	bool operator<=(const Fraction& o);//重载小于等于运算符
	bool operator>=(const Fraction& o);//重载大于等于运算符
	bool operator!=(const Fraction& o);//重载不等于运算符
};