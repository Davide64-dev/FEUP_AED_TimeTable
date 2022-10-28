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

int Slot::correspondencia(string dia){

    if (dia == "Monday") return 0;
    else if (dia == "Tuesday") return 1;
    else if (dia == "Wednesday") return 2;
    else if (dia == "Thursday") return 3;
    else if (dia == "Friday") return 4;
    else if (dia == "Saturday") return 5;
    else if (dia == "Sunday") return 6;
    else return -1;

}


bool diaMenor(string dia1, string dia2){
    if ((Slot::correspondencia(dia1) == -1) or (Slot::correspondencia(dia2) == -1)) return false;
    else return (Slot::correspondencia(dia1) < Slot::correspondencia(dia2));
}


bool Slot::operator<(Slot slot) const {
    if (diaDaSemana == slot.getDiaDaSemana()){
        return horaini < slot.gethoraini();
    }
    else return diaMenor(diaDaSemana, slot.getDiaDaSemana());
}
