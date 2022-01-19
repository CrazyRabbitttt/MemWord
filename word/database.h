//
// Created by SGX on 2022/1/19.
//

#ifndef WORD_DATABASE_H
#define WORD_DATABASE_H

#include <iostream>
#include <vector>
#include <functional>           //����ʵ�ֺ��������ͷ�ļ�
#include <map>
#include "word.h"

using std::vector;
using std::function;
using std::istream;
using std::ostream;

//static -> internalֻ���Ǳ��ļ�ʹ��     lambda�հ����
static const auto alwaysTrue = [](WordInfo const&) {
    return true;
};

//���ʵ����ݿ�ӿ�
//�ʿ���Ϣ�Ĵ�ȡ
//�û���Ϣ�Ĵ�ȡ�����
//��һ���ַ�������һ������
//��һ��filter������������Ҫ������еĵ���
class DataBase
{
public:

    virtual ~DataBase() {}              //�麯�������������д��
    //�����ж�ȡ�û�����Ϣ
    virtual void loadUserInfo (istream&) = 0;
    //�����б����û�����Ϣ
    virtual void saveUserInfo (ostream&) const = 0;
    //����û�����Ϣ
    virtual void clearUserInfo() = 0;
    //�����ж�ȡ�ʵ����Ϣ
    virtual void loadDictInfo(istream &) = 0;
    //������д��ʵ���Ϣ��һ�㲻����
    virtual void saveDictInfo(ostream &) = 0;

    //��������Ҫ��ĵ��ʵ��б�,ָ������
    virtual vector<WordInfo*> getWordList(function<bool(WordInfo const&)> = alwaysTrue) const = 0;
    virtual vector<const WordInfo*> getWordListConst ( function<bool(WordInfo const&)> = alwaysTrue ) const = 0;

    //�����ַ����ҵ��ʣ��ַ����ϸ�match
    virtual WordInfo* getWord (string const&) const = 0;
    //�����ݿ��м��뵥��
    virtual void addWord(WordInfo* ) = 0;

};

//�������ݿ�ʵ�ֵ���
class DataBaseImpl:public DataBase
{
protected:
    //���ݵ����ַ�������WordInfoָ��
    std::map<string, WordInfo*>     stringToWordPtr;

public:
    ~DataBaseImpl();

    //ʵ�ֽӿ�
    virtual void loadUserInfo (istream&);
    virtual void saveUserInfo (ostream&) const;
    virtual void clearUserInfo ();
    virtual void loadDictInfo (istream&);
    virtual void saveDictInfo (ostream&) const;
    virtual vector<WordInfo*> getWordList ( function<bool(WordInfo const&)> ) const;
    virtual vector<const WordInfo*> getWordListConst ( function<bool(WordInfo const&)> ) const;
    virtual WordInfo* getWord (string const&) const;
    virtual void addWord (WordInfo*);

};

#endif //WORD_DATABASE_H
