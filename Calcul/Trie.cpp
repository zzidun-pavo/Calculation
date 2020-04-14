#include "Trie.h"

#include <memory.h>

TrieNode::TrieNode()
{
    //初始化cnt子和节点
    cnt = 0;
    memset(son, 0, sizeof (son));
}

Trie::Trie()
{
    //初始化根节点和cnt
    rt = new TrieNode();
    cnt = 0;
}

int Trie::value(char c)
{
    //所需的字符范围很大,但是其实就十几种
    //所以就不使用ascii码了,直接给他定义一个值
    switch(c){
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case '\'': return 10;
    case '/': return 11;
    case '+': return 12;
    case '-': return 13;
    case '*': return 14;
    case ' ': return 15;
    case '=': return 16;
    default: return -1;
    }
}

void Trie::insert(std::string str)
{
    //因为我每次使用插入操作的时候都查重过了的
    //所以就不在这里再检查了
    cnt++;
    //步步迭代,直到叶子结点
    TrieNode *now = rt;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(!now->son[value(str[i])])
            now->son[value(str[i])] = new TrieNode();
        now = now->son[value(str[i])];
    }
    //当前字符串以这个叶子结点为结尾
    now->cnt++;
}

bool Trie::count(std::string str)
{
    //步步迭代,直到叶子结点
    TrieNode *now = rt;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(now->son[value(str[i])])
            now = now->son[value(str[i])];
        else
            return 0;
    }
    //如果这个结点的cnt大于0,那么至少已经有一个字符串出现过了
    if(now->cnt) return 1;
    else return 0;
}

int Trie::size()
{
    return cnt;
}
