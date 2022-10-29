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
        cout << "q - Sair" << "\n";

        cout << "" << "\n";
        cout << "?";
        cin >> op;
        cout << "" << "\n";

        if (op == "p"){
            int num;
            string temp = "=====================================";
            cout << "Inserir Número Mecanográfico: ";
            cout << "" << "\n";
            cin >> num;
            cout << temp << "\n";
            gestor.PesquisarEstudante(num);
            cout << temp << "\n";

        }
    }

}
