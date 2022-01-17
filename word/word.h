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
    string trans;       //����(����)

    Sentence() = default;
    Sentence(Json::Value const&);
    operator Json::Value() const;       //��Sentenceת����ΪValue
    friend istream &operator >> (istream&, Sentence&);              //����
    friend ostream &operator << (ostream&, Sentence const&);        //���const

};


struct Meaning
{
    string partOfSpeech;                //����
    string explain;                     //���Ľ���
    vector<Sentence> exampleList;       //�����б�

    Meaning() = default;
    Meaning(Json::Value const &);
    operator Json::Value()const;
    friend istream & operator >> (istream&, Meaning&);
    friend ostream & operator << (ostream&, Meaning const&);        //Meaning�ǲ��ɸ��ĵ�

};

//һ�����ʵ���Ϣ
struct WordDictInfo
{
    string              word;                   //���ʻ��ߴ���
    string              pronunciation;          //����
    vector<Meaning>     meaningList;            //������˼,Meaning�����
    vector<string>      similarWordList;        //������б�
    vector<string>      tagList;                //��ǩ�б����������ߡ�����

    //���õ���Json���д����
    WordDictInfo() = default;
    WordDictInfo (Json::Value const&);
    operator Json::Value()const;
    friend istream &operator >> (istream&, WordDictInfo&);
    friend ostream &operator << (ostream&, WordDictInfo const &);

};

struct WordUserInfo         //�û����ڵ��ʵ���Ϣ
{
    string              userWord;           //Ӣ�ĵ���
    vector<string>      noteList;           //�û����ıʼ�
    vector<string>      userTagList;        //�û����ı�ǩ
    vector<Sentence>    userSentenceList;   //�û���������
    int                 rememberLevel;      //�����ȼ�
    clock_t             lastTestTime;       //��һ��testʱ��


    WordUserInfo();
    WordUserInfo(Json::Value const&);
    operator Json::Value () const;
    friend istream& operator >> (istream&, WordUserInfo&);
    friend ostream& operator << (ostream&, WordUserInfo const&);
    bool empty() const;
};

struct WordInfo:public WordDictInfo,public WordUserInfo
{
    //�̳��������࣬�û��Ե��ʵ������Ϣ�����ʱ������Ϣ
    //���캯������������Ϣ
    WordInfo(WordDictInfo const& dictInfo, WordUserInfo const & userInfo)
        :WordDictInfo(dictInfo), WordUserInfo(userInfo){}

    bool empty() const = delete;    //��ֹʹ��empty��������ת��ΪWordUserInfo
    void clearUserInfo();
};

string toLower (string const &);

static const string WORD_PART_OF_SPEECH[] = {"n", "v", "a", "ad", "pron", "vi", "num", "vt", "int", "prep", "conj", "phr"};//pron
static const string WORD_TAG[] = {"junior", "senior", "CET4", "CET6", "TOEFL", "GRE"};
static const int WORD_LEVEL_MAX = 7;


#endif //WORD_WORD_H
