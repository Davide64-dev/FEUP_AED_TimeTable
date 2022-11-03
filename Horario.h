//
// Created by Davide Teixeira on 19/10/2022.
//

#ifndef UNTITLED3_HORARIO_H
#define UNTITLED3_HORARIO_H

#include <string>
#include "Slot.h"
#include "UcTurma.h"

using namespace std;
/**
 * Esta classe pretende armazenar todas os pares Uc/Turma existentes, com o respetivo horário
 */
class Horario {
    /**
     * Código da UC
     */
    string codUC;
    /**
     * Código da Tumra
     */
    string codTurma;
    /**
     * Lista de Slot com as aulas de cada par Uc/Turma
     */
    list<Slot> aulas;
    /**
     * Número de estudantes inscritos no par Uc/Turma
     */
    int numEstudantes = 0;
public:
    int getNumEstudantes() const;

    void setNumEstudantes(int numEstudantes);

public:
    Horario(string i, string j, list<Slot> k);
    Horario(string codUC, string codTurma);
    string getcodUC() const;
    string getcodTurma() const;
    list<Slot> getaulas() const;
    void addAula(Slot aula);
    bool operator<(Horario horario) const;
    bool operator==(Horario horario) const;
};

#endif //UNTITLED3_HORARIO_H
