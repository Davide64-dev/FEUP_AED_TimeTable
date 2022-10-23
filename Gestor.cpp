//
// Created by Davide Teixeira on 22/10/2022.
//

#include <fstream>
#include <istream>
#include <sstream>
#include "Gestor.h"

using namespace std;

Gestor::Gestor(set<Estudante> i , vector<Horario> j, queue<Pedido> k): estudantes(), horario(j), pedidos(k){};

Gestor::Gestor() = default;

set<Estudante> Gestor::getEstudantes() const{
    return estudantes;
}

vector<Horario> Gestor::getHorario() const{
    return horario;
}

queue<Pedido> Gestor::getPedidos() const{
    return pedidos;
}

void Gestor::readEstudantes() {
    vector<string> lineV(4);
    ifstream in("C:\\Users\\mapo0\\CLionProjects\\projeto\\AED_Project\\schedule\\students_classes.csv");
    string line, word;
    string name, codUc, codTurma;
    int sCode;

    list<UcTurma> hora;
    getline(in, line); //jump header
    while(getline(in, line)) {
        lineV.clear();
        istringstream iss(line);
        while(getline(iss, word, ',')) {
            lineV.push_back(word);
        }

        sCode = stoi(lineV[0]);
        name = lineV[1];
        codUc = lineV[2];
        codTurma = lineV[3];
        UcTurma UCTurma(codUc, codTurma);
        list<UcTurma> turma(1, UCTurma);
        Estudante student(sCode, name, turma);

        if(estudantes.find(student) == estudantes.end()) {
            estudantes.insert(student);
        } else {
            auto existing = estudantes.find(student);
            Estudante tutu(*existing);
            tutu.addUCTurma(UCTurma);
            estudantes.erase(student);
            estudantes.insert(tutu);
        }
    }
    in.close();
}

