//
// Created by Davide Teixeira on 19/10/2022.
//

#include "Estudante.h"

Estudante::Estudante(int i, string j, list<UcTurma> k): codigo(i), nome(j), horario(k){};

int Estudante::getcodigo() const{
    return codigo;
}

string Estudante::getnome()const{
    return nome;
}

list<UcTurma> Estudante::gethorario(){
    return horario;
}

bool Estudante::operator<(Estudante student) const {
    return codigo < student.codigo;
}

void Estudante::addUCTurma(UcTurma turma) {
    horario.push_back(turma);
}