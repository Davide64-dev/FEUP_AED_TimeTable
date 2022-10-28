//
// Created by Davide Teixeira on 22/10/2022.
//

#ifndef UNTITLED3_GESTOR_H
#define UNTITLED3_GESTOR_H

#include <queue>
#include <set>
#include "Estudante.h"
#include "Horario.h"
#include "Pedido.h"

using namespace std;

class Gestor {
    set<Estudante> estudantes;
    vector<Horario> horario;
    queue<Pedido> pedidos;
public:
    Gestor();
    Gestor(set<Estudante> i, vector<Horario> j,queue<Pedido> k);
    set<Estudante> getEstudantes() const;
    vector<Horario> getHorario() const;
    queue<Pedido> getPedidos() const;
    void readEstudantes();
    void readHorarios();
    void readAulas();
    void fillNumEstudantes();
    int countStudents(string codUC, string codTurma);
    bool studentInClass(Estudante student, string codUC, string codTurma);
};



#endif //UNTITLED3_GESTOR_H
