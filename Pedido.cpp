//
// Created by Davide Teixeira on 22/10/2022.
//

#include <list>
#include "Pedido.h"
#include "Slot.h"

using namespace std;

/**
 *
 * @return Retorna o código do Estudante
 */
int Pedido::getcodigo_estudante() const {
    return codigo_estudante;
}

/**
 *
 * @return Retorna o Tipo do Pedido
 */
const string &Pedido::getTipo() const {
    return tipo;
}

/**
 *
 * @param tipo Tipo do Pedido ("Add" ou "Rem")
 * @param codigoEstudante Código do Estudante
 * @param turmaR Turma a ser adicionado ou removido
 * @param uc Uc em que vai ocorrer a adição/remoção
 */
Pedido::Pedido(const string &tipo, int codigoEstudante, const string &turmaR, const string &uc) : tipo(tipo),
    codigo_estudante(codigoEstudante) {
    this->turmaR.push_back(turmaR);
    this->ucs.push_back(uc);
}

/**
 *
 * @param tipo Tipo de Pedido ("Alter")
 * @param codigoEstudante Código do Estudante
 * @param turmaR Turma(s) a ser removido
 * @param turmaA Turma(s) a ser adicionada
 * @param ucs Uc(s) em que vai(ão) ocorrer a(s) permutação(ões)
 */
Pedido::Pedido(const string &tipo, int codigoEstudante, const vector<string> &turmaR, const vector<string> &turmaA,
               const vector<string> &ucs) : tipo(tipo), codigo_estudante(codigoEstudante), turmaR(turmaR),
               turmaA(turmaA), ucs(ucs) {};
/**
 *
 * @return Retorna TurmaR
 */
const vector<string> &Pedido::getTurmaR() const {
    return turmaR;
}

/**
 *
 * @return Retorna TurmaA
 */
const vector<string> &Pedido::getTurmaA() const {
    return turmaA;
}

/**
 *
 * @return Retorna UCs
 */
const vector<string> &Pedido::getUCs() const {
    return ucs;
}

