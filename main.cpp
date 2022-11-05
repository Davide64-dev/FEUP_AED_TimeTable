#include <iostream>
#include "UcTurma.h"
#include "Gestor.h"
#include <algorithm>
void u(Gestor &gestor);
void o (Gestor &gestor);
void h(Gestor &gestor);
void p(Gestor &gestor);
void r(Gestor &gestor);
void ra(Gestor &gestor);
void rp(Gestor &gestor);
void printOcupacao(const vector<Horario>& temp, Gestor gestor);
bool compBynumEstudantes(const Horario& horario1, const Horario& horario2);

int main() {

    Gestor gestor{};

    gestor.readHorarios();
    gestor.readEstudantes();
    gestor.fillNumEstudantes();
    gestor.setMap();
    gestor.readPedidos();

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
        cout << "r - Pedidos" << "\n";

        cout << "" << "\n";
        cout << "g - Guardar dados para ficheiro" << "\n";

        cout << "" << "\n";
        cout << "q - Guardar e Sair" << "\n";

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

        if (op == 'r'){
            r(gestor);

        }

        if (op == 'g'){
            gestor.writeEstudantes();
            gestor.writePedidosPendentes();
        }

    }
    //gestor.writeEstudantes();
    gestor.writePedidosPendentes();

    return 0;
}

void p(Gestor &gestor){
    int num;
    string temp = "=====================================";
    cout << "Inserir Número Mecanográfico: ";
    cin >> num;
    cout << temp << "\n";
    gestor.PesquisarEstudante(num);
    cout << temp << "\n";
}

void h(Gestor &gestor){
    int num;
    string temp = "=====================================";
    cout << "Inserir Número Mecanográfico: ";
    cin >> num;
    cout << temp << "\n";
    gestor.HorariodoEstudante(num);
    cout << temp << "\n";
}


void o(Gestor &gestor){
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

void printOcupacao(const vector<Horario>& temp, Gestor gestor){
    cout << "Codigo UC|Nome Uc|Código Turma|Número de Estudantes" << "\n";
    for (const Horario& hor : temp){
        cout << hor.getcodUC() << "|" << gestor.cadeiras[hor.getcodUC()] << "|" <<
             hor.getcodTurma() << "|" << hor.getNumEstudantes() << "\n";
    }
}

void u(Gestor &gestor){
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

void r(Gestor &gestor) {
    char op = ' ';

    while(op != 'q'){
        cout << "" << '\n';
        cout << "a - Adicionar pedido" << "\n";

        cout << "" << "\n";
        cout << "p - Processar pedido" << "\n";

        cout << "" << "\n";
        cout << "q - Sair" << "\n";

        cout << "" << "\n";
        cout << "?";

        cin >> op;
        cout << "" << "\n";

        if (op == 'a')
            ra(gestor);

        if(op == 'p')
            rp(gestor);

    }
}

void ra(Gestor &gestor) {
    char op = ' ';
    while(op != 'q') {
        cout << "" << '\n';
        cout << "a - Adicionar turma" << "\n";

        cout << "" << "\n";
        cout << "r - Remover turma" << "\n";

        cout << "" << "\n";
        cout << "c - Alterar turmas" << "\n";

        cout << "" << "\n";
        cout << "q - Voltar" << "\n";

        cout << "" << "\n";
        cout << "?";

        cin >> op;
        cout << "" << "\n";

        if (op == 'a')
            gestor.addPedidoAdd();
        if (op == 'r')
            gestor.addPedidoRem();
        if (op == 'c')
            gestor.addPedidoAlt();
    }
}

void rp(Gestor &gestor) {
    if(gestor.getPedidos().empty()) {
        cout << "" << '\n';
        cout << "Sem pedidos!" << '\n';
        return;
    }
    char op = ' ';
    while(op != 'q' && !gestor.getPedidos().empty()){
        gestor.printPedido();

        cout << "" << '\n';
        cout << "a - Aceitar" << "\n";

        cout << "" << '\n';
        cout << "r - Rejeitar" << "\n";

        cout << "" << "\n";
        cout << "q - Voltar" << "\n";

        cout << "" << "\n";
        cout << "?";

        cin >> op;
        cout << "" << "\n";

        if (op == 'a'){
            if(!gestor.verifyPedido()) {
                char op1 = ' ';
                do {
                    cout << "Pedido não cumpre os requesitos. Pretende rejeitar pedido?";
                    cout << "" << '\n';
                    cout << "r - Rejeitar" << "\n";
                    cout << "" << "\n";
                    cout << "a - Aceitar" << "\n";
                    cout << "" << "\n";
                    cout << "q - Abortar" << "\n";
                    cout << "" << "\n";
                    cout << "?";
                    cin >> op1;
                    cout << "" << "\n";
                    if (op1 == 'r') {
                        gestor.rejeitarPedido();
                    }
                    if (op1 == 'a'){
                        gestor.aceitarPedido();
                    }
                }while(op1 != 'a' && op1 != 'r' && op1 != 'q');
            } else{
                gestor.aceitarPedido();
            }
        }
        if (op == 'r')
            gestor.rejeitarPedido();

        if(gestor.getPedidos().empty())
            cout << "Sem pedidos!";
    }

}

bool compBynumEstudantes(const Horario& horario1, const Horario& horario2){

    if (horario1.getNumEstudantes() == horario2.getNumEstudantes()){
        if (horario1.getcodUC() == horario2.getcodUC()){
            return horario1.getcodTurma() < horario2.getcodTurma();
        }
        else return horario1.getcodUC() < horario2.getcodUC();
    }
    else return horario1.getNumEstudantes() < horario2.getNumEstudantes();
}
