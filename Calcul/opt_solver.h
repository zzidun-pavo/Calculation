#pragma once

//�������
class OptSolver {
	int args;
	char** argv;
public:
	OptSolver(int args, char** argv);//���췽��
	int getArgId(const char* arg);//���ĳ�������±�
	char* getArg(int argId);//���ĳλ�õĲ���
};