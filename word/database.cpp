//
// Created by SGX on 2022/1/20.
//


#include "database.h"


DataBaseImpl::~DataBaseImpl()  {
    //实现析构函数
    //pair中 first : string     second : WordInfo*    用字符串索引单词
    for (auto const& each : stringToWordPtr)
        delete each.second;
}

//从一个输入流读取用户的信息
void DataBaseImpl::loadUserInfo(istream &in) {
    Json::Reader reader;
    Json::Value root;
    reader.parse(in,root);      //json函数，从输入流中读取数据Value中

    clearUserInfo();                //因为已经是读取成功了，将原来的进行清除

    //肯定是将JSON转换成为类的值
    //Map string（word） ， WordInfo
    int const wordSize = root.size();
    for (int i = 0; i < wordSize; ++i) {
        string const wordString  = root[i]["word"].asString();      //获取word索引WordInfo
        if (stringToWordPtr[wordString] == nullptr)
            std::cerr << "Sorry, DataBase: No this word in dictionary: "<< wordString << std::endl;
        else {
            //存在WordInfo， 那么存储？
            WordUserInfo& userInfo = *stringToWordPtr[wordString];      //原先的引用，用子类初始化父类
            userInfo = WordUserInfo(root[i]);           //此时已经更改了原先的userInfo
        }
    }
}

//向输出流中保存用户的信息
void DataBaseImpl::saveUserInfo(ostream &out) const {
    Json::Value root;
    for (auto const & pair : stringToWordPtr)
    {
        WordDictInfo const & dictInfo = *pair.second;
        WordUserInfo & userInfo = *pair.second;
        if (!userInfo.empty()) {        //用户信息不为空
            userInfo.userWord = dictInfo.word;
            root.append((Json::Value)userInfo);
        }
    }
    out << root;
}

void DataBaseImpl::clearUserInfo() {
        //调用WordInfo中的清除用户信息函数
        for (auto & pair : stringToWordPtr) {
            pair.second->clearUserInfo();
        }
}

//从输入流中读取单词的信息
void DataBaseImpl::loadDictInfo(istream &in) {
    Json::Value  root;
    Json::Reader  reader;
    reader.parse(in, root);

    stringToWordPtr.clear();

    int const wordSize = root.size();
    for (int i = 0; i < wordSize; ++i) {
        //root[i]["word"]就是单词
        WordInfo* ptr = new WordInfo(WordDictInfo(root[i]), WordUserInfo(root[i]));
        stringToWordPtr[ptr->word] = ptr;
    }
}

void DataBaseImpl::saveDictInfo(ostream &out) const {
    Json::Value root;
    for (auto const & pair : stringToWordPtr)
        root.append((Json::Value)(WordDictInfo &) (*pair.second));
        //转成Value                     转成父类            解引用得到map  调用map.second
    out << root;
}

vector<const WordInfo*>DataBaseImpl::getWordListConst(function<bool(const WordInfo &)> f) const {
    //从map中获取信息，转成vector
    vector<const WordInfo*> words;
    for (auto iter = stringToWordPtr.begin(); iter != stringToWordPtr.end(); iter++) {
        if (f(*(iter->second)))         //如果WordInfo是？
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


//从数据库中查询单词
WordInfo* DataBaseImpl::getWord(const string &str) const {
    auto it = stringToWordPtr.find(str);
    return it == stringToWordPtr.end() ? nullptr : it->second;
    //如果是检查到了最后一个了，那么肯定是没有了，返回null
    //如果检查到的不是，那么就返回->second
}


void DataBaseImpl::addWord(WordInfo *word) {
    string stringWord1 = word->word;
    stringToWordPtr.insert(std::make_pair(stringWord1, word));
}







