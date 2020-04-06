#include "Fraction.h"

#include <iostream>

Fraction::Fraction() {
	this->numerator = 1;
	this->denominator = 1;
}

Fraction::Fraction(long long numerator, long long denominator) {
	this->numerator = numerator;
	this->denominator = denominator;
	contract();
}

void Fraction::contract() {
	long long theGcd = gcd(numerator, denominator);
	numerator /= theGcd;
	denominator /= theGcd;
}

long long Fraction::gcd(long long a, long long b) {
	while (a ^= b ^= a ^= b %= a);
	return b;
}

Fraction Fraction::operator+(const Fraction& o) {
	long long theGcd = gcd(denominator, o.denominator);
	long long theLcm = denominator * o.denominator / theGcd;
	Fraction ret(numerator * theLcm / denominator + o.numerator * theLcm / o.denominator, theLcm);
	ret.contract();
	return ret;
}

Fraction Fraction::operator-(const Fraction& o) {
	long long theGcd = gcd(denominator, o.denominator);
	long long theLcm = denominator * o.denominator / theGcd;
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

Fraction Fraction::operator=(const Fraction& o) {
	return Fraction(o.numerator, o.denominator);
}

bool Fraction::operator<(const Fraction& o) {
	long long theGcd = gcd(denominator, o.denominator);
	if (numerator * o.denominator / theGcd < o.numerator * denominator / theGcd)
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