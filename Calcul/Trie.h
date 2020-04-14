#ifndef TRIE_H
#define TRIE_H

#include <string>

//�ֵ����Ľ��
class TrieNode{
public:
    TrieNode *son[20];//�ֵ����Ķ���
    int cnt;//��¼�Ƿ����һ���ַ���,�ѵ�ǰ�����Ϊ���Ľ��
    TrieNode();//���췽��
};

//�ֵ���
class Trie{
private:
    TrieNode *rt;//����
    int cnt;//��ǰ���˶��ٸ��ַ���
public:
    Trie();//���췽��
    int value(char c);//�������ַ�����һ��ֵ
    void insert(std::string str);//����һ���ַ���
    bool count(std::string str);//��ѯ�Ƿ����ĳ�ַ���
    int size();//��ѯ��ǰ�ж��ٸ��ַ���
};

#endif // TRIE_H
