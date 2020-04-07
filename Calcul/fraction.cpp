#include "fraction.h"

#include <string>

long long gcd(long long a, long long b)
{
	if (a == 0) return b;
	if (b == 0) return a;
	while (a ^= b ^= a ^= b %= a);
	return b;
}

long long lcm(long long a, long long b)
{
	return a * b / gcd(a, b);
}

Fraction::Fraction() {
	this->numerator = 1;
	this->denominator = 1;
}

Fraction::Fraction(long long numerator, long long denominator) {
	this->numerator = numerator;
	this->denominator = denominator;
	contract();
}

Fraction::Fraction(std::string str) {
	long long mix = 0;
	numerator = denominator = 0;
	int pre = 0, now = 0;
	for (int i = 0; str[i]; ++i)
	{
		if (str[i] == '\'') {
			while (pre < i) {
				mix *= 10;
				mix += (long long)str[i] - '0';
			}
			pre = i + 1;
		}
		else if (str[i] == '/') {
			while (pre < i) {
				numerator *= 10;
				numerator += (long long)str[i] - '0';
			}
			pre = i + 1;
		}
	}

	if (numerator) {
		while (str[pre]) {
			denominator *= 10;
			denominator += (long long)str[pre++] - '0';
		}
		numerator += mix * denominator;
		contract();
	}
	else {
		while (str[pre]) {
			mix *= 10;
			mix += (long long)str[pre++] - '0';
		}
		numerator = mix;
		denominator = 1;
	}

}
	
void Fraction::contract() {
	long long theGcd = gcd(numerator, denominator);
	numerator /= theGcd;
	denominator /= theGcd;
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

bool Fraction::operator>(const Fraction& o) {
	long long theGcd = gcd(denominator, o.denominator);
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