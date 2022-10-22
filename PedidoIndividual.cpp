//
// Created by Davide Teixeira on 22/10/2022.
//

#include "PedidoIndividual.h"

PedidoIndividual::PedidoIndividual(string i, string j, string k): UC(i), codTurma1(j), codTurma2(k){};

string PedidoIndividual::getUC() const{
    return UC;
}

string PedidoIndividual::getcodTurma1()const{
    return codTurma1;
}

string PedidoIndividual::getcodTurma2() const{
    return codTurma2;
}