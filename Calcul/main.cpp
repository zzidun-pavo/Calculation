#include "opt_getter.h"
#include "trans.h"
#include "make_check.h"

#include <iostream>

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
        std::cout << "��Ŀ���ֵķ�Χ������" << range << std::endl;
        std::cout << "��Ŀ������Ϊ" << num << std::endl;
        makeQuestion(range, num);
    }
    else if(aPath.length() && ePath.length()){
        std::cout << "��Ŀ���ļ�·����" << ePath << std::endl;
        std::cout << "�𰸵��ļ�·����" << aPath << std::endl;
        checkAnswer(ePath, aPath);

    }
    else {
        std::cout << "ʹ��-r <range> -n <number> ����ָ��������Ŀ�ķ�Χ������" << std::endl;
        std::cout << "ʹ��-e <exercisefile> -a <answer>�����Ĵ�" << std::endl;
    }

    return 0;
}
