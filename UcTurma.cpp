//
// Created by Davide Teixeira on 19/10/2022.
//

#include <string>
#include "UcTurma.h"
using namespace std;


UcTurma::UcTurma(string i, string j): codUC(i), codTurma(j), Cap(100){};

string UcTurma::getcodUC() const{
    return codUC;
}

string UcTurma::getcodTurma()const{
    return codTurma;
}

bool UcTurma::operator==(const UcTurma &other) const{
    return((codUC == other.getcodUC()) and (codTurma == other.getcodTurma()));

}
