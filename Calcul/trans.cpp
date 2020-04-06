#include "trans.h"

int str2Int(char* str, int radix)
{
	int x = 0;
	int len = 0;
	while(str[len]) {
		x *= radix;
		x += str[len++] - '0';
	}
	return x;
}
