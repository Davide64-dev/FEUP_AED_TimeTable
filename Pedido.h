//
// Created by Davide Teixeira on 22/10/2022.
//

#ifndef UNTITLED3_PEDIDO_H
#define UNTITLED3_PEDIDO_H


#include "PedidoIndividual.h"
#include "Slot.h"

using namespace std;

class Pedido {
    int codigo_estudante;
    list<PedidoIndividual> pedidos;
public:
    Pedido(int i, list<PedidoIndividual> j);
    int getcodigo_estudante() const;
    list<PedidoIndividual> getpedidos() const;
    bool verifyOverlap(list<Slot> horario);
    void filterTP(list<Slot> &horario);
};



#endif //UNTITLED3_PEDIDO_H
