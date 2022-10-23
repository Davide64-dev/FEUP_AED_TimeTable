#include <iostream>
#include "UcTurma.h"
#include "Gestor.h"

int main() {
    /*UcTurma temp = UcTurma("L.EIC001", "1L.EIC12");
    cout << temp.getcodUC() << endl;
    cout << temp.getcodTurma() << endl;*/

    Gestor gestor{};

    gestor.readEstudantes();

    cout << gestor.getEstudantes().size();
}
