#include <iostream>
#include "UcTurma.h"
#include "Gestor.h"

int main() {

    Gestor gestor{};

    gestor.readHorarios();
    gestor.readEstudantes();
    gestor.fillNumEstudantes();
    string op = "";

    while(op != "q"){
        cout << "" << '\n';
        cout << "p - Pesquisar Estudante" << "\n";

        cout << "" << "\n";
        cout << "h - Consultar Horário" << "\n";

        cout << "" << "\n";
        cout << "u - Estudantes com mais de n UC's" << "\n";

        cout << "" << "\n";
        cout << "q - Sair" << "\n";

        cout << "" << "\n";
        cout << "?";


        cin >> op;
        cout << "" << "\n";

        if (op == "p"){
            int num;
            string temp = "=====================================";
            cout << "Inserir Número Mecanográfico: ";
            cin >> num;
            cout << temp << "\n";
            gestor.PesquisarEstudante(num);
            cout << temp << "\n";

        }

        if (op == "h"){
            int num;
            string temp = "=====================================";
            cout << "Inserir Número Mecanográfico: ";
            cin >> num;
            cout << temp << "\n";
            gestor.HorariodoEstudante(num);
            cout << temp << "\n";

        }

        if (op == "u"){
            int num;
            string temp = "=====================================";
            cout << "n≥";
            cin >> num;
            cout << temp << "\n";
            gestor.maisNUcs(num);
            cout << temp << "\n";
        }

    }

    return 0;
}
