#include <iostream>
#include "UcTurma.h"
#include "Gestor.h"

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
            int num;
            string temp = "=====================================";
            cout << "Inserir Número Mecanográfico: ";
            cin >> num;
            cout << temp << "\n";
            gestor.PesquisarEstudante(num);
            cout << temp << "\n";

        }

        if (op == 'h'){
            int num;
            string temp = "=====================================";
            cout << "Inserir Número Mecanográfico: ";
            cin >> num;
            cout << temp << "\n";
            gestor.HorariodoEstudante(num);
            cout << temp << "\n";

        }

        if (op == 'o'){
            cout << "Codigo UC|Nome Uc|Código Turma|Número de Estudantes" << "\n";
            for (Horario hor : gestor.getHorario()){
               cout << hor.getcodUC() << "|" << gestor.cadeiras[hor.getcodUC()] << "|" << hor.getcodTurma() << "|" << hor.getNumEstudantes() << "\n";
            }
        }

        if (op == 'u'){
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

    }
    return 0;
}