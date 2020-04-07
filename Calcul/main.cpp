#include "opt_solver.h"
#include "trans.h"
#include "calcul.h"

#include <iostream>

int main(int args, char** argv)
{
	int range = 0; int num = 0;
	char* aPath = nullptr, * ePath = nullptr;
	int id = -1;

	OptSolver oser(args, argv);
	
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
		printf("题目数字的范围不大于%d\n", range);
		printf("题目的数量为%d\n", num);
	}
	else if(aPath && ePath){
		printf("题目的文件路径是%s\n", ePath);
		printf("答案的文件路径是%s\n", aPath);
		checkAnswer(ePath, aPath);

	}
	else {
		puts("使用-r <range> -n <number> 参数指定生成题目的范围和数量 ");
		puts("使用-e <exercisefile> -a <answer>来批改答案");
	}

	return 0;
}