#include <iostream>
#include "UcTurma.h"
#include "Gestor.h"

int main() {

    /*UcTurma temp = UcTurma("L.EIC001", "1L.EIC12");
    cout << temp.getcodUC() << endl;
    cout << temp.getcodTurma() << endl;*/

    Gestor gestor{};

    gestor.readHorarios();
    gestor.readEstudantes();
    gestor.fillNumEstudantes();

    cout << gestor.getEstudantes().size() << '\n';
    cout << gestor.getHorario().size() << '\n';

    vector <Horario> horario = gestor.getHorario();



    // Teste de Remoção de um aluno na turma

    Estudante temp = *gestor.getEstudantes().begin();
    UcTurma temp1 = UcTurma("L.EIC001", "1LEIC05\r"); // Caso em que o aluno se encontra na turma
    UcTurma temp2 = UcTurma("L.EIC001", "1LEIC11\r"); // Caso em que o aluno não se encontra na turma
    temp.delUCTurma(temp1); // Vai eliminar a UcTurma da lista 'horário'
    temp.delUCTurma(temp2); // Não vai funcionar e vai imprimir uma mensagem de erro


    // Teste de ordenação da lista 'horario' na classe 'Estudante'

    temp.addUCTurma(UcTurma("L.EIC001", "L.EIC005")); // Adição de uma turma no fim do 'horário'
    list <UcTurma> hor = temp.gethorario(); // Horário em si


    cout << "" << endl;                         // Imprimir a lista
    cout << "Antes de ser ordenada" << endl;    // antes da
    for (UcTurma i : hor) i.print();            // ordenação

    hor.sort(); // Operação de sort de uma lista da stl

    cout << "" << endl;                         // Imprimir a lista
    cout << "Depois de ser ordenada" << endl;   // depois da
    for (UcTurma i : hor) i.print();            // ordenação


    // Teste do sort do slot
    Slot slot1 = Slot(2, 1.5, "Thursday", "TP");
    Slot slot2 = Slot(5, 2, "Monday", "T");
    Slot slot3 = Slot(6, 2, "Thursday", "PL");
    list<Slot> listadeslots;
    listadeslots.push_back(slot1);
    listadeslots.push_back(slot2);
    listadeslots.push_back(slot3);

    listadeslots.sort();
}
