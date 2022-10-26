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

    cout << gestor.getEstudantes().size() << '\n';
    cout << gestor.getHorario().size() << '\n';


    // Teste de Remoção de um aluno na turma
    Estudante temp = *gestor.getEstudantes().begin();
    UcTurma temp1 = UcTurma("L.EIC001", "1LEIC05\r"); // Caso em que o aluno se encontra na turma
    UcTurma temp2 = UcTurma("L.EIC001", "1LEIC11\r"); // Caso em que o aluno não se encontra na turma
    temp.delUCTurma(temp1); // Vai eliminar a UcTurma da lista 'horário'
    temp.delUCTurma(temp2); // Não vai funcionar e vai imprimir uma mensagem de erro

}
