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


const string &Pedido::getTipo() const {
    return tipo;
}

Pedido::Pedido(const string &tipo, int codigoEstudante, const string &turmaR, const string &uc) : tipo(tipo),
    codigo_estudante(codigoEstudante) {
    this->turmaR.push_back(turmaR);
    this->ucs.push_back(uc);
}

Pedido::Pedido(const string &tipo, int codigoEstudante, const vector<string> &turmaR, const vector<string> &turmaA,
               const vector<string> &ucs) : tipo(tipo), codigo_estudante(codigoEstudante), turmaR(turmaR),
               turmaA(turmaA), ucs(ucs) {}

const vector<string> &Pedido::getTurmaR() const {
    return turmaR;
}

const vector<string> &Pedido::getTurmaA() const {
    return turmaA;
}

const vector<string> &Pedido::getUCs() const {
    return ucs;
}

