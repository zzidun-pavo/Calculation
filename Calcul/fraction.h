#pragma once

#include <iostream>

//�����������
long long gcd(long long a, long long b);

//������С������
long long lcm(long long a, long long b);

//������
class Fraction {
public:
	//���ӷ�ĸ
	long long numerator, denominator;
	//���췽��
	Fraction();
	Fraction(long long numerator, long long denomiator);

	void contract();//ͨ��
	Fraction operator+(const Fraction& o);//���ؼӷ������
	Fraction operator-(const Fraction& o);//���ؼ��������
	Fraction operator*(const Fraction& o);//���س˷������
	Fraction operator/(const Fraction& o);//���س��������
	Fraction operator=(const Fraction& o);//���ظ�ֵ�����
	bool operator<(const Fraction& o);//����С�������
	bool operator>(const Fraction& o);//���ش��������
	bool operator==(const Fraction& o);//���ص��������
	bool operator<=(const Fraction& o);//����С�ڵ��������
	bool operator>=(const Fraction& o);//���ش��ڵ��������
	bool operator!=(const Fraction& o);//���ز����������
};