#pragma once

//处理参数
class OptSolver {
	int args;
	char** argv;
public:
	OptSolver(int args, char** argv);//构造方法
	int getArgId(const char* arg);//获得某参数的下标
	char* getArg(int argId);//获得某位置的参数
};