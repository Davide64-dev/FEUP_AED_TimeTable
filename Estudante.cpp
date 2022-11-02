//
// Created by Davide Teixeira on 19/10/2022.
//
#include <iostream>
#include <algorithm>
using namespace std;
#include "Estudante.h"

Estudante::Estudante(int i, string j, list<UcTurma> k): codigo(i), nome(j), horario(k){};

int Estudante::getcodigo() const{
    return codigo;
}

string Estudante::getnome()const{
    return nome;
}

list<UcTurma> Estudante::gethorario() const{
    return horario;
}

bool Estudante::operator<(Estudante student) const {
    return codigo < student.codigo;
}

bool Estudante::ordemAlfabética(Estudante student) const {
    if (nome == student.getnome()) {
        return codigo < student.getcodigo();
    }
    else return nome < student.getnome();
}

bool Estudante::ordemNumeroUcs(Estudante student) const {
    if (horario.size() == student.gethorario().size()){
        return codigo < student.getcodigo();
    }
    else return horario.size() < student.gethorario().size();
}

void Estudante::addUCTurma(UcTurma turma) {
    horario.push_back(turma);
}

bool Estudante::delUCTurma(UcTurma turma){
    UcTurma temp = turma;
    std::list<UcTurma>::iterator it;
    it = find(horario.begin(), horario.end(), turma);
    if (it != horario.end())
        horario.erase(it);
    else
        return false;
    return true;
}

bool Estudante::naTurma(UcTurma turma){
    for (UcTurma i : horario){
        if (i == turma){
            return true;
        }
    }
}

