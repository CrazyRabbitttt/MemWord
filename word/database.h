//
// Created by SGX on 2022/1/19.
//

#ifndef WORD_DATABASE_H
#define WORD_DATABASE_H

#include <iostream>
#include <vector>
#include <functional>           //用于实现函数对象的头文件
#include <map>
#include "word.h"

using std::vector;
using std::function;
using std::istream;
using std::ostream;

//static -> internal只能是本文件使用     lambda闭包语句
static const auto alwaysTrue = [](WordInfo const&) {
    return true;
};

//单词的数据库接口
//词库信息的存取
//用户信息的存取与清空
//用一个字符串索引一个单词
//用一个filter函数查找满足要求的所有的单词
class DataBase
{
public:

    virtual ~DataBase() {}              //虚函数，子类必须重写？
    //从流中读取用户的信息
    virtual void loadUserInfo (istream&) = 0;
    //向流中保存用户的信息
    virtual void saveUserInfo (ostream&) const = 0;
    //清除用户的信息
    virtual void clearUserInfo() = 0;
    //从流中读取词典的信息
    virtual void loadDictInfo(istream &) = 0;
    //向流中写入词典信息，一般不调用
    virtual void saveDictInfo(ostream &) = 0;

    //返回满足要求的单词的列表,指针数组
    virtual vector<WordInfo*> getWordList(function<bool(WordInfo const&)> = alwaysTrue) const = 0;
    virtual vector<const WordInfo*> getWordListConst ( function<bool(WordInfo const&)> = alwaysTrue ) const = 0;

    //根据字符查找单词，字符串严格match
    virtual WordInfo* getWord (string const&) const = 0;
    //向数据库中加入单词
    virtual void addWord(WordInfo* ) = 0;

};

//单词数据库实现的类
class DataBaseImpl:public DataBase
{
protected:
    //根据单词字符串索引WordInfo指针
    std::map<string, WordInfo*>     stringToWordPtr;

public:
    ~DataBaseImpl();

    //实现接口
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
