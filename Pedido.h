//
// Created by Davide Teixeira on 22/10/2022.
//

#ifndef UNTITLED3_PEDIDO_H
#define UNTITLED3_PEDIDO_H


#include "Slot.h"
#include <vector>

using namespace std;

class Pedido {
    string tipo;
    int codigo_estudante;
    vector<string> turmaR;
    vector<string> turmaA;
    vector<string> ucs;
    int CAP = 30;
public:
    Pedido(const string &tipo, int codigoEstudante, const string &turmaR, const string &uc);

    Pedido(const string &tipo, int codigoEstudante, const vector<string> &turmaR, const vector<string> &turmaA,
           const vector<string> &ucs);

    int getcodigo_estudante() const;

    const vector<string> &getTurmaR() const;

    const vector<string> &getTurmaA() const;

    const vector<string> &getUCs() const;

    const string &getTipo() const;
};



#endif //UNTITLED3_PEDIDO_H
