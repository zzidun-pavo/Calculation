#include "trans.h"

int cstrToInt(const char* str)
{
	if (str == nullptr) return 0;

	int x = 0; int len = 0;
	while(str[len]) {
		x *= 10;
		x += str[len++] - '0';
	}
	return x;
}
