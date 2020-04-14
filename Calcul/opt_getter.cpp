#include "opt_getter.h"

#include <string.h>

//��Ϊwindwos��ĳЩ������û��getopt.h(˵�ľ���vs)
//����д�������,�������ȡ�����в����Ĳ���

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
