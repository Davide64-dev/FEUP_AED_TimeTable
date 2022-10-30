//
// Created by Davide Teixeira on 19/10/2022.
//

#include <list>
#include "Horario.h"

Horario::Horario(string i, string j, list<Slot> k): codUC(i), codTurma(j), aulas(k){};

Horario::Horario(string codUC, string codTurma) {
    this->codUC = codUC;
    this->codTurma = codTurma;
    aulas.clear();
}

string Horario::getcodUC() const{
    return codUC;
}

string Horario::getcodTurma()const{
    return codTurma;
}

list<Slot> Horario::getaulas() const{
    return aulas;
}

void Horario::addAula(Slot aula) {
    aulas.push_back(aula);
}

int Horario::getNumEstudantes() const {
    return numEstudantes;
}

void Horario::setNumEstudantes(int numEstudantes) {
    Horario::numEstudantes = numEstudantes;
}

bool Horario::operator<(Horario horario) const{
    if (codUC == horario.getcodUC()){
        return codTurma < horario.getcodTurma();
    }
    else return codUC < horario.getcodUC();

}
bool Horario::operator==(Horario horario) const {

    return ((codUC == horario.getcodUC()) and (codTurma == horario.getcodTurma()));

}


