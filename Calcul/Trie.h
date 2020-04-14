#ifndef TRIE_H
#define TRIE_H

#include <string>

//字典树的结点
class TrieNode{
public:
    TrieNode *son[20];//字典树的儿子
    int cnt;//记录是否存在一个字符串,把当前结点作为最后的结点
    TrieNode();//构造方法
};

//字典树
class Trie{
private:
    TrieNode *rt;//树根
    int cnt;//当前存了多少个字符串
public:
    Trie();//构造方法
    int value(char c);//给所有字符设置一个值
    void insert(std::string str);//插入一个字符串
    bool count(std::string str);//查询是否存在某字符串
    int size();//查询当前有多少个字符串
};

#endif // TRIE_H
