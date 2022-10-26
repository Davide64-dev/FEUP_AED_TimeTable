//
// Created by Davide Teixeira on 19/10/2022.
//

#ifndef UNTITLED3_UCTURMA_H
#define UNTITLED3_UCTURMA_H

using namespace std;

class UcTurma {
    string codUC;
    string codTurma;
    int Cap;
public:
    UcTurma(string i, string j);
    string getcodUC() const;
    string getcodTurma() const;
    bool operator== (const UcTurma &other) const;
    bool operator< (const UcTurma &other) const;
    void print();
};


#endif //UNTITLED3_UCTURMA_H
