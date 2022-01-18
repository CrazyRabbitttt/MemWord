//
// Created by SGX on 2022/1/18.
//

#include "word.h"

//实现三个类的输入和输出


istream & operator >> (istream &in, Sentence &s)
{
    //Sentence :str & trans
    std::getline(in, s.str, '|');       //用'|'进行隔断读取， 如果不加则以'\n'为分隔
    std::getline(in, s.trans, '|');
    return in;
}

ostream & operator << (ostream & out, Sentence const & sentence) {
     out << sentence.str << '|' << sentence.trans << '|';
     return out;
}

istream & operator >> (istream & in, Meaning  & m) {
    std::getline(in, m.partOfSpeech, '|');      //语义
    std::getline(in, m.explain, '|');           //解释
    //输入Sentence
   // std::cout << "输入n和'|'\n";
    int n;char c;
    in >> n >> c;
    m.exampleList.resize(n);
    for (int i = 0; i < n; i++) {
        in >> m.exampleList[i];             //还是进行的Sentence的读取，但是上面已经是写好了
    }
    return in;
}
ostream & operator << (ostream & out, Meaning const &m) {
    out << m.partOfSpeech << '|';
    out << m.explain << '|';
    out << m.exampleList.size() << '|';
    for (auto & each : m.exampleList) {
        out << each;
    }
    return out;
}














