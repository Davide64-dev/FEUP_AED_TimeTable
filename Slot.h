//
// Created by Davide Teixeira on 19/10/2022.
//

#ifndef UNTITLED3_SLOT_H
#define UNTITLED3_SLOT_H

#include <string>

using namespace std;

class Slot {
    float horaini;
    float duracao;
    string tipo;
public:
    Slot(float i, float j, string k);
    float gethoraini() const;
    float getduaracao() const;
    string gettipo() const;
};


#endif //UNTITLED3_SLOT_H
