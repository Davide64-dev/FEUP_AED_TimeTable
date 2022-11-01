//
// Created by Davide Teixeira on 22/10/2022.
//

#include <fstream>
#include <istream>
#include <sstream>
#include <iostream>
#include <map>
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
    sort(horario.begin(), horario.end());
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

Estudante Gestor::PesquisarEstudante(int numero) {

    list<UcTurma> temp;

    temp.push_back(UcTurma("Hello, ", "World!"));

    Estudante ghost = Estudante(numero, "error", temp);

    if (estudantes.find(ghost) == estudantes.end()) {
        cout << "Estudante não Inscrito" << "\n";
        return ghost;
    } else {
        auto existing = estudantes.find(ghost);
        Estudante verdadeiro(*existing);

        cout << "Estudante Encontrado" << "\n";
        cout << "Número de Estudante: " << numero << "\n";
        cout << "Nome: " << verdadeiro.getnome() << "\n";

        return verdadeiro;
    }
}

bool Gestor::cmp(pair<Slot, UcTurma>& a, pair<Slot, UcTurma>& b){
    return a.first < b.first;
}

void Gestor::HorariodoEstudante(int numero){


    map<string, string> cadeiras;

    cadeiras.insert(pair<string, string>("L.EIC001", "Álgebra Linear e Geometria Analítica"));
    cadeiras.insert(pair<string, string>("L.EIC002", "Análise Matemática I"));
    cadeiras.insert(pair<string, string>("L.EIC003", "Fundamentos de Programação"));
    cadeiras.insert(pair<string, string>("L.EIC004", "Fundamentos de Sistemas Computacionais"));
    cadeiras.insert(pair<string, string>("L.EIC005", "Matemática Discreta"));
    cadeiras.insert(pair<string, string>("UP001", "Projeto UP"));
    cadeiras.insert(pair<string, string>("L.EIC006", "Arquitetura de Computadores"));
    cadeiras.insert(pair<string, string>("L.EIC007", "Análise Matemática II"));
    cadeiras.insert(pair<string, string>("L.EIC008", "Física I"));
    cadeiras.insert(pair<string, string>("L.EIC010", "Teoria da Computação"));
    cadeiras.insert(pair<string, string>("L.EIC009", "Programação"));
    cadeiras.insert(pair<string, string>("L.EIC011", "Algoritmos e Estruturas de Dados"));
    cadeiras.insert(pair<string, string>("L.EIC012", "Bases de Dados"));
    cadeiras.insert(pair<string, string>("L.EIC013", "Física II"));
    cadeiras.insert(pair<string, string>("L.EIC014", "Laboratório de Desenho e Teste de Software"));
    cadeiras.insert(pair<string, string>("L.EIC015", "Sistemas Operativos"));
    cadeiras.insert(pair<string, string>("L.EIC016", "Desenho de Algoritmos"));
    cadeiras.insert(pair<string, string>("L.EIC017", "Engenharia de Software"));
    cadeiras.insert(pair<string, string>("L.EIC018", "Laboratório de Computadores"));
    cadeiras.insert(pair<string, string>("L.EIC019", "Linguagens e Tecnologias Web"));
    cadeiras.insert(pair<string, string>("L.EIC020", "Métodos Estatísticos"));
    cadeiras.insert(pair<string, string>("L.EIC021", "Fundamentos de Segurança Informática"));
    cadeiras.insert(pair<string, string>("L.EIC022", "Interação Pessoa Computador"));
    cadeiras.insert(pair<string, string>("L.EIC023", "Laboratório de Bases de Dados e Aplicações Web"));
    cadeiras.insert(pair<string, string>("L.EIC024", "Programação Funcional e Lógica"));
    cadeiras.insert(pair<string, string>("L.EIC025", "Redes de Computadores"));
    cadeiras.insert(pair<string, string>("L.EIC026", "Compiladores"));
    cadeiras.insert(pair<string, string>("L.EIC027", "Computação Gráfica"));
    cadeiras.insert(pair<string, string>("L.EIC028", "Computação Paralela e Distribuida"));
    cadeiras.insert(pair<string, string>("L.EIC029", "Inteligência Artificial"));
    cadeiras.insert(pair<string, string>("L.EIC030", "Projeto Integrador"));



    Estudante student = PesquisarEstudante(numero);

    if (student.getnome() == "error"){
    }
    else{
        list<UcTurma> turmas = student.gethorario();
        vector<pair<Slot, UcTurma>> mondays;
        vector<pair<Slot, UcTurma>> tuesdays;
        vector<pair<Slot, UcTurma>> wednesdays;
        vector<pair<Slot, UcTurma>> thursdays;
        vector<pair<Slot, UcTurma>> fridays;

        for (UcTurma turma : turmas){
            list<Slot> k;
            Horario temp = getHorariobyUcTurma(turma);
            for (Slot i : temp.getaulas()){
                if (i.getDiaDaSemana() == "Monday")
                    mondays.push_back(pair<Slot, UcTurma>(i, turma));
                else if (i.getDiaDaSemana() == "Tuesday")
                    tuesdays.push_back(pair<Slot, UcTurma>(i, turma));
                else if (i.getDiaDaSemana() == "Wednesday")
                    wednesdays.push_back(pair<Slot, UcTurma>(i, turma));
                else if (i.getDiaDaSemana() == "Thursday")
                    thursdays.push_back(pair<Slot, UcTurma>(i, turma));
                else if (i.getDiaDaSemana() == "Friday")
                    fridays.push_back(pair<Slot, UcTurma>(i, turma));
                    }
        }

        sort(mondays.begin(), mondays.end(), cmp);
        sort(tuesdays.begin(), tuesdays.end(), cmp);
        sort(wednesdays.begin(), wednesdays.end(), cmp);
        sort(thursdays.begin(), thursdays.end(), cmp);
        sort(fridays.begin(), fridays.end(), cmp);


        cout << "=====================================" << "\n";
        cout << "Segunda-Feira: ";

        printHorario(mondays, cadeiras);

        cout << "Terça-Feira: ";

        printHorario(tuesdays, cadeiras);

        cout << " " << "\n";
        cout << "Quarta-Feira: ";

        printHorario(wednesdays, cadeiras);

        cout <<" " << "\n";
        cout << "Quinta-Feira: ";

        printHorario(thursdays, cadeiras);

        cout << " " << "\n";
        cout << "Sexta-Feira: ";

        printHorario(fridays, cadeiras);
    }
}

void Gestor::printHorario(vector<pair<Slot, UcTurma>> vetor, map<string, string> cadeiras){
    for (pair<Slot, UcTurma> i : vetor){
        cout << i.first.gethoraini() << "-" << i.first.getduaracao() + i.first.gethoraini()
             << " -> " << i.first.gettipo() << " - " << cadeiras[i.second.getcodUC()] << "(" <<
             i.second.getcodUC() << ")" << " - "<<  i.second.getcodTurma() << "\n";
        cout << "               ";
    }
    cout << " " << "\n";
}

Horario Gestor::getHorariobyUcTurma(UcTurma turma){
    list<Slot> lista;
    Horario temp = Horario(turma.getcodUC(), turma.getcodTurma(), lista);
    std::vector<int>::iterator it;
    int low = 0;
    int high= horario.size()-1;
    int middle;
    while (low < high){
        int middle = low + (high - low) / 2;
        if (horario[middle] < temp) low = middle+1;
        else high = middle;
    }
    middle = low + (high - low) / 2;
    if (horario[middle] == temp) return horario[middle];
    else return temp;
}

bool ordemAlfabetica(Estudante student1, Estudante student2){
    if (student1.getnome() == student2.getnome()) {
        return student1.getcodigo() < student2.getcodigo();
    }
    else return student1.getnome() < student2.getnome();
}

struct ordemAlfabeticaStruct {

    bool operator()(Estudante const &student1, Estudante const &student2) const{

        if (student1.getnome() == student2.getnome())         {
            return student1.getcodigo() < student2.getcodigo();
        }
        else return student1.getnome() < student2.getnome();
    }
};

void Gestor::maisNUcs(int n) {
    set<Estudante, ordemAlfabeticaStruct> temp(estudantes.begin(), estudantes.end());
    std::set<Estudante>::iterator it;
    //temp = estudantes;
    cout << "Id|Nome" << "\n";
    for (it = temp.begin(); it != temp.end(); it++) {
        if (it->gethorario().size() >= n){
            cout << it->getcodigo() << "|" << it->getnome() << "\n";
        }
    }
}
 /*
struct ordemalfabeticaStruct {
    bool operator()(Estudante const &student1, Estudante const &student2) const {

        if (student1.getnome() == student2.getnome()) {
            return student1.getcodigo() < student2.getcodigo();
        } else return student1.getnome() < student2.getnome();
    }
};
  */