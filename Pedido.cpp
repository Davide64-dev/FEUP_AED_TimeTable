//
// Created by Davide Teixeira on 22/10/2022.
//

#include <list>
#include "Pedido.h"
#include "Slot.h"

using namespace std;


int Pedido::getcodigo_estudante() const {
    return codigo_estudante;
}


//Retorna falso se houver sobreposicção de horários
bool Pedido::verifyOverlap(list<Slot> horario)  {
    filterTP(horario);
    for(auto it1 = horario.begin(); it1 != horario.end(); it1++) {
        auto it2 = it1;
        for(++it2; it2 != horario.end(); it2++) {
            if(it1->getDiaDaSemana() == it2->getDiaDaSemana()) {
                float start1 = it1->gethoraini(), start2 = it2->gethoraini();
                float end1 = start1 + it1->getduaracao(), end2 = start2 + it2->getduaracao();
                if(start2 < end1 && start1 < end2 ) return false;
            }
        }
    }

    return true;
}

void Pedido::filterTP(list<Slot> &horario) {
    auto it = horario.begin();
    while(it != horario.end()) {
        if(it->gettipo() != "TP") {
            it = horario.erase(it);
        } else {
            it++;
        }
    }
}

const string &Pedido::getTipo() const {
    return tipo;
}

Pedido::Pedido(const string &tipo, int codigoEstudante, const string &ucR, const vector<string> &turma) : tipo(
        tipo), codigo_estudante(codigoEstudante), turma(turma) {
    this->ucR.push_back(ucR);
}

Pedido::Pedido(const string &tipo, int codigoEstudante, const vector<string> &ucR, const vector<string> &ucA,
               const vector<string> &turma) : tipo(tipo), codigo_estudante(codigoEstudante), ucR(ucR), ucA(ucA),
               turma(turma) {}

const vector<string> &Pedido::getUcR() const {
    return ucR;
}

const vector<string> &Pedido::getUcA() const {
    return ucA;
}

const vector<string> &Pedido::getTurma() const {
    return turma;
}

