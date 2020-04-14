#include "opt_getter.h"

#include <string.h>

//因为windwos下某些编译器没有getopt.h(说的就是vs)
//所以写了这个类,来方便获取命令行参数的操作

OptGetter::OptGetter(int args, char** argv) {
        this->args = args;
        this->argv = argv;
}

int OptGetter::getArgId(const char* arg){
        for (int i = 0; i < args; ++i)
        {
                if (strcmp(arg, argv[i]) == 0) {
                        return i;
                }
        }
        return -1;
}

std::string OptGetter::getArg(int argId){
    if (argId >= args) return "";
    return std::string(argv[argId], argv[argId]+strlen(argv[argId]));
}
