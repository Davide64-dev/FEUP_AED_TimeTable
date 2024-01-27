#ifndef UNTITLED3_UCTURMA_H
#define UNTITLED3_UCTURMA_H

using namespace std;
/**
 * Esta classe representa um par Uc/Turma
 */
class UcTurma {
    /**
     * Código da UC
     */
    string codUC;
    /**
     * Código da Turma
     */
    string codTurma;
    /**
     * Capacidade máxima da turma
     */
    int Cap;
public:
    UcTurma(string i, string j);
    string getcodUC() const;
    string getcodTurma() const;
    int getCap() const;
    bool operator== (const UcTurma &other) const;
    bool operator< (const UcTurma &other) const;
};


#endif //UNTITLED3_UCTURMA_H
