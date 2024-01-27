#include <iostream>
#include <string>
#include "UcTurma.h"
using namespace std;

/**
 *
 * @param i Código da Uc
 * @param j Código da Turma
 */
UcTurma::UcTurma(string i, string j): codUC(i), codTurma(j), Cap(25){};

/**
 * Complexidade: O(1)
 * @return Retorna o código da UC
 */
string UcTurma::getcodUC() const{
    return codUC;
}

/**
 * Complexidade: O(1)
 * @return Retorna o código da Turma
 */
string UcTurma::getcodTurma()const{
    return codTurma;
}

/**
 * Complexidade: O(1)
 * @return Retorna Cap (Capacidade Máxima)
 */
int UcTurma::getCap()const{
    return Cap;
}

/**
 * Override do operador '=='\n
 * Complexidade: O(1)
 * @param other Objeto da classe UcTurma
 * @return Retorna true se o código da UC e o código da Turma forem iguais. Retorna falso, em qualquer outro caso
 */
bool UcTurma::operator==(const UcTurma &other) const{
    return((codUC == other.getcodUC()) and (codTurma == other.getcodTurma()));

}

/**
 * Override do operador '<'\n
 * Complexidade: O(n)
 * @param other Objeto da classe UcTurma
 * @return Retorna true se o código da UC do primeiro for menor do que o do segundo, utilizando o código da Turma como
 * critério de desempate. Retorna false em qualquer outro caso
 */
bool UcTurma::operator< (const UcTurma &other) const{
    if (codUC == other.getcodUC()){
        return (codTurma < other.getcodUC());
    }
    return codUC < other.getcodUC();
}