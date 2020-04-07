#include "opt_solver.h"

#include <cstring>

OptSolver::OptSolver(int args, char** argv) {
	this->args = args;
	this->argv = argv;
}

int OptSolver::getArgId(const char* arg){
	for (int i = 0; i < args; ++i)
	{
		if (strcmp(arg, argv[i]) == 0) {
			return i;
		}
	}
	return -1;
}

char* OptSolver::getArg(int argId){
	if (argId >= args) return nullptr;
	return argv[argId];
}