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
