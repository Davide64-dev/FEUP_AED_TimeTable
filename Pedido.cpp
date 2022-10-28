//
// Created by Davide Teixeira on 22/10/2022.
//

#include <list>
#include "Pedido.h"
#include "Slot.h"

using namespace std;

Pedido::Pedido(int i, list<PedidoIndividual> j): codigo_estudante(i), pedidos(j){};

int Pedido::getcodigo_estudante() const {
    return codigo_estudante;
}

list<PedidoIndividual> Pedido::getpedidos()const{
    return pedidos;
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