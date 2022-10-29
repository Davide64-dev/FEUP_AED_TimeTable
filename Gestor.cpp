//
// Created by Davide Teixeira on 22/10/2022.
//

#include <fstream>
#include <istream>
#include <sstream>
#include <iostream>
#include "Gestor.h"

using namespace std;

Gestor::Gestor(set<Estudante> i , vector<Horario> j, queue<Pedido> k): estudantes(i), horario(j), pedidos(k){};

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
    ifstream in("../schedule/students_classes.csv");
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

        if (!codTurma.empty() && codTurma[codTurma.size() - 1] == '\r')
            codTurma.erase(codTurma.size() - 1);

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

void Gestor::readHorarios() {
    readAulas();

    vector<string> lineV(6);
    ifstream in("../schedule/classes.csv");
    string classCode, ucCode, weekday, type;
    float sHour, duration;

    string line, word;

    getline(in, line); //jump header
    while(getline(in, line)) {
        lineV.clear();
        istringstream iss(line);
        while (getline(iss, word, ',')) {
            lineV.push_back(word);
        }

        classCode = lineV[0];
        ucCode = lineV[1];
        weekday = lineV[2];
        sHour = stof(lineV[3]);
        duration = stof(lineV[4]);
        type = lineV[5];

        if (!type.empty() && type[type.size() - 1] == '\r')
            type.erase(type.size() - 1);

        // Procura linear -------- mudar pra binaria
        for(Horario& hor : horario) {

            string temp1 = hor.getcodUC();
            string temp2 = hor.getcodTurma();

            if (!temp1.empty() && temp1[temp1.size() - 1] == '\r')
                temp1.erase(temp1.size() - 1);

            if (!temp2.empty() && temp2[temp2.size() - 1] == '\r')
                temp2.erase(temp2.size() - 1);

            if(temp1 == ucCode && temp2 == classCode) {
                hor.addAula(Slot(sHour, duration, weekday, type));
            }
        }
    }
    in.close();
}

void Gestor::readAulas() {
    vector<string> lineV(2);
    ifstream in("../schedule/classes_per_uc.csv");
    string classCode, ucCode;

    string line, word;

    getline(in, line); //jump header
    while(getline(in, line)) {
        lineV.clear();
        istringstream iss(line);
        while (getline(iss, word, ',')) {
            lineV.push_back(word);
        }

        ucCode = lineV[0];
        classCode = lineV[1];

        if (!classCode.empty() && classCode[classCode.size() - 1] == '\r')
            classCode.erase(classCode.size() - 1);

        horario.emplace_back(ucCode, classCode);
    }
    in.close();
}

void Gestor::fillNumEstudantes() {
    for(Horario& hor : horario) {
        hor.setNumEstudantes(countStudents(hor.getcodUC(), hor.getcodTurma()));
    }
}

int Gestor::countStudents(string codUC, string codTurma) {
    int count = 0;
    for(const Estudante& student : estudantes) {
        if(studentInClass(student, codUC, codTurma)) {
            count++;
        }
    }
    return count;
}

bool Gestor::studentInClass(Estudante student, string codUC, string codTurma) {
    for(const UcTurma& ucTurma : student.gethorario()) {
        if(ucTurma.getcodUC() == codUC && ucTurma.getcodTurma() == codTurma) {
            return true;
        }
    }
    return false;
}

Estudante Gestor::PesquisarEstudante(int numero){

     list<UcTurma> temp;

     temp.push_back(UcTurma("Hello, ", "World!"));

    Estudante ghost = Estudante(numero, "", temp);
    if(estudantes.find(ghost) == estudantes.end()){
        cout << "Estudante não Inscrito" << "\n";
    }
    else{
        auto existing = estudantes.find(ghost);
        Estudante verdadeiro(*existing);

        cout << "Estudante Encontrado" << "\n";
        cout << "Número de Estudante: " << numero << "\n";
        cout << "Nome: " << verdadeiro.getnome() << "\n";

        return verdadeiro;
    }

}


