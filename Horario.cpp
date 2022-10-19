//
// Created by Davide Teixeira on 19/10/2022.
//

#include <list>
#include "Horario.h"

Horario::Horario(string i, string j, list<Slot> k): codUC(i), codTurma(j), aulas(k){};

string Horario::getcodUC() const{
    return codUC;
}

string Horario::getcodTurma()const{
    return codTurma;
}

list<Slot> Horario::getaulas() const{
    return aulas;
}