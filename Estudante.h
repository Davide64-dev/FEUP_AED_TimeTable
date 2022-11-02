//
// Created by Davide Teixeira on 19/10/2022.
//

#ifndef UNTITLED3_ESTUDANTE_H
#define UNTITLED3_ESTUDANTE_H

#include <string>
#include <list>
#include "UcTurma.h"
using namespace std;

class Estudante {
    int codigo;
    string nome;
    list<UcTurma> horario;
public:
    Estudante(int i, string j, list<UcTurma> k);
    int getcodigo() const;
    string getnome() const;
    list<UcTurma> gethorario() const;
    bool operator<(Estudante student) const;
    void addUCTurma(UcTurma turma);
    bool delUCTurma(UcTurma turma);
    bool naTurma(UcTurma turma);
    bool ordemAlfabética(Estudante student) const;
    bool ordemNumeroUcs(Estudante student) const;
};


#endif //UNTITLED3_ESTUDANTE_H
