//
// Created by SGX on 2022/1/17.
//
#include "word.h"
#include <cctype>
#include <algorithm>

string toLower (string const& str)
{
    string s = str;
    //transform(��Ԫ�ص�������ĩβԪ�ص���������Ԫ�ص�����������);
    //std::transform(s.begin(), s.end(), s.begin(), (int (*)(int))tolower);
    for (int i = 0; i < s.size(); i++) s[i] = tolower(s[i]);
    return s;
}


//Sentence Meaning Word �� JSON��Value�Ļ���ת��


Sentence::Sentence(Json::Value const& json) {
    str = json["str"].asString();
    trans = json["trans"].asString();
}


Sentence::operator Json::Value () const             //��Sentenceת����ΪJson::Value ����
{
    Json::Value json;
    json["str"] = str;              //��Sentense����Json
    json["trans"] = trans;
    return json;
}


Meaning::Meaning(const Json::Value &json) {
    partOfSpeech = json["POS"].asString();                      //����
    explain = json["explain"].asString();                       //���Ľ���

    const int exampleSize = json["example"].size();
    exampleList.resize(exampleSize);

    for (int i = 0; i < exampleSize; i++) {
        exampleList[i] = Sentence(json["example"][i]);
    }
}













