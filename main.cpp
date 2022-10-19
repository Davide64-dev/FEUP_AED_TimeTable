#include <iostream>
#include "UcTurma.h"

int main() {
    UcTurma temp = UcTurma("L.EIC001", "1L.EIC12");
    cout << temp.getcodUC() << endl;
    cout << temp.getcodTurma() << endl;
}
