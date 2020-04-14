#ifndef FRACTION_H
#define FRACTION_H

#include <string>

//�����������
int gcd(int a, int b);

//������С������
int lcm(int a, int b);

//������
class Fraction {
public:
    //���ӷ�ĸ
    int numerator, denominator;

    //���췽��
    Fraction();
    Fraction(int numerator, int denomiator);
    Fraction(std::string str);//�����ַ�����ʼ������

    void contract();//ͨ��
    Fraction operator+(const Fraction& o);//���ؼӷ������
    Fraction operator-(const Fraction& o);//���ؼ��������
    Fraction operator*(const Fraction& o);//���س˷������
    Fraction operator/(const Fraction& o);//���س��������
    void operator=(const Fraction& o);//���ظ�ֵ�����
    bool operator<(const Fraction& o);//����С�������
    bool operator>(const Fraction& o);//���ش��������
    bool operator==(const Fraction& o);//���ص��������
    bool operator<=(const Fraction& o);//����С�ڵ��������
    bool operator>=(const Fraction& o);//���ش��ڵ��������
    bool operator!=(const Fraction& o);//���ز����������
    std::string toString();//��������ת�����ַ���
    bool inRange(int range);//�жϷ����Ƿ��������
};

#endif // FRACTION_H
