#include "calcul.h"

#include <stack>
#include <vector>
#include <string.h>
#include <iostream>

//�ַ����ָ�ɲ������Ͳ�����������
void split(std::vector<std::string>& vec, std::string str)
{
    unsigned int pre = 0;
    char cStr[120];
    strcpy(cStr, str.c_str());

    for(unsigned int now = 0; cStr[now]; ++now)
        if(cStr[now] == ' '){
            if(pre < now)
                vec.push_back(std::string(cStr+pre, cStr+now));
            pre = now+1;
        }else if(cStr[now] == '=') break;
}

//�ж�ĳ���ַ����ǲ��������ǲ�����
bool isOperator(std::string str)
{
    return str=="+" || str=="-" || str=="*" || str=="/" || str == "(" || str == ")";
}

//���ز����������ȶ�
int prior(char op)
{
    if(op == '(' || op == ')')
        return 1;
    if(op == '+' || op == '-')
        return 2;
    if(op == '*' || op == '/')
        return 3;
    return 0;
}

//����
Fraction calcul(std::string exe)
{
    std::stack<Fraction> fracStk;//���ջ�������������
    std::stack<char> optStk;//���ջ�������������

    std::vector<std::string> vec;
    split(vec, exe);

//    for(std::string& s: vec){
//        std::cout << s << std::endl;
//    }


    for(std::string s : vec)
    {
        if(isOperator(s)){
            char op = s[0];
            if(op == '(') optStk.push(op);//������ֱ�ӽ�������ջ
            else if(op == ')'){
                //�����������,��ô�Ͱ�ǰ��ȫ��������Ľ���������,ֱ������������
                while(optStk.top() != '(')
                {
                    Fraction operand2 = fracStk.top(); fracStk.pop();
                    Fraction operand1 = fracStk.top(); fracStk.pop();
                    switch(optStk.top()){
                    case '+': fracStk.push(operand1 + operand2); optStk.pop(); break;
                    case '-': fracStk.push(operand1 - operand2); optStk.pop(); break;
                    case '*': fracStk.push(operand1 * operand2); optStk.pop(); break;
                    case '/': fracStk.push(operand1 / operand2); optStk.pop(); break;
                    }
                }
                optStk.pop();//�������������ŵ���
            }else if(optStk.empty()) optStk.push(op);
            else{
                //�����һ�������������޶ȸ���,��ô�Ȱ���һ���Ľ�������
                while(!optStk.empty() && prior(op) <= prior(optStk.top()))
                {
                    Fraction operand2 = fracStk.top(); fracStk.pop();
                    Fraction operand1 = fracStk.top(); fracStk.pop();
                    switch(optStk.top()){
                    case '+': fracStk.push(operand1 + operand2); optStk.pop(); break;
                    case '-': fracStk.push(operand1 - operand2); optStk.pop(); break;
                    case '*': fracStk.push(operand1 * operand2); optStk.pop(); break;
                    case '/': fracStk.push(operand1 / operand2); optStk.pop(); break;
                    }
                }
                optStk.push(op);//�ѵ�ǰ������ѹ��ȥ
            }
        }else{
            fracStk.push(Fraction(s));//����ǲ�����,ֱ�ӽ�������ջ
        }
    }

    //���������ջ�ǿ�,��ô�Ͱ���ȫ�������
    while(optStk.size())
    {
        Fraction operand2 = fracStk.top(); fracStk.pop();
        Fraction operand1 = fracStk.top(); fracStk.pop();
        switch(optStk.top()){
        case '+': fracStk.push(operand1 + operand2); optStk.pop(); break;
        case '-': fracStk.push(operand1 - operand2); optStk.pop(); break;
        case '*': fracStk.push(operand1 * operand2); optStk.pop(); break;
        case '/': fracStk.push(operand1 / operand2); optStk.pop(); break;
        }
    }
    //��������ջֻ��ʣ��һ����,�����Ǵ�
    return fracStk.top();
}
