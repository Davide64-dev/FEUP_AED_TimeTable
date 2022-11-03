//
// Created by Davide Teixeira on 19/10/2022.
//

#ifndef UNTITLED3_SLOT_H
#define UNTITLED3_SLOT_H

#include <string>

using namespace std;
/**
 * Esta classe pretende modular uma aula de um dado para Uc/Turma
 */
class Slot {
    /**
     * Hora a que a aula começa
     */
    float horaini;
    /**
     * Duração da aula
     */
    float duracao;
    /**
     * Dia da semana em que acontece a aula
     */
    string diaDaSemana;
    /**
     * Tipo de aula (T, TP, PL, ...)
     */
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
