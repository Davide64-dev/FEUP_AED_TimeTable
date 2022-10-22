//
// Created by Davide Teixeira on 22/10/2022.
//

#ifndef UNTITLED3_PEDIDOINDIVIDUAL_H
#define UNTITLED3_PEDIDOINDIVIDUAL_H

#include <string>

using namespace std;

class PedidoIndividual {
    string UC;
    string codTurma1;
    string codTurma2;
public:
    PedidoIndividual(string i, string j, string k);
    string getUC() const;
    string getcodTurma1() const;
    string getcodTurma2() const;
};


#endif //UNTITLED3_PEDIDOINDIVIDUAL_H
