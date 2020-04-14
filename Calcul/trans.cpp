#include "trans.h"

int cstrToInt(std::string str)
{
        if (str.length() == 0) return 0;

        int x = 0;
        unsigned int len = 0;
        while(str[len]) {
                x *= 10;
                x += str[len++] - '0';
        }
        return x;
}
