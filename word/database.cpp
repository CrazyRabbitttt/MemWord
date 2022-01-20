//
// Created by SGX on 2022/1/20.
//


#include "database.h"


DataBaseImpl::~DataBaseImpl()  {
    //ʵ����������
    //pair�� first : string     second : WordInfo*    ���ַ�����������
    for (auto const& each : stringToWordPtr)
        delete each.second;
}

//��һ����������ȡ�û�����Ϣ
void DataBaseImpl::loadUserInfo(istream &in) {
    Json::Reader reader;
    Json::Value root;
    reader.parse(in,root);      //json���������������ж�ȡ����Value��

    clearUserInfo();                //��Ϊ�Ѿ��Ƕ�ȡ�ɹ��ˣ���ԭ���Ľ������

    //�϶��ǽ�JSONת����Ϊ���ֵ
    //Map string��word�� �� WordInfo
    int const wordSize = root.size();
    for (int i = 0; i < wordSize; ++i) {
        string const wordString  = root[i]["word"].asString();      //��ȡword����WordInfo
        if (stringToWordPtr[wordString] == nullptr)
            std::cerr << "Sorry, DataBase: No this word in dictionary: "<< wordString << std::endl;
        else {
            //����WordInfo�� ��ô�洢��
            WordUserInfo& userInfo = *stringToWordPtr[wordString];      //ԭ�ȵ����ã��������ʼ������
            userInfo = WordUserInfo(root[i]);           //��ʱ�Ѿ�������ԭ�ȵ�userInfo
        }
    }
}

//��������б����û�����Ϣ
void DataBaseImpl::saveUserInfo(ostream &out) const {
    Json::Value root;
    for (auto const & pair : stringToWordPtr)
    {
        WordDictInfo const & dictInfo = *pair.second;
        WordUserInfo & userInfo = *pair.second;
        if (!userInfo.empty()) {        //�û���Ϣ��Ϊ��
            userInfo.userWord = dictInfo.word;
            root.append((Json::Value)userInfo);
        }
    }
    out << root;
}

void DataBaseImpl::clearUserInfo() {
        //����WordInfo�е�����û���Ϣ����
        for (auto & pair : stringToWordPtr) {
            pair.second->clearUserInfo();
        }
}

//���������ж�ȡ���ʵ���Ϣ
void DataBaseImpl::loadDictInfo(istream &in) {
    Json::Value  root;
    Json::Reader  reader;
    reader.parse(in, root);

    stringToWordPtr.clear();

    int const wordSize = root.size();
    for (int i = 0; i < wordSize; ++i) {
        //root[i]["word"]���ǵ���
        WordInfo* ptr = new WordInfo(WordDictInfo(root[i]), WordUserInfo(root[i]));
        stringToWordPtr[ptr->word] = ptr;
    }
}

void DataBaseImpl::saveDictInfo(ostream &out) const {
    Json::Value root;
    for (auto const & pair : stringToWordPtr)
        root.append((Json::Value)(WordDictInfo &) (*pair.second));
        //ת��Value                     ת�ɸ���            �����õõ�map  ����map.second
    out << root;
}

vector<const WordInfo*>DataBaseImpl::getWordListConst(function<bool(const WordInfo &)> f) const {
    //��map�л�ȡ��Ϣ��ת��vector
    vector<const WordInfo*> words;
    for (auto iter = stringToWordPtr.begin(); iter != stringToWordPtr.end(); iter++) {
        if (f(*(iter->second)))         //���WordInfo�ǣ�
        {
            words.push_back(iter->second);
        }
    }
    return words;
}


vector<WordInfo*> DataBaseImpl::getWordList(function<bool(const WordInfo & )>f) const {
    vector<WordInfo*> words;
    for(auto iter = stringToWordPtr.begin(); iter != stringToWordPtr.end(); iter ++)
    {
        if (f(*(iter -> second)))
        {
            words.push_back(iter -> second);
        }
    }
    return words;
}


//�����ݿ��в�ѯ����
WordInfo* DataBaseImpl::getWord(const string &str) const {
    auto it = stringToWordPtr.find(str);
    return it == stringToWordPtr.end() ? nullptr : it->second;
    //����Ǽ�鵽�����һ���ˣ���ô�϶���û���ˣ�����null
    //�����鵽�Ĳ��ǣ���ô�ͷ���->second
}


void DataBaseImpl::addWord(WordInfo *word) {
    string stringWord1 = word->word;
    stringToWordPtr.insert(std::make_pair(stringWord1, word));
}







