#ifndef OPT_GETTER_H
#define OPT_GETTER_H

#include <string>

//�������
class OptGetter {
    int args;
    char** argv;
public:
    OptGetter(int args, char** argv);//���췽��
    int getArgId(const char* arg);//���ĳ�������±�
    std::string getArg(int argId);//���ĳλ�õĲ���
};

#endif // OPT_GETTER_H
