//
// Created by Davide Teixeira on 22/10/2022.
//

#include "Gestor.h"

Gestor::Gestor(set<Estudante> i , vector<Horario> j, queue<Pedido> k): estudantes(), horario(j), pedidos(k){};

//set<Estudante> Gestor::getEstudantes() const{
//    return estudantes;
//}

vector<Horario> Gestor::getHorario() const{
    return horario;
}

queue<Pedido> Gestor::getPedidos() const{
    return pedidos;
}