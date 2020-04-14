#include "Trie.h"

#include <memory.h>

TrieNode::TrieNode()
{
    //��ʼ��cnt�Ӻͽڵ�
    cnt = 0;
    memset(son, 0, sizeof (son));
}

Trie::Trie()
{
    //��ʼ�����ڵ��cnt
    rt = new TrieNode();
    cnt = 0;
}

int Trie::value(char c)
{
    //������ַ���Χ�ܴ�,������ʵ��ʮ����
    //���ԾͲ�ʹ��ascii����,ֱ�Ӹ�������һ��ֵ
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
    //��Ϊ��ÿ��ʹ�ò��������ʱ�򶼲��ع��˵�
    //���ԾͲ��������ټ����
    cnt++;
    //��������,ֱ��Ҷ�ӽ��
    TrieNode *now = rt;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(!now->son[value(str[i])])
            now->son[value(str[i])] = new TrieNode();
        now = now->son[value(str[i])];
    }
    //��ǰ�ַ��������Ҷ�ӽ��Ϊ��β
    now->cnt++;
}

bool Trie::count(std::string str)
{
    //��������,ֱ��Ҷ�ӽ��
    TrieNode *now = rt;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(now->son[value(str[i])])
            now = now->son[value(str[i])];
        else
            return 0;
    }
    //����������cnt����0,��ô�����Ѿ���һ���ַ������ֹ���
    if(now->cnt) return 1;
    else return 0;
}

int Trie::size()
{
    return cnt;
}
