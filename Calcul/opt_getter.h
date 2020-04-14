#ifndef OPT_GETTER_H
#define OPT_GETTER_H

#include <string>

//处理参数
class OptGetter {
    int args;
    char** argv;
public:
    OptGetter(int args, char** argv);//构造方法
    int getArgId(const char* arg);//获得某参数的下标
    std::string getArg(int argId);//获得某位置的参数
};

#endif // OPT_GETTER_H
