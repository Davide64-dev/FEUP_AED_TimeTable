//
// Created by Davide Teixeira on 19/10/2022.
//

#ifndef UNTITLED3_HORARIO_H
#define UNTITLED3_HORARIO_H

#include <string>
#include "Slot.h"

using namespace std;

class Horario {
    string codUC;
    string codTurma;
    list<Slot> aulas;
    int numEstudantes = 0;
public:
    int getNumEstudantes() const;

    void setNumEstudantes(int numEstudantes);

public:
    Horario(string i, string j, list<Slot> k);
    Horario(string codUC, string codTurma);
    string getcodUC() const;
    string getcodTurma() const;
    list<Slot> getaulas() const;
    void addAula(Slot aula);
};

#endif //UNTITLED3_HORARIO_H
