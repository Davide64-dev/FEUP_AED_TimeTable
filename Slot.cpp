//
// Created by Davide Teixeira on 19/10/2022.
//

#include "Slot.h"

Slot::Slot(float horaini, float duracao, const string &diaDaSemana, const string &tipo) : horaini(horaini),
                                                                                          duracao(duracao),
                                                                                          diaDaSemana(diaDaSemana),
                                                                                          tipo(tipo) {}

float Slot::gethoraini() const{
    return horaini;
}

float Slot::getduaracao() const{
    return duracao;
}

string Slot::gettipo() const{
    return tipo;
}

const string &Slot::getDiaDaSemana() const {
    return diaDaSemana;
}

