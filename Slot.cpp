//
// Created by Davide Teixeira on 19/10/2022.
//

#include "Slot.h"

Slot::Slot(float i, float j, string k): horaini(i), duracao(j), tipo(k){};

float Slot::gethoraini() const{
    return horaini;
}

float Slot::getduaracao() const{
    return duracao;
}

string Slot::gettipo() const{
    return tipo;
}