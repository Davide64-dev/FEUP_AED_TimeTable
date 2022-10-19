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
public:
    Horario(string i, string j, list<Slot> k);
    string getcodUC() const;
    string getcodTurma() const;
    list<Slot> getaulas() const;
};

#endif //UNTITLED3_HORARIO_H
