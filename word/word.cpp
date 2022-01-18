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
    json["str"] = str;              //用Sentence构造Json
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

Meaning::operator Json::Value() const {
    Json::Value json;
    json["POS"] = partOfSpeech;     //语义
    json["explain"] = explain;
            //将所有的样例语句转换成json添加进去
    for (Sentence const& sentense : exampleList) {
        json["example"].append((Json::Value) sentense);
    }
}


WordDictInfo::WordDictInfo(Json::Value const& json) {
    word = json["word"].asString();
    pronunciation = json["pron"].asString();

    int const meaningSize = json["mean"].size();

    //填充MeaningList，一层套一层的 Meaning -> Sentense ->string
    meaningList.resize(meaningSize);
    for (int i = 0; i < meaningSize; ++i) {
        //一个Meaning类中同样也是包含了很多种类的对象,Vector存储的是Meaning类的对象
        meaningList[i] = Meaning(json["mean"][i]);
    }

    //填充tagList
    int const tagSize = json["tag"].size();
    tagList.resize(tagSize);
    for (int i = 0; i < tagSize; ++i) {
        tagList[i] = json["tag"][i].asString();         //tag就是单纯的String,与Meaning类不同
    }

    //填充近义词(similarWord)
    int const similarSize = json["similar"].size();
    similarWordList.resize(similarSize);
    for (int i = 0; i < similarSize; ++i) {
        similarWordList[i] = json["similar"][i].asString();
    }

}

//将word转换成为Json对象并且返回的是JSON对象
WordDictInfo::operator Json::Value() const {
    Json::Value json;
    json["word"] = word;
    json["pron"] = pronunciation;

    for (Meaning const& meaning : meaningList) {
        json["mean"].append((Json::Value)meaning);      //转换成为Json类型添加到Json中
    }

    for (string const& tag : tagList) {
        json["tag"].append(tag);                        //单纯的string，不用转换
    }

    for (string const& similar : similarWordList) {
        json["similar"].append(similar);
    }
    return json;
}

//default : 0
WordUserInfo::WordUserInfo()
    :rememberLevel(0), lastTestTime(0) {}

WordUserInfo::WordUserInfo(const Json::Value &json) {
    userWord = json["word"].asString();
    rememberLevel = json["level"].asInt();
    lastTestTime = json["lasttime"].asInt();

    //填充Sentence
    const int noteSize = json["note"].size();
    noteList.resize(noteSize);
    for (int i = 0; i < noteList.size(); i++) {
        noteList[i] = json["note"][i].asString();
    }

    //填充Tag（string）
    const int tagSize = json["tag"].size();
    userTagList.resize(tagSize);
    for (int i = 0; i < tagSize; ++i) {
        userTagList[i] = json["tag"][i].asString();
    }

    //填充Sentence（包含str和trans）
    const int sentenceSize = json["userSentence"].size();
    userSentenceList.resize(sentenceSize);
    for (int i = 0; i < sentenceSize; ++i) {
        userSentenceList[i] = json["userSentence"][i];
    }
}

WordUserInfo::operator Json::Value() const {
    Json::Value json;
    json["word"] = userWord;
    json["level"] = rememberLevel;
    json["lasttime"] = (int)lastTestTime;
    for (string const & note : noteList) {
        json["note"].append(note);
    }

    for (string const & tag : userTagList) {
        json["userTag"].append(tag);
    }

    //填充sentence类
    for (Sentence const & sentence : userSentenceList) {
        json["userSentence"].append((Json::Value) sentence);        //转换成为Value类型
    }

    return json;
}



bool WordUserInfo::empty() const {
    //如果全部都是空的才返回空
    return noteList.empty() && userTagList.empty() && userSentenceList.empty() &&
    rememberLevel == 0 && lastTestTime == 0;
}


void WordInfo::clearUserInfo() {
    userWord.clear();
    noteList.clear();
    userTagList.clear();
    userSentenceList.clear();
    rememberLevel = 0;
    lastTestTime = 0;
}












