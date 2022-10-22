//
// Created by Davide Teixeira on 22/10/2022.
//

#include <list>
#include "Pedido.h"
using namespace std;

Pedido::Pedido(int i, list<PedidoIndividual> j): codigo_estudante(i), pedidos(j){};

int Pedido::getcodigo_estudante() const {
    return codigo_estudante;
}

list<PedidoIndividual> Pedido::getpedidos()const{
    return pedidos;
}
