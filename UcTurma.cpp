//
// Created by Davide Teixeira on 19/10/2022.
//
#include <iostream>
#include <string>
#include "UcTurma.h"
using namespace std;

/**
 *
 * @param i Código da Uc
 * @param j Código da Turma
 */
UcTurma::UcTurma(string i, string j): codUC(i), codTurma(j), Cap(100){};

/**
 *
 * @return Retorna o código da UC
 */
string UcTurma::getcodUC() const{
    return codUC;
}

/**
 *
 * @return Retorna o código da Turma
 */
string UcTurma::getcodTurma()const{
    return codTurma;
}

int UcTurma::getCap()const{
    return Cap;
}

/**
 * Override do operador '=='
 * @param other Objeto da classe UcTurma
 * @return Retorna true se o código da UC e o código da Turma forem iguais. Retorna falso, em qualquer outro caso
 */
bool UcTurma::operator==(const UcTurma &other) const{
    return((codUC == other.getcodUC()) and (codTurma == other.getcodTurma()));

}

/**
 * Override do operador '<'
 * @param other Objeto da classe UcTurma
 * @return Retorna true se o código da UC do primeiro for menor do que o do segundo, utilizando o código da UC como
 * critério de desempate. Retorna false em qualquer outro caso
 */
bool UcTurma::operator< (const UcTurma &other) const{
    if (codUC == other.getcodUC()){
        return (codTurma < other.getcodUC());
    }
    return codUC < other.getcodUC();
}