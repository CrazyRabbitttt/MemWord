//
// Created by SGX on 2022/1/18.
//

#include "word.h"

//ʵ�����������������


istream & operator >> (istream &in, Sentence &s)
{
    //Sentence :str & trans
    std::getline(in, s.str, '|');       //��'|'���и��϶�ȡ�� �����������'\n'Ϊ�ָ�
    std::getline(in, s.trans, '|');
    return in;
}

ostream & operator << (ostream & out, Sentence const & sentence) {
     out << sentence.str << '|' << sentence.trans << '|';
     return out;
}

istream & operator >> (istream & in, Meaning  & m) {
    std::getline(in, m.partOfSpeech, '|');      //����
    std::getline(in, m.explain, '|');           //����
    //����Sentence
   // std::cout << "����n��'|'\n";
    int n;char c;
    in >> n >> c;
    m.exampleList.resize(n);
    for (int i = 0; i < n; i++) {
        in >> m.exampleList[i];             //���ǽ��е�Sentence�Ķ�ȡ�����������Ѿ���д����
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














