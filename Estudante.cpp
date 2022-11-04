//
// Created by Davide Teixeira on 19/10/2022.
//
#include <iostream>
#include <algorithm>
using namespace std;
#include "Estudante.h"
/**
 * @param i Código do Estudante
 * @param j Nome do Estudante
 * @param k Lista de UcTurma às quais se encontra inscrito
 */
Estudante::Estudante(int i, string j, list<UcTurma> k): codigo(i), nome(j), horario(k){};

/**
 *
 * @return Retorna o número mecanográfico do Estudante
 */
int Estudante::getcodigo() const{
    return codigo;
}
/**
 *
 * @return Retorna o nome do Estudante
 */
string Estudante::getnome()const{
    return nome;
}

/**
 *
 * @return Retorna uma lista com todas as UcTurmas às quais o Estudante se encontra inscrito
 */
list<UcTurma> Estudante::gethorario() const{
    return horario;
}
/**
 * Função Override do operador '<'
 * @param student Objeto da classe Estudante
 * @return Retorna true se o número do primeiro estudante for menor que o número do segundo. Retorna false
 * em qualquer outro caso
 */
bool Estudante::operator<(Estudante student) const {
    return codigo < student.codigo;
}

/**
 * Função de compração de dois objetos da classe estudante por ordem alfabética dos seus nomes
 * @param student Objeto da classe Estudante
 * @return Retorna true se o nome do primeiro estudante vier em primeiro, por ordem alfabética. Retorna false,
 * caso o segundo estudante vier primeiro. Nos casos em que o nome é igual, usa o número mecanográfico como
 * critério de desempate
 */

bool Estudante::ordemAlfabética(Estudante student) const {
    if (nome == student.getnome()) {
        return codigo < student.getcodigo();
    }
    else return nome < student.getnome();
}

/**
 * Função de comparação de dois objetos da classe estudante, por número de UC a que estãos inscritos
 * @param student Objeto da classe Estudante
 * @return Retorna true se o primeiro estudante tiver menos unidades curriculares do que o segundo e false caso
 * tenha mais. Caso estejam inscritos ao mesmo número de Uc's, usa-se o número mecanográfico como critério de desempate
 */
bool Estudante::ordemNumeroUcs(Estudante student) const {
    if (horario.size() == student.gethorario().size()){
        return codigo < student.getcodigo();
    }
    else return horario.size() < student.gethorario().size();
}


/**
 * Adiciona a um estudante uma UcTurma, sem qualquer restrição
 * @param turma Objeto da classe UcTurma (Turma a remover o Estudante)
 */
void Estudante::addUCTurma(UcTurma turma) {
    horario.push_back(turma);
}

/**
 * Remove a um estudante uma UcTurma, apenas com a restrição de ter de estar inscrito a essa mesma turma
 * @param turma Objeto da classe UcTurma (Turma a adicionar o Estudante)
 * @return Retorna true, se for possível adicionar, retorna false em qualquer outro cado
 */
bool Estudante::delUCTurma(UcTurma turma){
    UcTurma temp = turma;
    std::list<UcTurma>::iterator it;
    it = find(horario.begin(), horario.end(), turma);
    if (it != horario.end())
        horario.erase(it);
    else
        return false;
    return true;
}

int Estudante::naTurma(UcTurma turma) const{
    for (UcTurma i : horario){
        if (i.getcodUC() == turma.getcodUC()){
            if(i.getcodTurma() == turma.getcodTurma()){
                return 0;
            }
            else return 1;
        }
    }
    return -1;
}