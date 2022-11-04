//
// Created by Davide Teixeira on 22/10/2022.
//

#ifndef UNTITLED3_GESTOR_H
#define UNTITLED3_GESTOR_H

#include <queue>
#include <set>
#include "Estudante.h"
#include "Horario.h"
#include "Pedido.h"
#include <map>

using namespace std;
/**
 * Esta classe representa a entidade com responsabilidade de consultar os "Estudante", assim como os seus horários,
 * consultar as UcTurma e gerir os pedidos
 */

class Gestor {
    /**
     * Árvore Binária de Pesquisa com todos os objetos da classe "Estudante" inscritos
     */
    set<Estudante> estudantes;
    /**
     * Vetor com todos os objetos da classe "Horario"
     */
    vector<Horario> horario;
    /**
     * Fila que contém todos os objetos da classe "Pedido" a serem processados
     */
    queue<Pedido> pedidos;
public:
    /**
     * Mapa com as cadeiras que relaciona o código da UC com o nome da mesma
     */
    map<string, string> cadeiras;
    Gestor();
    Gestor(set<Estudante> i, vector<Horario> j,queue<Pedido> k);
    set<Estudante> getEstudantes() const;
    vector<Horario> getHorario() const;
    queue<Pedido> getPedidos() const;
    void readEstudantes();
    void readHorarios();
    void readAulas();
    void readPedidos();
    void fillNumEstudantes();
    int countStudents(const string& codUC, const string& codTurma);
    bool studentInClass(const Estudante& student, const string& codUC, string codTurma);
    Estudante PesquisarEstudante(int numero);
    void HorariodoEstudante(int numero);
    static bool cmp(pair<Slot, UcTurma>& a, pair<Slot, UcTurma>& b);
    static void printHorario(const vector<pair<Slot, UcTurma>>& vetor, map<string, string> cadeiras);
    Horario getHorariobyUcTurma(const UcTurma& turma);
    void maisNUcsAlfabetico(int n);
    void maisNUcsNumero(int n);
    void maisNUcs(int n);
    void setMap();
    void processPedidos();
    void pedidoAdd();
    void pedidoRemove();
    void pedidoAlter();
    set<Estudante>::iterator searchStudent(int code);
    list<Horario> getHorario(const list<UcTurma>& turmas);
    bool verifyOverlap(const list<Horario>& horario);
    void filterTP(list<Slot>& horario);
    list<Slot> getSlots(const list<Horario>& horario);
    bool verifyCap();
    void printPedido();
    bool verifyPedido();
    bool verifyAdd();
    bool verifyAlter();
    void rejeitarPedido();
    void aceitarPedido();
    void arquivar(bool aceite);
    void addPedidoAdd();
    void addPedidoRem();
    void addPedidoAlt();
    void writeEstudantes();
    void writePedidosPendentes();
    static string VectorintoString(vector<string> vetor);
    static vector<string> StringintoVectorClassCode(string conjunto);
    static vector<string> StringintoVectorUcCode(string conjunto);
    bool verifyClasses(vector<Horario> temp, vector<UcTurma> toAdd, vector<UcTurma> toRem);
    bool containsUC(const Horario& horario, vector<UcTurma>& ucTurmas);
};



#endif //UNTITLED3_GESTOR_H
