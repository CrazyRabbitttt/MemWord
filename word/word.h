//
// Created by SGX on 2022/1/17.
//

#ifndef WORD_WORD_H
#define WORD_WORD_H



#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "json/json.h"

using std::string;
using std::vector;
using std::istream;
using std::ostream;


struct Sentence
{
    string str;
    string trans;       //翻译(中文)

    Sentence() = default;
    Sentence(Json::Value const&);
    operator Json::Value() const;       //将Sentence转换成为Value
    friend istream &operator >> (istream&, Sentence&);              //输入
    friend ostream &operator << (ostream&, Sentence const&);        //输出const

};


struct Meaning
{
    string partOfSpeech;                //词性
    string explain;                     //中文解释
    vector<Sentence> exampleList;       //例句列表

    Meaning() = default;
    Meaning(Json::Value const &);
    operator Json::Value()const;
    friend istream & operator >> (istream&, Meaning&);
    friend ostream & operator << (ostream&, Meaning const&);        //Meaning是不可更改的

};

//一个单词的信息
struct WordDictInfo
{
    string              word;                   //单词或者词组
    string              pronunciation;          //发音
    vector<Meaning>     meaningList;            //各种意思,Meaning类对象
    vector<string>      similarWordList;        //近义词列表
    vector<string>      tagList;                //标签列表：四六级或者。。。

    //利用的是Json库读写单词
    WordDictInfo() = default;
    WordDictInfo (Json::Value const&);
    operator Json::Value()const;
    friend istream &operator >> (istream&, WordDictInfo&);
    friend ostream &operator << (ostream&, WordDictInfo const &);

};

struct WordUserInfo         //用户对于单词的信息
{
    string              userWord;           //英文单词
    vector<string>      noteList;           //用户做的笔记
    vector<string>      userTagList;        //用户做的标签
    vector<Sentence>    userSentenceList;   //用户做的例句
    int                 rememberLevel;      //熟练等级
    clock_t             lastTestTime;       //上一次test时间


    WordUserInfo();
    WordUserInfo(Json::Value const&);
    operator Json::Value () const;
    friend istream& operator >> (istream&, WordUserInfo&);
    friend ostream& operator << (ostream&, WordUserInfo const&);
    bool empty() const;
};

struct WordInfo:public WordDictInfo,public WordUserInfo
{
    //继承了两个类，用户对单词的添加信息，单词本身的信息
    //构造函数，传两个信息
    WordInfo(WordDictInfo const& dictInfo, WordUserInfo const & userInfo)
        :WordDictInfo(dictInfo), WordUserInfo(userInfo){}

    bool empty() const = delete;    //禁止使用empty，必须先转换为WordUserInfo
    void clearUserInfo();
};

string toLower (string const &);

static const string WORD_PART_OF_SPEECH[] = {"n", "v", "a", "ad", "pron", "vi", "num", "vt", "int", "prep", "conj", "phr"};//pron
static const string WORD_TAG[] = {"junior", "senior", "CET4", "CET6", "TOEFL", "GRE"};
static const int WORD_LEVEL_MAX = 7;


#endif //WORD_WORD_H
