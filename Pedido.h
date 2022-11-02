//
// Created by Davide Teixeira on 22/10/2022.
//

#ifndef UNTITLED3_PEDIDO_H
#define UNTITLED3_PEDIDO_H


#include "PedidoIndividual.h"
#include "Slot.h"
#include <vector>

using namespace std;

class Pedido {
protected:
    string tipo;
    int codigo_estudante;
    vector<string> ucR;
    vector<string> ucA;
    vector<string> turma;
    int CAP = 30;
public:
    Pedido(const string &tipo, int codigoEstudante, const string &ucR, const vector<string> &turma);

    Pedido(const string &tipo, int codigoEstudante, const vector<string> &ucR, const vector<string> &ucA,
           const vector<string> &turma);

    int getcodigo_estudante() const;

    const vector<string> &getUcR() const;

    const vector<string> &getUcA() const;

    const vector<string> &getTurma() const;

    bool verifyOverlap(list<Slot> horario);

    void filterTP(list<Slot> &horario);

    const string &getTipo() const;
};



#endif //UNTITLED3_PEDIDO_H
