#include <iostream>
#include "UcTurma.h"
#include "Gestor.h"
void u(Gestor gestor);
void o (Gestor gestor);
void h(Gestor gestor);
void p(Gestor gestor);
void printOcupacao(vector<Horario> temp, Gestor gestor);
bool compBynumEstudantes(Horario horario1, Horario horario2);

int main() {

    Gestor gestor{};

    gestor.readHorarios();
    gestor.readEstudantes();
    gestor.fillNumEstudantes();
    gestor.setMap();

    char op = ' ';

    while(op != 'q'){
        cout << "" << '\n';
        cout << "p - Pesquisar Estudante" << "\n";

        cout << "" << "\n";
        cout << "h - Consultar Horário" << "\n";

        cout << "" << "\n";
        cout << "u - Estudantes com mais de n UC's" << "\n";

        cout << "" << "\n";
        cout << "o - Ocupação de Turmas/UC" << "\n";

        cout << "" << "\n";
        cout << "q - Sair" << "\n";

        cout << "" << "\n";
        cout << "?";

        cin >> op;
        cout << "" << "\n";

        if (op == 'p'){
            p(gestor);

        }

        if (op == 'h'){
            h(gestor);

        }

        if (op == 'o'){
            o(gestor);
            }

        if (op == 'u'){
            u(gestor);

        }

    }
    return 0;
}

void p(Gestor gestor){
    int num;
    string temp = "=====================================";
    cout << "Inserir Número Mecanográfico: ";
    cin >> num;
    cout << temp << "\n";
    gestor.PesquisarEstudante(num);
    cout << temp << "\n";
}

void h(Gestor gestor){
    int num;
    string temp = "=====================================";
    cout << "Inserir Número Mecanográfico: ";
    cin >> num;
    cout << temp << "\n";
    gestor.HorariodoEstudante(num);
    cout << temp << "\n";
}


void o(Gestor gestor){
    char op1 = ' ';
    while(op1 != 'q') {
        cout << "   u - Ordenação por UC" << "\n";

        cout << "" << "\n";
        cout << "   c - Ordenação Crescente" << "\n";

        cout << "" << "\n";
        cout << "   d - Ordenação Decrescente" << "\n";

        cout << "" << "\n";
        cout << "   q - Sair" << "\n";

        cout << "" << "\n";
        cout << "   ?";

        cin >> op1;
        cout << "" << "\n";

        if (op1 == 'u') {
            vector<Horario> temp = gestor.getHorario();
            printOcupacao(temp, gestor);
            op1 = 'q';
        }

            // Dá sort duas vezes - talvez não seja a melhor opção
        else if (op1 == 'c') {
            vector<Horario> temp = gestor.getHorario();
            sort(temp.begin(), temp.end(), compBynumEstudantes);
            printOcupacao(temp, gestor);
            sort(temp.begin(), temp.end());
            op1 = 'q';
        } else if (op1 == 'd') {
            vector<Horario> temp = gestor.getHorario();
            sort(temp.begin(), temp.end(), compBynumEstudantes);
            reverse(temp.begin(), temp.end());
            printOcupacao(temp, gestor);
            sort(temp.begin(), temp.end());
            op1 = 'q';

        }
    }
}

void printOcupacao(vector<Horario> temp, Gestor gestor){
    cout << "Codigo UC|Nome Uc|Código Turma|Número de Estudantes" << "\n";
    for (Horario hor : temp){
        cout << hor.getcodUC() << "|" << gestor.cadeiras[hor.getcodUC()] << "|" <<
             hor.getcodTurma() << "|" << hor.getNumEstudantes() << "\n";
    }
}

void u(Gestor gestor){
    char op1 = ' ';
    while(op1 != 'q') {
        //cout << "" << '\n';
        cout << "   a - Ordem Alfabética" << "\n";

        cout << "" << "\n";
        cout << "   u - Ordem Crescente de Número de Uc's" << "\n";

        cout << "" << "\n";
        cout << "   n - Ordem Número Mecanográfico" << "\n";

        cout << "" << "\n";
        cout << "   q - Sair" << "\n";

        cout << "" << "\n";
        cout << "   ?";

        cin >> op1;
        cout << "" << "\n";

        int num;

        if (op1 == 'a') {
            string temp = "=====================================";
            cout << "   n≥";
            cin >> num;
            cout << temp << "\n";
            gestor.maisNUcsAlfabetico(num);
            cout << temp << "\n";
            op1 = 'q';
        }

        else if (op1 == 'u') {
            string temp = "=====================================";
            cout << "   n≥";
            cin >> num;
            cout << temp << "\n";
            gestor.maisNUcsNumero(num);
            cout << temp << "\n";
            op1 = 'q';
        }


        else if (op1 == 'n') {
            string temp = "=====================================";
            cout << "   n≥";
            cin >> num;
            cout << temp << "\n";
            gestor.maisNUcs(num);
            cout << temp << "\n";
            op1 = 'q';
        }
    }
}

bool compBynumEstudantes(Horario horario1, Horario horario2){

    if (horario1.getNumEstudantes() == horario2.getNumEstudantes()){
        if (horario1.getcodUC() == horario2.getcodUC()){
            return horario1.getcodTurma() < horario2.getcodTurma();
        }
        else return horario1.getcodUC() < horario2.getcodUC();
    }
    else return horario1.getNumEstudantes() < horario2.getNumEstudantes();
}
