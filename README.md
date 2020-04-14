## github项目地址

https://github.com/zzidun-pavo/Calculation.git

## 耗费的时间

| PSP                                     | Personal Software Process Stages        | 预估耗时（分钟） | 实际耗时（分钟） |
| --------------------------------------- | --------------------------------------- | ---------------- | ---------------- |
| Planning                                | 计划                                    |                  |                  |
| · Estimate                              | · 估计这个任务需要多少时间              | 15               | 10               |
| Development                             | 开发                                    |                  |                  |
| · Analysis                              | · 需求分析 (包括学习新技术)             | 30               | 40               |
| · Design Spec                           | · 生成设计文档                          | 50               | 120              |
| · Design Review                         | · 设计复审 (和同事审核设计文档)         | 30               | 10               |
| · Coding Standard                       | · 代码规范 (为目前的开发制定合适的规范) | 30               | 20               |
| · Design                                | · 具体设计                              | 60               | 30               |
| · Coding                                | · 具体编码                              | 400              | 1100             |
| · Code Review                           | · 代码复审                              | 100              |                  |
| · Test                                  | · 测试（自我测试，修改代码，提交修改）  | 60               | 40               |
| Reporting                               | 报告                                    |                  |                  |
| · Test Report                           | · 测试报告                              | 40               | 40               |
| · Size Measurement                      | · 计算工作量                            | 20               | 20               |
| · Postmortem & Process Improvement Plan | · 事后总结, 并提出过程改进计划          | 30               | 30               |
| 合计                                    |                                         |                  |                  |

## 效能分析

![](https://img2020.cnblogs.com/blog/1597450/202004/1597450-20200414221833516-1146689914.png)
![](https://img2020.cnblogs.com/blog/1597450/202004/1597450-20200414221839589-208345145.png)



在vs的性能探测中,可以看到大部分的开销是io操作.

其次就是计算等式所调用的`calcul()`函数,以及这个函数所调用的`split()`.

因为需要不断地随机生成,每次生成一条都要调用数次的`calcul()`函数.

生成题目的复杂度到后面可能要到阶层的级别.

在找到更好的生成方法前,这个消耗很难减少.

其他查重等操作已经通过一些数据结构降低到O(n)的复杂度了.



## 要求和思路

##### 要求

- 使用-n参数控制生成题目的个数
- 使用-r参数控制生成题目中的数值
- 生成的题目计算过程中不能产生负数
- 如果存在形如$e_1\div e_2$的子表达式,那么其结果是真分数.
- 每道题目中运算符不超过3个
- 程序一次运行生成的题目不能重复,生成的题目存入执行程序的当前目录下的`Exercises.txt`文件

> 1.四则运算题目1
>
> 2.四则运算题目2

- 生成题目的同时,计算出所有题目的答案,并存入执行程序的当前目录下的`answer.txt`文件.

> 答案1
>
> 答案2

- 程序能支持一万道题目的生成
- 程序支持对给定题目文件和答案文件,判断答案中的对错并进行数量统计,结果输出到文件`Grade.txt`

```shell
Myapp.exe -e <exercisefile>.txt -a <answer>.txt
```

> Correct: 5 (1,3,5,7,9)
>
> Wrong: 5 (2,4,6,8,10)



##### 保证数字的范围

先生成一个结果作为答案,然后再生成题目,每次产生下一个操作数的时候根据答案来控制.

##### 分数的实现

IEEE754的小数存在精度问题,算出小数再倒推分数会很麻烦.

全程不用小数,先实现一个分数类,分数类中自动用gcd约分.

##### 范围和数量的关系

当n和r的大小不恰当时,r的范围内出不了n道题目.

要先计算出对于每一个r,最多能产生多少道题目.

对于不恰当的输入参数,返回某些结果.

##### 如何实现

~~先随机产生除法和减法的运算符,使得运算数不同.~~

~~因为除法和减法没有交换性,所以只需要保证每个位置的数字不同,即可保证没有重复的式子.~~

~~然后在产生的几个操作数中,随机拆分成若干个数的相加或者相乘.~~

以上为错误示范.

可能是因为我操作有问题,或者说这个方向本身就不对.

写道后面发现极为复杂.于是放弃.

最终还是选择一个操作数,一个操作符地生成.

##### 效率问题

~~当n远大于r的时候,这样子的生成是非常慢的,因为产生出相同式子的概率非常大.~~

~~所以应该确认一个范围,当n比r大到一定程度后,不再随机产生式子,而是按顺序枚举式子.~~

以上的考虑是多余的,如果其实直接生成的效率还是挺高的

#### 判重

如果直接字符串hash的话,脑测冲突太大.

所以选择了字典树的方法,字符串的长度非常有限,所以每次查询和插入都接近O(1),空间为O(n)

## 设计

![](https://img2020.cnblogs.com/blog/1597450/202004/1597450-20200414221821007-284272551.png)



main()处理命令行参数,决定生成题目和批改答案.

如果生成题目,则不断调用`randQuestion()`函数,每次生成后用字典树判重.直到题目数量足够.

如果检查答案,那么就逐行读入题目,题目扔到calcul()中算出结果,判断结果和答案对比.

## 代码说明

#### main:

主函数,判断参数并且调用函数

```c++
int main(int args, char** argv)
{
    int range = 0; int num = 0;
    std::string aPath, ePath;
    int id = -1;

    OptGetter oser(args, argv);

    if ((id = oser.getArgId("-r")) != -1) {
        range = cstrToInt(oser.getArg(id + 1));
    }

    if ((id = oser.getArgId("-n")) != -1) {
        num = cstrToInt(oser.getArg(id + 1));
    }

    if ((id = oser.getArgId("-e")) != -1) {
        ePath = oser.getArg(id + 1);
    }

    if ((id = oser.getArgId("-a")) != -1) {
        aPath = oser.getArg(id + 1);
    }


    if (range && num) {
        std::cout << "题目数字的范围不大于" << range << std::endl;
        std::cout << "题目的数量为" << num << std::endl;
        makeQuestion(range, num);
    }
    else if(aPath.length() && ePath.length()){
        std::cout << "题目的文件路径是" << ePath << std::endl;
        std::cout << "答案的文件路径是" << aPath << std::endl;
        checkAnswer(ePath, aPath);

    }
    else {
        std::cout << "使用-r <range> -n <number> 参数指定生成题目的范围和数量" << std::endl;
        std::cout << "使用-e <exercisefile> -a <answer>来批改答案" << std::endl;
    }

    return 0;
}
```

#### fraction:

实现分数的存储和表示(这些函数的实现比较简单)

```C++
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
```

#### opt_solver:

处理参数

```C++
//处理参数
class OptGetter {
    int args;
    char** argv;
public:
    OptGetter(int args, char** argv);//构造方法
    int getArgId(const char* arg);//获得某参数的下标
    std::string getArg(int argId);//获得某位置的参数
};
```

#### calcul:

##### split()

把字符串根据空格分割成操作符和操作数,存在一个`vector`中

```C++
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
```

##### calcul()

用两个栈实现计算

```C++
//计算
Fraction calcul(std::string exe)
{
    std::stack<Fraction> fracStk;//这个栈用来存操作数的
    std::stack<char> optStk;//这个栈用来存操作符的

    std::vector<std::string> vec;
    split(vec, exe);

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
```

#### randQuestion

生成一条题目.

我注意到,在某些情况下,对于某个操作符很难得出合法的操作数.

为了防止被卡在这个位置,我每3次就会更新opt,换一个更容易生成操作数的操作符.

```C++
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
```

## 测试运行

一些测试数据
![](https://img2020.cnblogs.com/blog/1597450/202004/1597450-20200414221753344-1470632763.png)
![](https://img2020.cnblogs.com/blog/1597450/202004/1597450-20200414221802335-1134614607.png)





## 项目小结

player1:

	这次的作业,我总结我这次就一种感觉"想的太多,做的太少".
	
	一开始方向就有问题,但是一直在想一些边缘的操作上抓牛角尖.方向错误,越努力越反动.
	
	还没做完一直想怎么优化,做起来束手束脚,很多代码改来改去.什么hash,Trie的.
	
	最终没有时间,连交换律都不知道怎么处理.

player2:

	这是我第一次与人合作。相比起以前一个人独立完成任务时的艰辛，合作结对的优势在于集思广益，使得在进行分析设计时考虑更加全面完整、编码时速度更快、任务完成度更高，也使得参与者们能相互学习相互促进。