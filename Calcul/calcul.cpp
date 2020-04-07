#include "fraction.h"
#include "calcul.h"

#include <iostream>
#include <string>
#include <vector>

void makeQuestion(int range, int num)
{
	FILE* oFile;
	errno_t err;
	if ((err = fopen_s(&oFile, "./Exercises.txt", "w")) != 0) {
		printf("文件打开失败./Exercise.txt\n");
		return;
	}
	
}

void checkAnswer(char* ePath, char* aPath)
{
	FILE* eFile, * aFile,* gFile;
	errno_t err;
	if ((err = fopen_s(&eFile, ePath, "r")) != 0) {
		printf("文件打开失败%s\n", ePath);
		return;
	}
	if ((err = fopen_s(&aFile, aPath, "r")) != 0) {
		printf("文件打开失败%s\n", aPath);
		return;
	}
	if ((err = fopen_s(&gFile, "./Grade.txt", "w")) != 0) {
		printf("文件打开失败Grade.txt\n");
		return;
	}
}