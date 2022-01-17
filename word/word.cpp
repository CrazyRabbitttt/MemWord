//
// Created by SGX on 2022/1/17.
//
#include "word.h"
#include <cctype>
#include <algorithm>

string toLower (string const& str)
{
    string s = str;
    //transform(首元素迭代器，末尾元素迭代器，首元素迭代器，函数);
    //std::transform(s.begin(), s.end(), s.begin(), (int (*)(int))tolower);
    for (int i = 0; i < s.size(); i++) s[i] = tolower(s[i]);
    return s;
}


//Sentence Meaning Word 和 JSON中Value的互相转换


Sentence::Sentence(Json::Value const& json) {
    str = json["str"].asString();
    trans = json["trans"].asString();
}


Sentence::operator Json::Value () const             //将Sentence转换成为Json::Value 类型
{
    Json::Value json;
    json["str"] = str;              //用Sentense构造Json
    json["trans"] = trans;
    return json;
}


Meaning::Meaning(const Json::Value &json) {
    partOfSpeech = json["POS"].asString();                      //词义
    explain = json["explain"].asString();                       //中文解释

    const int exampleSize = json["example"].size();
    exampleList.resize(exampleSize);

    for (int i = 0; i < exampleSize; i++) {
        exampleList[i] = Sentence(json["example"][i]);
    }
}













