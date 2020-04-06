#pragma once

#include <iostream>

long long gcd(long long a, long long b)
{
	while (a ^= b ^= a ^= b %= a);
	return b;
}

class Fraction {
public:
	long long numerator, denominator;
	Fraction();
	Fraction(long long numerator, long long denomiator);
	void contract();
	long long gcd(long long a, long long b);
	Fraction operator+(const Fraction& o);
	Fraction operator-(const Fraction& o);
	Fraction operator*(const Fraction& o);
	Fraction operator/(const Fraction& o);
	Fraction operator=(const Fraction& o);
	bool operator<(const Fraction& o);
	bool operator==(const Fraction& o);
};