//
// Created by Davide Teixeira on 19/10/2022.
//

#ifndef UNTITLED3_SLOT_H
#define UNTITLED3_SLOT_H

#include <string>

using namespace std;

class Slot {
    float horaini;
    float duracao;
    string diaDaSemana;
    string tipo;
public:
    Slot(float horaini, float duracao, const string &diaDaSemana, const string &tipo);
    float gethoraini() const;
    float getduaracao() const;
    string gettipo() const;
    const string &getDiaDaSemana() const;
    bool operator<(Slot slot) const;
    static bool diaMenor(string dia1, string dia2);
    static int correspondencia(string dia);
};


#endif //UNTITLED3_SLOT_H
