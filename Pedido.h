//
// Created by Davide Teixeira on 22/10/2022.
//

#ifndef UNTITLED3_PEDIDO_H
#define UNTITLED3_PEDIDO_H


#include "Slot.h"
#include <vector>

using namespace std;

/**
 * Esta classe pretende armazenar todas os "Pedido" feitos que ainda se encontram por processar
 */
class Pedido {
    /**
     * Tipo do pedido {Add, Rem, ALter}
     */
    string tipo;
    /**
     * Código do estudante que efetuou o pedido
     */
    int codigo_estudante;
    /**
     * Turma(s) que o estudante pretende remover
     */
    vector<string> turmaR;
    /**
     * Turma(s) que o estudante prentende adicionar
     */
    vector<string> turmaA;
    /**
     * Uc(s) em que vai(ão) ser realizada(s) alterção(ões)
     */
    vector<string> ucs;
public:
    Pedido(const string &tipo, int codigoEstudante, const string &turmaR, const string &uc);

    Pedido(const string &tipo, int codigoEstudante, const vector<string> &turmaR, const vector<string> &turmaA,
           const vector<string> &ucs);

    int getcodigo_estudante() const;

    const vector<string> &getTurmaR() const;

    const vector<string> &getTurmaA() const;

    const vector<string> &getUCs() const;

    const string &getTipo() const;
};



#endif //UNTITLED3_PEDIDO_H
