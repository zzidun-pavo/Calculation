#ifndef MAKE_CHECK_H
#define MAKE_CHECK_H

#include <string>

//生成题目
void makeQuestion(int range, int num);

//检查答案
void checkAnswer(std::string ePath, std::string aPath);

#endif // MAKE_CHECK_H
