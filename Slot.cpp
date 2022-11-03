//
// Created by Davide Teixeira on 19/10/2022.
//

#include "Slot.h"
/**
 *
 * @param horaini Hora a que a aula começa
 * @param duracao Duração da aula
 * @param diaDaSemana Dia da semana em que acontece a aula
 * @param tipo Tipo de aula (T, TP, PL, ...)
 */
Slot::Slot(float horaini, float duracao, const string &diaDaSemana, const string &tipo) : horaini(horaini),
                                                                                          duracao(duracao),
                                                                                          diaDaSemana(diaDaSemana),
                                                                                          tipo(tipo) {}
/**
 *
 * @return Retorna a hora a que começa a aula
 */
float Slot::gethoraini() const{
    return horaini;
}
/**
 *
 * @return Retorna a duração da aula
 */
float Slot::getduaracao() const{
    return duracao;
}

/**
 *
 * @return Retorna o tipo da aula
 */
string Slot::gettipo() const{
    return tipo;
}

/**
 *
 * @return Retorna o Dia da Semana
 */
const string &Slot::getDiaDaSemana() const {
    return diaDaSemana;
}

/**
 * Função auxiliar que faz uma correspondência entre o dia da semana e um número de forma a poder comparar os dias da
 * semana
 * @param dia Dia da semana
 * @return Retorna um número 0...6 correspondente (Monday...Sunday). Caso não seja dado nenhuma string correta, retorna
 *  -1
 */
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

/**
 * Função que retorna o menor de dois dias
 * @param dia1 Primeiro dia (da semana)
 * @param dia2 Segundo dia (da semana)
 * @return Retorna true se o primeiro dia for menor. Retorna false em qualquer outro caso
 */
bool Slot::diaMenor(string dia1, string dia2){
    if ((Slot::correspondencia(dia1) == -1) or (Slot::correspondencia(dia2) == -1)) return false;
    else return (Slot::correspondencia(dia1) < Slot::correspondencia(dia2));
}

/**
 * Override do operador '<'
 * @param slot Objeto da classe Slot
 * @return Retorna true se o dia e hora do primeiro Sdlot forem menores que o dia e hora do segundo Slot
 */
bool Slot::operator<(Slot slot) const {
    if (diaDaSemana == slot.getDiaDaSemana()){
        return horaini < slot.gethoraini();
    }
    else return diaMenor(diaDaSemana, slot.getDiaDaSemana());
}
