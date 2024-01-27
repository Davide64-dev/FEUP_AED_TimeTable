#include <list>
#include "Horario.h"

/**
 *
 * @param i Código da UC
 * @param j Código da Turma
 * @param k lista de Slot com as aulas
 */
Horario::Horario(string i, string j, list<Slot> k): codUC(i), codTurma(j), aulas(k){};

/**
 *
 * @param codUC Código da UC
 * @param codTurma Código da Turma
 */
Horario::Horario(string codUC, string codTurma) {
    this->codUC = codUC;
    this->codTurma = codTurma;
    aulas.clear();
}

/**
 * Complexidade: O(1)
 * @return Retorna o código da UC
 */
string Horario::getcodUC() const{
    return codUC;
}
/**
 * Complexidade: O(1)
 * @return Retorna o código da turma
 */
string Horario::getcodTurma()const{
    return codTurma;
}
/**
 * Complexidade: O(1)
 * @return Retorna a lista com as datas e horas das aulas
 */
list<Slot> Horario::getaulas() const{
    return aulas;
}

/**
 * Adiciona uma aula ao Horario\n
 * Complexidade: O(1)
 * @param aula Objeto Slot com as informações relativas à aula
 */
void Horario::addAula(Slot aula) {
    aulas.push_back(aula);
}

/**
 * Complexidade: O(1)
 * @return Retorna o número de estudantes
 */
int Horario::getNumEstudantes() const {
    return numEstudantes;
}

/**
 * Método que define o número de estudantes\n
 * Complexidade: O(1)
 * @param numEstudantes Número de estudantes que vai substituir o atributo antigo
 */
void Horario::setNumEstudantes(int numEstudantes) {
    Horario::numEstudantes = numEstudantes;
}

/**
 * Adiciona 1 ao númestudantes\n
 * Complexidade: O(1)
 */
void Horario::incrementS() {
    numEstudantes++;
}

/**
 * Remove 1 ao numestudantes\n
 * Complexidade: O(1)
 */
void Horario::decrementS() {
    numEstudantes--;
}
/**
 * Função Override do operador '<'\n
 * Complexidade: O(1)
 * @param horario Objeto da classe Horario
 * @return Retorna true se o código da UC do primeiro Horário for menor do que o do segundo. Caso seja igual, o
 * critério de desempate é o código da Turma. Retorna false em qualquer outro caso
 */
bool Horario::operator<(Horario horario) const{
    if (codUC == horario.getcodUC()){
        return codTurma < horario.getcodTurma();
    }
    else return codUC < horario.getcodUC();

}

/**
 * Função Override do operador '=='\n
 * Complexidade: O(1)
 * @param horario Objeto da classe Horario
 * @return Retorna true se o código da UC e o código da Turma forem iguais. Retorna false em qualquer outro caso
 */
bool Horario::operator==(Horario horario) const {

    return ((codUC == horario.getcodUC()) and (codTurma == horario.getcodTurma()));

}

