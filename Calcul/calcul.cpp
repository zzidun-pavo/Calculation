#include "fraction.h"
#include "calcul.h"

#include <iostream>
#include <string>
#include <vector>

void makeQuestion(int range, int num)
{
	FILE *oFile = fopen("./Exercises.txt", "w");
	
}

void checkAnswer(char* ePath, char* aPath)
{
	FILE* eFile = fopen(ePath, "r");
	FILE* aFile = fopen(aPath, "r");
	FILE* gFile = fopen("../Grade.txt", "w");

}