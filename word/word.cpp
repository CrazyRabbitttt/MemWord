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
    json["str"] = str;              //��Sentence����Json
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

Meaning::operator Json::Value() const {
    Json::Value json;
    json["POS"] = partOfSpeech;     //����
    json["explain"] = explain;
            //�����е��������ת����json��ӽ�ȥ
    for (Sentence const& sentense : exampleList) {
        json["example"].append((Json::Value) sentense);
    }
}


WordDictInfo::WordDictInfo(Json::Value const& json) {
    word = json["word"].asString();
    pronunciation = json["pron"].asString();

    int const meaningSize = json["mean"].size();

    //���MeaningList��һ����һ��� Meaning -> Sentense ->string
    meaningList.resize(meaningSize);
    for (int i = 0; i < meaningSize; ++i) {
        //һ��Meaning����ͬ��Ҳ�ǰ����˺ܶ�����Ķ���,Vector�洢����Meaning��Ķ���
        meaningList[i] = Meaning(json["mean"][i]);
    }

    //���tagList
    int const tagSize = json["tag"].size();
    tagList.resize(tagSize);
    for (int i = 0; i < tagSize; ++i) {
        tagList[i] = json["tag"][i].asString();         //tag���ǵ�����String,��Meaning�಻ͬ
    }

    //�������(similarWord)
    int const similarSize = json["similar"].size();
    similarWordList.resize(similarSize);
    for (int i = 0; i < similarSize; ++i) {
        similarWordList[i] = json["similar"][i].asString();
    }

}

//��wordת����ΪJson�����ҷ��ص���JSON����
WordDictInfo::operator Json::Value() const {
    Json::Value json;
    json["word"] = word;
    json["pron"] = pronunciation;

    for (Meaning const& meaning : meaningList) {
        json["mean"].append((Json::Value)meaning);      //ת����ΪJson������ӵ�Json��
    }

    for (string const& tag : tagList) {
        json["tag"].append(tag);                        //������string������ת��
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

    //���Sentence
    const int noteSize = json["note"].size();
    noteList.resize(noteSize);
    for (int i = 0; i < noteList.size(); i++) {
        noteList[i] = json["note"][i].asString();
    }

    //���Tag��string��
    const int tagSize = json["tag"].size();
    userTagList.resize(tagSize);
    for (int i = 0; i < tagSize; ++i) {
        userTagList[i] = json["tag"][i].asString();
    }

    //���Sentence������str��trans��
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

    //���sentence��
    for (Sentence const & sentence : userSentenceList) {
        json["userSentence"].append((Json::Value) sentence);        //ת����ΪValue����
    }

    return json;
}



bool WordUserInfo::empty() const {
    //���ȫ�����ǿյĲŷ��ؿ�
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












