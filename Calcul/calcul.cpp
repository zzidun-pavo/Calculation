#include "calcul.h"

#include <stack>
#include <vector>
#include <string.h>
#include <iostream>

//字符串分割成操作符和操作数的数组
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

//判断某个字符串是操作数还是操作符
bool isOperator(std::string str)
{
    return str=="+" || str=="-" || str=="*" || str=="/" || str == "(" || str == ")";
}

//返回操作符的优先度
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

//计算
Fraction calcul(std::string exe)
{
    std::stack<Fraction> fracStk;//这个栈用来存操作数的
    std::stack<char> optStk;//这个栈用来存操作符的

    std::vector<std::string> vec;
    split(vec, exe);

//    for(std::string& s: vec){
//        std::cout << s << std::endl;
//    }


    for(std::string s : vec)
    {
        if(isOperator(s)){
            char op = s[0];
            if(op == '(') optStk.push(op);//左括号直接进操作符栈
            else if(op == ')'){
                //如果是右括号,那么就把前面全部运算符的结果都算出来,直到遇到左括号
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
                optStk.pop();//把遇到的左括号弹出
            }else if(optStk.empty()) optStk.push(op);
            else{
                //如果上一个操作符的有限度更大,那么先把上一个的结果算出来
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
                optStk.push(op);//把当前操作符压进去
            }
        }else{
            fracStk.push(Fraction(s));//如果是操作数,直接进操作数栈
        }
    }

    //如果操作符栈非空,那么就把他全部算出来
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
    //最后操作数栈只会剩下一个数,并且是答案
    return fracStk.top();
}
