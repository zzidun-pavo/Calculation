#include "fraction.h"
#include "getopt.h"
#include "trans.h"
#include "calcul.h"

#include <iostream>

int main(int args, char* argv[])
{
	char c;
	char argStr[] = "r:n:e:a:";
	int range = 0;
	int num = 0;
	char* aFile, * eFile;

	while ((c = getopt(args, argv, argStr)) != -1) {
		switch (c) {
		case 'r': range = str2Int(argv[optind-1], 10); break;
		case 'n': num = str2Int(argv[optind-1], 10); break;
		case 'e': eFile = argv[optind]; break;
		case 'a': aFile = argv[optind]; break;
		}

	}
	if (!range || !num) {
		puts("使用-r <range> -n <number> 参数指定生成题目的范围和数量 ");
		puts("使用-e <exercisefile> -a <answer>来批改答案");
	}

	return 0;
}