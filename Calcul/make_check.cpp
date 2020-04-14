#include "fraction.h"
#include "make_check.h"
#include "calcul.h"
#include "Trie.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <ctime>

//某深海中的stl操作
static std::mt19937 rnd(static_cast<unsigned int>(time(nullptr)));

//生成一个range内的整数
inline int randInt(int range)
{
    return static_cast<int>(rnd() % INT_MAX) % range;
}

//生成符合要求的range范围的分数
inline Fraction randFrac(int range)
{
    int deno = randInt(range-1)+1;
    int mix = randInt(range);
    int nume = mix*deno + randInt(deno);
    return Fraction(nume, deno);
}

//生成符合要求的range范围的分数,并且他是小于maxFrac的
inline Fraction randFrac(Fraction maxFrac, int range)
{
    Fraction ret;
    do{
        ret = randFrac(range);
    }while(ret > maxFrac);
    return Fraction();
}

//检查输入的范围和生成题目数量是否合理
//(其实这些数字挺合理的,但是我的代码太菜了,要生成这些题目会可能卡住
bool checkRange(int range, int num)
{
    if(range <= 1) return 1;
    if(range == 2 && num >= 20) return 1;
    if(range == 3 && num >= 400) return 1;
    if(range == 4 && num >= 1000) return 1;
    if(range == 5 && num >= 3000) return 1;
    if(range == 6 && num >= 6000) return 1;
    if(num > 10000) return 1;
    if(range > 10000) return 1;
    return 0;
}

//一堆不堪一看的代码
/*
std::string randQuestion1(Fraction ans, int range, int dep, int prior)
{
    int opt = randInt(4);

    Fraction a, b;
    if(dep == 0) return ans.toString();

    if(opt == 0)
    {
        do{
            a = randFrac(ans, range);
            b = ans - a;
        }while(!b.inRange(range));

        if(a < b)
        {
            Fraction c = a;
            a = b; b = c;
        }

        if(prior > 1)
        {
            if(randInt(2)) return std::string("( "+randQuestion1(a, range, dep-1, 1)+" + "+b.toString() + " )");
            else return std::string("( "+a.toString()+" + "+randQuestion1(b, range, dep-1, 1)+" )");
        }else
        {
            if(randInt(2)) return std::string(randQuestion1(a, range, dep-1, 1)+" + "+b.toString());
            else return std::string(a.toString()+" + "+randQuestion1(b, range, dep-1, 1));
        }

    }else if(opt == 1)
    {
        do{
            a = randFrac(range);
            b = a - ans;
        }while(!b.inRange(range));

        if(prior > 1)
        {
            if(randInt(2)) return std::string("( "+randQuestion1(a, range, dep-1, 1)+" - "+b.toString() + " )");
            else return std::string("( "+a.toString()+" - "+randQuestion1(b, range, dep-1, 1)+" )");
        }else
        {
            if(randInt(2)) return std::string(randQuestion1(a, range, dep-1, 1)+" - "+b.toString());
            else return std::string(a.toString()+" - "+randQuestion1(b, range, dep-1, 1));
        }

    }else if(opt == 2)
    {
        do{
            do{
                b = randFrac(range);
            }while(b.numerator == 0);
            a = ans / b;
        }while(!a.inRange(range));

        if(a < b)
        {
            Fraction c = a;
            a = b; b = c;
        }

        if(randInt(2)) return std::string(randQuestion1(a, range, dep-1, 2)+" * "+b.toString());
        else return std::string(a.toString()+" * "+randQuestion1(b, range, dep-1, 2));

    }else if(opt == 3)
    {
        do{
            a = randFrac(range);
            b = a/ans;
        }while(!b.inRange(range));

        if(randInt(2)) return std::string(randQuestion1(a, range, dep-1, 2)+" / "+b.toString());
        else return std::string(a.toString()+" / "+randQuestion1(b, range, dep-1, 2));

    }else{
        return "";
    }
}

Fraction count(Fraction a, int opt, Fraction b)
{
    switch(opt)
    {
    case 0: return a + b;
    case 1: return a - b;
    case 2: return a * b;
    case 3: return a / b;
    default: return Fraction();
    }
}
*/

//生成一条题目
std::string randQuestion(int range, int optNum)
{
    Fraction ans, now;
    int cnt = 0;
    std::string ret, tmp;

    now = randFrac(range);
    ret += now.toString();

    while(cnt <= optNum)
    {
        int opt = randInt(4);

        int times = 0;

        do{
            times++;
            if(times > 3){
                opt = randInt(4);
                times = 0;
            }else
                now = randFrac(range);


            if(opt == 3) while(now.numerator == 0) now = randFrac(range);


            switch(opt){
                case 0: tmp = ret + " + " + now.toString();break;
                case 1: tmp = ret + " - " + now.toString();break;
                case 2: tmp = ret + " * " + now.toString();break;
                case 3: tmp = ret + " / " + now.toString();break;
            }

        }while(!calcul(tmp + " =").inRange(range));

        cnt++;
        ret = tmp;
    }

    return ret;
}

//生成一堆题目
void makeQuestion(int range, int num)
{
    //文件操作
    std::ofstream eStream, aStream;
    eStream.open("./Exercises.txt", std::ios::out);
    aStream.open("./Answers.txt", std::ios::out);

    Trie uniqueTrie;//字典树,用来判重

    if(checkRange(range, num)){
        std::cout << "数字的范围与题目的数量差别太悬殊了!" << std::endl;
        return;
    }


    std::string nowQuestion;

    //Fraction ans;
    //int dep = 0;

    while(num--)
    {
/*
        dep = randInt(4);
        ans = randFrac(range);
        nowQuestion = randQuestion1(ans, range, dep, 0);
        while(uniqueTrie.count(nowQuestion)){
            dep = (rnd()+INT_MAX) % 4;
            ans = randFrac(range);
            nowQuestion = randQuestion1(ans, range, dep, 0);
        }
*/
        //一路生成,直到题目没有出现过
        do{
            nowQuestion = randQuestion(range, randInt(3));
        }while(uniqueTrie.count(nowQuestion));

        uniqueTrie.insert(nowQuestion);
        //std::cout << nowQuestion << std::endl;
        nowQuestion += " =";
        eStream << uniqueTrie.size() << ":" << nowQuestion << std::endl;
        aStream << uniqueTrie.size() << ":" << calcul(nowQuestion).toString() << std::endl;
    }

    //关闭文件
    aStream.close();
    eStream.close();
}

//检查一堆题目
void checkAnswer(std::string ePath, std::string aPath)
{
    //文件操作
    std::ifstream eStream, aStream;
    std::ofstream gStream;
    eStream.open(ePath.c_str(), std::ios::in);  if(!eStream.is_open())  { std::cout << "文件打开失败" << ePath << std::endl; return;}
    aStream.open(aPath.c_str(), std::ios::in);  if(!aStream.is_open())  { std::cout << "文件打开失败" << aPath << std::endl; return;}

    std::vector<int> correct, incorrect;
    int cnt = 1;

    //一次读取一行
    std::string eLine, aLine;
    while(std::getline(eStream, eLine) &&
          std::getline(aStream, aLine))
    {
        //去掉前面的题号
        unsigned int cat = 0;
        while(eLine[cat] != ':') cat++;
        eLine = eLine.substr(cat+1);
        aLine = aLine.substr(cat+1);
        //然后扔到calcul函数里算一个结果
        if(calcul(eLine) == Fraction(aLine))
            correct.push_back(cnt++);
        else
            incorrect.push_back(cnt++);
    }

    //关闭文件
    eStream.close();
    aStream.close();

    gStream.open("./Grade.txt", std::ios::out);

    //输出所有题目的正误
    if(correct.size()){
        gStream << "Correct: " << correct.size() << " (";
        for(unsigned int i = 0; i < correct.size(); ++i)
            gStream << correct[i] << ((i+1 != correct.size())?',':')');
        gStream << std::endl;
    }
    if(incorrect.size()){
        gStream << "Wrong: " << incorrect.size() << " (";
        for(unsigned int i = 0; i < incorrect.size(); ++i)
            gStream << incorrect[i] << ((i+1 != incorrect.size())?',':')');
        gStream << std::endl;
    }

    //关闭文件
    gStream.close();
}

