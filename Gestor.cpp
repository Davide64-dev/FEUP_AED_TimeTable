#include <fstream>
#include <istream>
#include <sstream>
#include <iostream>
#include <map>
#include <algorithm>
#include "Gestor.h"

using namespace std;
/**
 *
 * @param i Árvore Binária de Pesquisa com os estudantes
 * @param j Vetor com todos os objetos da classe "Horario"
 * @param k Fila que contém todos os objetos da classe "Pedido" a serem processados
 */
Gestor::Gestor(set<Estudante> i , vector<Horario> j, queue<Pedido> k): estudantes(i), horario(j), pedidos(k) {}

/**
 * Método que adidicona ao mapa todas as correspondências entre o código e o nome da UC\n
 * Complexidade: O(1)
 */
void Gestor::setMap(){
    cadeiras.insert(pair<string, string>("L.EIC001", "Álgebra Linear e Geometria Analítica"));
    cadeiras.insert(pair<string, string>("L.EIC002", "Análise Matemática I"));
    cadeiras.insert(pair<string, string>("L.EIC003", "Fundamentos de Programação"));
    cadeiras.insert(pair<string, string>("L.EIC004", "Fundamentos de Sistemas Computacionais"));
    cadeiras.insert(pair<string, string>("L.EIC005", "Matemática Discreta"));
    cadeiras.insert(pair<string, string>("UP001", "Projeto UP"));
    cadeiras.insert(pair<string, string>("L.EIC006", "Arquitetura de Computadores"));
    cadeiras.insert(pair<string, string>("L.EIC007", "Análise Matemática II"));
    cadeiras.insert(pair<string, string>("L.EIC008", "Física I"));
    cadeiras.insert(pair<string, string>("L.EIC010", "Teoria da Computação"));
    cadeiras.insert(pair<string, string>("L.EIC009", "Programação"));
    cadeiras.insert(pair<string, string>("L.EIC011", "Algoritmos e Estruturas de Dados"));
    cadeiras.insert(pair<string, string>("L.EIC012", "Bases de Dados"));
    cadeiras.insert(pair<string, string>("L.EIC013", "Física II"));
    cadeiras.insert(pair<string, string>("L.EIC014", "Laboratório de Desenho e Teste de Software"));
    cadeiras.insert(pair<string, string>("L.EIC015", "Sistemas Operativos"));
    cadeiras.insert(pair<string, string>("L.EIC016", "Desenho de Algoritmos"));
    cadeiras.insert(pair<string, string>("L.EIC017", "Engenharia de Software"));
    cadeiras.insert(pair<string, string>("L.EIC018", "Laboratório de Computadores"));
    cadeiras.insert(pair<string, string>("L.EIC019", "Linguagens e Tecnologias Web"));
    cadeiras.insert(pair<string, string>("L.EIC020", "Métodos Estatísticos"));
    cadeiras.insert(pair<string, string>("L.EIC021", "Fundamentos de Segurança Informática"));
    cadeiras.insert(pair<string, string>("L.EIC022", "Interação Pessoa Computador"));
    cadeiras.insert(pair<string, string>("L.EIC023", "Laboratório de Bases de Dados e Aplicações Web"));
    cadeiras.insert(pair<string, string>("L.EIC024", "Programação Funcional e Lógica"));
    cadeiras.insert(pair<string, string>("L.EIC025", "Redes de Computadores"));
    cadeiras.insert(pair<string, string>("L.EIC026", "Compiladores"));
    cadeiras.insert(pair<string, string>("L.EIC027", "Computação Gráfica"));
    cadeiras.insert(pair<string, string>("L.EIC028", "Computação Paralela e Distribuida"));
    cadeiras.insert(pair<string, string>("L.EIC029", "Inteligência Artificial"));
    cadeiras.insert(pair<string, string>("L.EIC030", "Projeto Integrador"));
}


Gestor::Gestor() = default;

/**
 *
 * @return Retorna a BST com os estudantes\n
 * Complexidade: O(1)
 */
set<Estudante> Gestor::getEstudantes() const{
    return estudantes;
}

/**
 *
 * @return Retorna o vetor com os horarios\n
 * Complexidade: O(1)
 */
vector<Horario> Gestor::getHorario() const{
    return horario;
}

/**
 *
 * @return Retorna a fila com os pedidos\n
 * Complexidade(1)
 */
queue<Pedido> Gestor::getPedidos() const{
    return pedidos;
}

/**
 * Método que lê o ficheiro "student_classes.csv" e cria os objetos da classe Estudante\n
 * Complexidade: O(nlog(n))
 */
void Gestor::readEstudantes() {
    vector<string> lineV(4);
    ifstream in("../schedule/students_classes.csv");
    string line, word;
    string name, codUc, codTurma;
    int sCode;

    list<UcTurma> hora;
    getline(in, line); //jump header
    while(getline(in, line)) {
        lineV.clear();
        istringstream iss(line);
        while(getline(iss, word, ',')) {
            lineV.push_back(word);
        }

        sCode = stoi(lineV[0]);
        name = lineV[1];
        codUc = lineV[2];
        codTurma = lineV[3];

        if (!codTurma.empty() && codTurma[codTurma.size() - 1] == '\r')
            codTurma.erase(codTurma.size() - 1);

        UcTurma UCTurma(codUc, codTurma);
        list<UcTurma> turma(1, UCTurma);
        Estudante student(sCode, name, turma);

        if(estudantes.find(student) == estudantes.end()) {
            estudantes.insert(student);

        } else {
            auto existing = estudantes.find(student);
            Estudante tutu(*existing);
            tutu.addUCTurma(UCTurma);
            estudantes.erase(student);
            estudantes.insert(tutu);
        }
    }
    in.close();
}

/**
 * Método que lê o ficheiro classes.csv e cria os objetos da classe Slot e adiciona-os à classe Horario correspondente\n
 * Complexidade: O(n^2)
 */
void Gestor::readHorarios() {
    readAulas();

    vector<string> lineV(6);
    ifstream in("../schedule/classes.csv");
    string classCode, ucCode, weekday, type;
    float sHour, duration;

    string line, word;

    getline(in, line); //jump header
    while(getline(in, line)) {
        lineV.clear();
        istringstream iss(line);
        while (getline(iss, word, ',')) {
            lineV.push_back(word);
        }

        classCode = lineV[0];
        ucCode = lineV[1];
        weekday = lineV[2];
        sHour = stof(lineV[3]);
        duration = stof(lineV[4]);
        type = lineV[5];

        if (!type.empty() && type[type.size() - 1] == '\r')
            type.erase(type.size() - 1);

        // Procura linear -------- mudar pra binaria
        for(Horario& hor : horario) {

            string temp1 = hor.getcodUC();
            string temp2 = hor.getcodTurma();

            if (!temp1.empty() && temp1[temp1.size() - 1] == '\r')
                temp1.erase(temp1.size() - 1);

            if (!temp2.empty() && temp2[temp2.size() - 1] == '\r')
                temp2.erase(temp2.size() - 1);

            if(temp1 == ucCode && temp2 == classCode) {
                hor.addAula(Slot(sHour, duration, weekday, type));
            }
        }
    }
    in.close();
    sort(horario.begin(), horario.end());
}

/**
 * Método que lê o ficheiro classes_per_uc.csv e cria os objetos da classe Horario\n
 * Complexidade: O(n)
 */
void Gestor::readAulas() {
    vector<string> lineV(2);
    ifstream in("../schedule/classes_per_uc.csv");
    string classCode, ucCode;

    string line, word;

    getline(in, line); //jump header
    while(getline(in, line)) {
        lineV.clear();
        istringstream iss(line);
        while (getline(iss, word, ',')) {
            lineV.push_back(word);
        }

        ucCode = lineV[0];
        classCode = lineV[1];

        if (!classCode.empty() && classCode[classCode.size() - 1] == '\r')
            classCode.erase(classCode.size() - 1);

        horario.emplace_back(ucCode, classCode);
    }
    in.close();
}

/**
 * Método que lê o ficheiro "pendentes.csv" e cria os objetos da classe Pedido. Correspondem a pedidos que ainda
 * não foram processados\n
 * O(n)
 */
void Gestor::readPedidos(){
    vector<string> lineV(4);
    ifstream in("../schedule/pendentes.csv");
    int codEstudante;
    string tipo, turmaR, turmaA, Uc;

    string line, word;

    getline(in, line);
    while(getline(in, line)){
        lineV.clear();
        istringstream iss(line);
        while (getline(iss, word, ',')){
            lineV.push_back(word);
        }
        tipo = lineV[0];
        codEstudante = stoi(lineV[1]);
        turmaR = lineV[2];
        turmaA = lineV[3];
        Uc = lineV[4];

        if (!Uc.empty() && Uc[Uc.size() - 1] == '\r')
            Uc.erase(Uc.size() - 1);

        if (tipo == "Alter"){
            vector<string> turmaRVetor = StringintoVectorClassCode(turmaR);
            vector<string> turmaAVetor = StringintoVectorClassCode(turmaA);
            vector<string> UcVetor = StringintoVectorUcCode(Uc);
            Pedido pedido = Pedido(tipo, codEstudante, turmaRVetor, turmaAVetor, UcVetor);
            pedidos.push(pedido);
        }

        else if (tipo == "Remove"){
            Pedido pedido = Pedido(tipo, codEstudante, turmaR, Uc);
            pedidos.push(pedido);
        }

        else{
            Pedido pedido = Pedido(tipo, codEstudante, turmaA, Uc);
            pedidos.push(pedido);
        }


    }

}

/**
 * Método auxiliar que transforma uma string do tipo "nLEICXYZ/nLEICXYZ..." em vários string "nLEICXYZ" (dá "split")
 * e retorna o vetor com todas essas strings em questão\n
 * Complexidade: O(n) em que n corresponde ao tamanho da string
 * @param conjunto A string que vai ser dado "split"
 * @return Retorna o vetor com todas os códigos ClassCode
 */
vector<string> Gestor::StringintoVectorClassCode(std::string conjunto) {
    vector <string> retorno;
    unsigned length = conjunto.size();
    for(unsigned i = 0; i < length; i+=8){
        string classcode = conjunto.substr(i, 7);
        retorno.push_back(classcode);
    }
    return retorno;
}

/**
 * Método auxiliar que transforma uma string do tipo "L.EICXYZ/L.EICXYZ..." em vários string "L.EICXYZ" (dá "split")
 * e retorna o vetor com todas essas strings em questão\n
 * Complexidade: O(n) em que n corresponde ao tamanho da string
 * @param conjunto A string que vai ser dado "split"
 * @return Retorna o vetor com todos os codigos UcCode
 */
vector<string> Gestor::StringintoVectorUcCode(std::string conjunto) {
    vector <string> retorno;
    unsigned length = conjunto.size();
    for(unsigned i = 0; i < length; i+=9){
        string classcode = conjunto.substr(i, 8);
        retorno.push_back(classcode);
    }
    return retorno;
}

/**
 * Adiciona à classe Horario o atributo com o número de estudantes inscritos numa UcTurma\n
 * Complexidade: O(n*m)
 */
void Gestor::fillNumEstudantes() {
    for(Horario& hor : horario) {
        hor.setNumEstudantes(countStudents(hor.getcodUC(), hor.getcodTurma()));
    }
}

/**
 * Método que conta o número de estudantes que estão inscritos numa dada UcTurma\n
 * Complexidade: O(n)
 * @param codUC Código da UC
 * @param codTurma Código da Turma
 * @return Número de estudantes que têm essa unidade curricular
 */
int Gestor::countStudents(const string& codUC, const string& codTurma) {
    int count = 0;
    for(const Estudante& student : estudantes) {
        if(studentInClass(student, codUC, codTurma)) {
            count++;
        }
    }
    return count;
}

/**
 * Método que verifica se um estudante se encontra inscrito numa dada UcTurma\n
 * Complexidade: O(n)
 * @param student Estudante a verificar
 * @param codUC Código da UC
 * @param codTurma Código da Turma
 * @return Retorna true se o estudante estiver inscrito na turma e false em qualquer outro caso
 */
bool Gestor::studentInClass(const Estudante& student, const string& codUC, string codTurma) {
    for(const UcTurma& ucTurma : student.gethorario()) {
        if(ucTurma.getcodUC() == codUC && ucTurma.getcodTurma() == codTurma) {
            return true;
        }
    }
    return false;
}

/**
 * Método que procura um estudante na BST e imprime o seu número e nome\n
 * Complexidade: O(log(n))
 * @param numero Número Mecanográfico do Estudante
 * @return O objeto Estudante com o número dado. Caso não exista vai retornar um objeto error
 */
Estudante Gestor::PesquisarEstudante(int numero) {

    list<UcTurma> temp;

    temp.push_back(UcTurma("Hello, ", "World!"));

    Estudante ghost = Estudante(numero, "error", temp);

    if (estudantes.find(ghost) == estudantes.end()) {
        cout << "Estudante não Inscrito" << "\n";
        return ghost;
    } else {
        auto existing = estudantes.find(ghost);
        Estudante verdadeiro(*existing);

        cout << "Estudante Encontrado" << "\n";
        cout << "Número de Estudante: " << numero << "\n";
        cout << "Nome: " << verdadeiro.getnome() << "\n";

        return verdadeiro;
    }
}

/**
 * Método auxiliar para ordenar pares com Slot e Turma\n
 * Complexidade: O(1)
 * @param a Primeiro par
 * @param b Segundo par
 * @return Retorna verdadeiro, se o primeiro Slot for menor do que o segundo Slot
 */
bool Gestor::cmp(pair<Slot, UcTurma>& a, pair<Slot, UcTurma>& b){
    return a.first < b.first;
}

/**
 * Método que procura um estudante na BST e imprime o seu número, nome e horário\n
 * Utiliza a função Gestor::PesquisarEstudante para auxiliar na pesquisa e a função Gestor::printHorario
 * para imprimir o horário\n
 * Complexidade: O(n*log(m))
 * @param numero Número Mecanográfico do Estudante
 */
void Gestor::HorariodoEstudante(int numero){

    Estudante student = PesquisarEstudante(numero);

    if (student.getnome() == "error"){
    }
    else{
        list<UcTurma> turmas = student.gethorario();
        vector<pair<Slot, UcTurma>> mondays;
        vector<pair<Slot, UcTurma>> tuesdays;
        vector<pair<Slot, UcTurma>> wednesdays;
        vector<pair<Slot, UcTurma>> thursdays;
        vector<pair<Slot, UcTurma>> fridays;

        for (UcTurma turma : turmas){
            list<Slot> k;
            Horario temp = getHorariobyUcTurma(turma);
            for (Slot i : temp.getaulas()){
                if (i.getDiaDaSemana() == "Monday")
                    mondays.push_back(pair<Slot, UcTurma>(i, turma));
                else if (i.getDiaDaSemana() == "Tuesday")
                    tuesdays.push_back(pair<Slot, UcTurma>(i, turma));
                else if (i.getDiaDaSemana() == "Wednesday")
                    wednesdays.push_back(pair<Slot, UcTurma>(i, turma));
                else if (i.getDiaDaSemana() == "Thursday")
                    thursdays.push_back(pair<Slot, UcTurma>(i, turma));
                else if (i.getDiaDaSemana() == "Friday")
                    fridays.push_back(pair<Slot, UcTurma>(i, turma));
                    }
        }

        sort(mondays.begin(), mondays.end(), cmp);
        sort(tuesdays.begin(), tuesdays.end(), cmp);
        sort(wednesdays.begin(), wednesdays.end(), cmp);
        sort(thursdays.begin(), thursdays.end(), cmp);
        sort(fridays.begin(), fridays.end(), cmp);


        cout << "=====================================" << "\n";
        cout << "Segunda-Feira: ";

        printHorario(mondays, cadeiras);

        cout << "Terça-Feira: ";

        printHorario(tuesdays, cadeiras);

        cout << " " << "\n";
        cout << "Quarta-Feira: ";

        printHorario(wednesdays, cadeiras);

        cout <<" " << "\n";
        cout << "Quinta-Feira: ";

        printHorario(thursdays, cadeiras);

        cout << " " << "\n";
        cout << "Sexta-Feira: ";

        printHorario(fridays, cadeiras);
    }
}

/**
 * Função auxiliar para imprimir um dado horário\n
 * Complexidade: O(n)
 * @param vetor Vetor de pair<Slot, Turma> (já ordenado)
 * @param cadeiras Mapa para fazer corresponder o código da UC ao seu nome
 */
void Gestor::printHorario(const vector<pair<Slot, UcTurma>>& vetor, map<string, string> cadeiras){
    for (const pair<Slot, UcTurma>& i : vetor){
        cout << i.first.gethoraini() << "-" << i.first.getduaracao() + i.first.gethoraini()
             << " -> " << i.first.gettipo() << " - " << cadeiras[i.second.getcodUC()] << "(" <<
             i.second.getcodUC() << ")" << " - "<<  i.second.getcodTurma() << "\n";
        cout << "               ";
    }
    cout << " " << "\n";
}

/**
 * Função que dado um objeto UcTurma, retorna o objeto Horario homólogo, usando pesquisa binária\n
 * Complexidade: O(log(n))
 * @param turma Objeto da classe UcTurma
 * @return Objeto da classe Horario
 */
Horario Gestor::getHorariobyUcTurma(const UcTurma& turma){
    list<Slot> lista;
    Horario temp = Horario(turma.getcodUC(), turma.getcodTurma(), lista);
    std::vector<int>::iterator it;
    int low = 0;
    int high= horario.size()-1;
    int middle;
    while (low < high){
        middle = low + (high - low) / 2;
        if (horario[middle] < temp) low = middle+1;
        else high = middle;
    }
    middle = low + (high - low) / 2;
    if (horario[middle] == temp) return horario[middle];
    else return temp;
}

/**
 * Struct auxiliar para ordenar o set de estudantes por ordem alfabética\n
 * Complexidade: O(1)
 */
struct ordemAlfabeticaStruct {

    bool operator()(Estudante const &student1, Estudante const &student2) const{

        if (student1.getnome() == student2.getnome())         {
            return student1.getcodigo() < student2.getcodigo();
        }
        else return student1.getnome() < student2.getnome();
    }
};

/**
 * Struct auxiliar para ordenar o set de estudantes por ordem de número de UC's\n
 * Complexidade: O(1)
 */
struct ordemNumUcStruct{

    bool operator()(Estudante const &student1, Estudante const &student2) const{

        if (student1.gethorario().size() == student2.gethorario().size()){
            return student1.getcodigo() < student2.getcodigo() ;
        }
        else return student1.gethorario().size() < student2.gethorario().size();
    }

};

/**
 * Método que imprime todos os estudantes com mais de n UC's por ordem alfabética\n
 * Complexidade: O(nlog(n))
 * @param n
 */
void Gestor::maisNUcsAlfabetico(int n) {
    set<Estudante, ordemAlfabeticaStruct> temp(estudantes.begin(), estudantes.end());
    set<Estudante>::iterator it;
    cout << "Id|Nome|n" << "\n";
    for (it = temp.begin(); it != temp.end(); it++) {
        if (it->gethorario().size() >= n){
            cout << it->getcodigo() << "|" << it->getnome() << "|" << it->gethorario().size() <<"\n";
        }
    }
}

/**
 * Método que imprime todos os estudantes com mais de n UC's por ordem crescente do número de UC's\n
 * Complexidade: O(nlog(n))
 * @param n
 */
void Gestor::maisNUcsNumero(int n){
    set<Estudante, ordemNumUcStruct> temp(estudantes.begin(), estudantes.end());
    set<Estudante>::iterator it;
    cout << "Id|Nome|n" << "\n";
    for (it = temp.begin(); it != temp.end(); it++){
        if(it->gethorario().size() >= n){
            cout << it->getcodigo() << "|" << it->getnome() << "|" << it->gethorario().size() << "\n";
        }
    }
}

/**
 * Método que imprime todos os estudantes com mais de n UC's por ordem crescente de número mecanográfico\n
 * Complexidade: O(n)
 * @param n
 */
void Gestor::maisNUcs(int n){
   set<Estudante>::iterator it;
   cout << "Id|Nome|n" << "\n";
   for (it = estudantes.begin(); it != estudantes.end(); it++){
       if (it->gethorario().size() >= n){
             cout << it->getcodigo() << "|" << it->getnome() << "|" << it->gethorario().size() << "\n";
       }
   }
}

/**
 * Procura um estudante por code. Retorna o const iterator.\n
 * Complexidade: O(log(n))
 * @param code Número Mecanográfico do Estudante
 * @return Iterador do Estudante
 */

set<Estudante>::iterator Gestor::searchStudent(int code) {
    list<UcTurma> temp;
    temp.emplace_back("", "");
    Estudante ghost = Estudante(code, "", temp);
    return estudantes.find(ghost);
}

/**
 * Método auxiliar que dado um objeto da classe Pedido, imprime as características importantes do mesmo\n
 * Complexidade: O(1)
 */
void Gestor::printPedido() {
    cout << '\n';
    cout << "Aluno: " << pedidos.front().getcodigo_estudante() << '\n';
    cout << "Tipo: " << pedidos.front().getTipo() << '\n';
    if(pedidos.front().getTipo() != "Alter") {
        cout << "Turma: " << pedidos.front().getTurmaR().front() << '\n';
        cout << "UC: " << pedidos.front().getUCs().front() << " (" << cadeiras[pedidos.front().getUCs().front()] << ")" << '\n';
    } else {
        for(int i = 0; i < pedidos.front().getUCs().size(); i++) {
            cout << "Turma: " << pedidos.front().getTurmaA().at(i);
            cout << " -> " << pedidos.front().getTurmaR().at(i) << '\n';
            cout << "UC: " << pedidos.front().getUCs().at(i) << " ("<<cadeiras[pedidos.front().getUCs().at(i)] << ")" << '\n';
        }
    }

}

/**
 * Verifica o primeiro pedido da fila\n
 * Complexidade: O(n)
 * @return Retorna true nos casos em que o Pedido obedece às restrições
 */
bool Gestor::verifyPedido() {
    if(pedidos.front().getTipo() == "Add")
        return verifyAdd();
    if(pedidos.front().getTipo() == "Alter")
        return verifyAlter();
    return true;
}

/**
 * Verifica o primeiro pedido da fila, se o mesmo for um pedido do tipo "Add"
 * @return Retorna true nos casos em que o Pedido obedece às restrições
 */
bool Gestor::verifyAdd() {
    int studentCode = pedidos.front().getcodigo_estudante();
    string uc = pedidos.front().getUCs().front();
    string turma = pedidos.front().getTurmaR().front();
    UcTurma ucTurma = UcTurma(uc, turma);
    auto studentIt = searchStudent(studentCode);
    Estudante student(*studentIt);
    student.addUCTurma(ucTurma);
    list<UcTurma> turmas = student.gethorario();
    list<Horario> studentHor = getHorario(turmas);
    vector<Horario> temp(horario);
    vector<UcTurma> toAdd(1, ucTurma);
    vector<UcTurma> toRem;

    return verifyOverlap(studentHor) && verifyClasses(temp, toAdd, toRem) && verifyCap(ucTurma);
}

/**
 * Verifica o primeiro pedido da fila, se o mesmo for um pedido do tipo "Alter"
 * @return Retorna true nos casos em que o Pedido obedece às restrições
 */
bool Gestor::verifyAlter() {
    int studentCode = pedidos.front().getcodigo_estudante();
    vector<string> uCs = pedidos.front().getUCs();
    vector<string> turmaR = pedidos.front().getTurmaR();
    vector<string> turmaA = pedidos.front().getTurmaA();

    auto studentIt = searchStudent(studentCode);
    Estudante student(*studentIt);

    vector<Horario> temp(horario);
    vector<UcTurma> toAdd;
    vector<UcTurma> toRem;

    for(int i = 0; i < uCs.size(); i++) {
        string uc = uCs.at(i);
        string turmaRem = turmaR.at(i);
        string turmaAdd = turmaA.at(i);

        student.addUCTurma(UcTurma(uc, turmaAdd));
        toAdd.emplace_back(uc, turmaAdd);
        student.delUCTurma(UcTurma(uc, turmaRem));
        toRem.emplace_back(uc, turmaRem);
    }

    list<UcTurma> turmas = student.gethorario();
    list<Horario> studentHor = getHorario(turmas);
    return verifyOverlap(studentHor) && verifyClasses(temp, toAdd, toRem) && verifyCapvector(toAdd);
}

/**
 * Rejeita um pedido, independentemente se passa, ou não, nas restriçoes.\n
 * Quando invocado, arquiva o Pedido e retira-o da fila
 * Complexidade: O(1)
 */
void Gestor::rejeitarPedido() {
    arquivar(false);
    pedidos.pop();
}

/**
 * Aceita um pedido, independentemente se passa, ou não, nas restriçoes.\n
 * Quando invocado, arquiva o Pedido, retira-o da fila e faz as alterações nos atributos para continuar coerente\n
 * Complexidade: O(n) em que n é o número de horários existentes (constante)
 */
void Gestor::aceitarPedido() {
    arquivar(true);
    if(pedidos.front().getTipo() == "Add")
        pedidoAdd();
    if(pedidos.front().getTipo() == "Remove")
        pedidoRemove();
    if(pedidos.front().getTipo() == "Alter")
        pedidoAlter();
    pedidos.pop();
}

/**
 * Permite adicionar um Pedido do tipo "Add", sobre várias restriçoes(Estudante existir, UcTurma existir...).
 *  Esse Pedido é adicionado à fila pedidos\n
 *  Complexidade: O(log(n)*m)
 */
void Gestor::addPedidoAdd() {
    int codigo_estudante;
    string turmaA;
    string uC;
    cout << '\n';
    cout << "Codigo de estudante: ";
    cin >> codigo_estudante;
    cout << '\n';
    if (searchStudent(codigo_estudante) == estudantes.end()) {
        cout << "Estudante não inscrito" << "\n";
    } else {
        cout << "UC: ";
        cin >> uC;
        cout << '\n';
        cout << "Turma: ";
        cin >> turmaA;
        cout << '\n';
        list<Slot> temp;
        Horario teste = Horario(uC, turmaA, temp);
        if(find(horario.begin(), horario.end(), teste) == horario.end()) {
            cout << "Par UC/Turma não existente" << "\n";
        }else{
            UcTurma temp2 = UcTurma(uC, turmaA);
            int help = searchStudent(codigo_estudante)->naTurma(temp2);
            if(help == -1) {
                pedidos.push(Pedido("Add", codigo_estudante, turmaA, uC));
                cout << "Pedido adicionado com sucesso" << "\n";
            }
            else if (help == 0){
                cout << "Estudante já inscrito na turma" << "\n";
            }
            else {
                cout << "Estudante inscrito na UC, noutra Turma (pedir alteração)" << "\n";
            }
        }
    }
}

/**
 *  Permite adicionar um Pedido do tipo "Rem", sobre várias restriçoes(Estudante existir, UcTurma existir...).
 *  Esse Pedido é adicionado à fila pedidos\n
 *  Complexidade: O(log(n)*m)
 */
void Gestor::addPedidoRem() {
    int codigo_estudante;
    string turmaR;
    string uC;
    cout << '\n';
    cout << "Codigo de estudante: ";
    cin >> codigo_estudante;
    cout << '\n';
    if (searchStudent(codigo_estudante) == estudantes.end()){
        cout << "Estudante não inscrito" << "\n";
    }else {
        cout << "UC: ";
        cin >> uC;
        cout << '\n';
        cout << "Turma: ";
        cin >> turmaR;
        cout << '\n';
        list<Slot> temp;
        Horario teste = Horario(uC, turmaR, temp);
        if (find(horario.begin(), horario.end(), teste) == horario.end()){
            cout << "Par UC/Turma não existente" << "\n";
        }
        else {
            UcTurma temp2 = UcTurma(uC, turmaR);
            int help = searchStudent(codigo_estudante)->naTurma(temp2);
            if(help == 0) {
                pedidos.push(Pedido("Remove", codigo_estudante, turmaR, uC));
                cout << "Pedido adicionado com sucesso" << "\n";
            }else if (help == 1){
                cout << "Estudante está inscrito na UC, mas encontra-se noutra turma (consultar horário)" << "\n";
            }else{
                cout << "Estudante não inscrito na UC" << "\n";
            }
        }
    }

}

/**
 *  Permite adicionar um Pedido do tipo "Alter", sobre várias restriçoes(Estudante existir, UcTurma existir...).
 *  Esse Pedido é adicionado à fila pedidos\n
 *  Complexidade: O(log(n)*m)
 */
void Gestor::addPedidoAlt() {
    int codigo_estudante;
    string turmaA;
    string turmaR;
    vector<string> turmasA;
    vector<string> turmasR;
    vector<string> uCs;
    string uC;
    char op1 = ' ';
    cout << '\n';
    cout << "Codigo de estudante: ";
    cin >> codigo_estudante;
    cout << '\n';
    if (searchStudent(codigo_estudante)!=estudantes.end()) {
        while (op1 != 'q') {
            cout << '\n';
            cout << "UC: ";
            cin >> uC;
            cout << '\n';
            cout << "Turma antiga: ";
            cin >> turmaA;
            cout << '\n';
            cout << "Turma nova: ";
            cin >> turmaR;
            cout << '\n';
            list<Slot> temp;
            Horario teste1 = Horario(uC, turmaA, temp);
            Horario teste2 = Horario(uC, turmaR, temp);
            if ((find(horario.begin(), horario.end(), teste1) == horario.end()) && (find(horario.begin(), horario.end(), teste2) == horario.end())) {
                 cout << "Par UC/Turma não existente" << "\n";
            } else {
                UcTurma temp2 = UcTurma(uC, turmaA);
                int help1 = searchStudent(codigo_estudante)->naTurma(temp2);

                UcTurma temp3 = UcTurma(uC, turmaR);
                int help2 = searchStudent(codigo_estudante)->naTurma(temp3);

                if (help1 == -1){
                    cout << "Estudante não inscrito na " << uC << "\n";
                }

                else{
                    if (help1 == 0 && help2 == 1) {
                        turmasA.push_back(turmaA);
                        turmasR.push_back(turmaR);
                        uCs.push_back(uC);
                        cout << "Adicionado ao pedido" << "\n";
                    }

                    else if (help1 == 1 && help2==0){
                        cout << "Estudante encontra-se inscrito na " << turmaA << " e não na " << turmaR << "\n" << "Não é necessário fazer nada" << "\n";
                    }

                    else if (help1 == 1 && help2 == 1){
                        cout << "O estudante não se encontra inscrito na turma " << turmaR << "\n" << "Não ºé possível realizar a operação" << "\n";
                    }

                    else if (help2 == 0 && help2 == 0){
                        cout << "!!Erro!!" << "\n" << "O estudante encontra-se em duas turmas diferentes, necessária remoção de uma delas" << "\n";
                    }
                }
            }
            cout << '\n' << "Digite 'q' se tiver concluido pedido, 's' se quiser continuar" << '\n';
            cout << "?";
            cin >> op1;
            cout << "\n";

        }
        Pedido ajuda = Pedido("Alter", codigo_estudante, turmasR, turmasA, uCs);
        pedidos.push(Pedido("Alter", codigo_estudante, turmasR, turmasA, uCs));
    } else{
        cout << "Estudante não inscrito" << "\n";
    }
}

/**
 * Este método arquiva o primerio pedido da fila, guardando-o no ficheiro "arquivo.csv"\n
 * Complexidade: O(1)
 * @param aceite Valor booleano que se refere se o pedido foi(true), ou não(false) aceite
 */
void Gestor::arquivar(bool aceite) {

    string estado = aceite ? "Aceite" : "Rejeitado";
    string tipo = pedidos.front().getTipo();
    int cod = pedidos.front().getcodigo_estudante();
    vector<string> turmaR = pedidos.front().getTurmaR();
    vector<string> turmaA = pedidos.front().getTurmaA();
    vector<string> ucs = pedidos.front().getUCs();
    ofstream file("../schedule/arquivo.csv", ios::app);
    if(tipo == "Add") {
        file << estado << ',' << cod << ',' << "" << ',' << turmaR.front() << ',' << ucs.front() << endl;
    }
    if(tipo == "Remove") {
        file << estado << ',' << cod << ',' << turmaR.front() << ',' << "" << ',' << ucs.front() << endl;
    }
    if(tipo == "Alter") {
        for(int i = 0; i < ucs.size(); i++) {
            file << estado << ',' << cod << ',' << turmaR.at(i) << ',' << turmaA.at(i) << ',' << ucs.at(i) << endl;
        }
    }
}

/**
 * Este método escreve os pedidos que ainda não foram processados no ficheiro "pendentes.csv", para
 * poderem ser guardados quando a aplicação fecha, e lidos quando a aplicação é reiniciada\n
 * Complexidade: O(n)
 */
void Gestor::writePedidosPendentes(){
    ofstream file("../schedule/pendentes.csv");
    string tipo;
    int cod;
    vector<string> turmaR;
    vector<string> turmaA;
    vector<string> ucs;

    while(!pedidos.empty()) {
        string tipo = pedidos.front().getTipo();
        cod = pedidos.front().getcodigo_estudante();
        turmaR = pedidos.front().getTurmaR();
        turmaA = pedidos.front().getTurmaA();
        ucs = pedidos.front().getUCs();

        file << "Tipo,Número,Remover,Adicionar,UC" << endl;
        if (tipo == "Add") {
            file << tipo << ',' << cod << ',' << "" << ',' << turmaR.front() << ',' << ucs.front() << endl;
        }
        if (tipo == "Remove") {
            file << tipo << ',' << cod << ',' << turmaR.front() << ',' << "" << ',' << ucs.front() << endl;
        }
        if (tipo == "Alter") {

            file << tipo << ',' << cod << ',' << VectorintoString(turmaR) << ',' << VectorintoString(turmaA) << ','
                 << VectorintoString(ucs) << endl;
        }
        pedidos.pop();
    }
    file.close();
}

/**
 * Método auxiliar, que transforma um vetor de strings numa string só, separada com "/"\n
 * Complexidade: O(n)
 * @param vetor Vetor com a string
 * @return Retorna a string concatenada
 */
string Gestor::VectorintoString(vector<std::string> vetor) {
    int length = vetor.size();
    string temp = "";
    for (unsigned i = 0; i < length-1; i++){
        temp = temp + vetor[i];
        temp = temp + "/";
    }
    temp = temp + vetor[length-1];
    temp = temp +  "";
    return temp;
}

/**
 * Processa os pedidos de adicionar um aluno a uma UC/Turma.\n
 * Complexidade: O(nlog(n))
 * Verifica se o novo horario cumpre as condiçoes
 */
void Gestor::pedidoAdd() {
    int studentCode = pedidos.front().getcodigo_estudante();
    string uc = pedidos.front().getUCs().front();
    string turma = pedidos.front().getTurmaR().front();

    auto studentIt = searchStudent(studentCode);
    for(Horario& hor : horario) {
        if(hor.getcodTurma() == turma && hor.getcodUC() == uc){
            hor.incrementS();
            break;
        }
    }
    string istoeumnome = "nome";
    list<UcTurma> istoeumhorario;
    Estudante tmp = Estudante(studentCode, istoeumnome, istoeumhorario);
    auto existing = estudantes.find(tmp);
    Estudante tutu(*existing);
    tutu.addUCTurma(UcTurma(uc, turma));
    estudantes.erase(existing);
    estudantes.insert(tutu);
}

/**
 * Processa os pedidos de remoção do aluno de uma UC/Turma\n
 * Complexidade: O(nlog(n))
 */
void Gestor::pedidoRemove() {
    int studentCode = pedidos.front().getcodigo_estudante();
    string uc = pedidos.front().getUCs().front();
    string turma = pedidos.front().getTurmaR().front();

    auto studentIt = searchStudent(studentCode);
    if(studentIt == estudantes.end()) return;
    for(Horario& hor : horario) {
        if(hor.getcodTurma() == turma && hor.getcodUC() == uc){
            hor.decrementS();
            break;
        }
    }

    string istoeumnome = "nome";
    list<UcTurma> istoeumhorario;
    Estudante tmp = Estudante(studentCode, istoeumnome, istoeumhorario);

    auto existing = estudantes.find(tmp);

    Estudante tutu(*existing);
    tutu.delUCTurma(UcTurma(uc, turma));
    estudantes.erase(existing);
    estudantes.insert(tutu);
}

/**
 * Processa os pedidos de alterar a ucs de UCs.
 * Verifica se o novo horário cumpre as condições\n
 * Complexidade: O(nlog(n)*m)
 */
void Gestor::pedidoAlter() {
    int studentCode = pedidos.front().getcodigo_estudante();
    vector<string> uCs = pedidos.front().getUCs();
    vector<string> turmaR = pedidos.front().getTurmaR();
    vector<string> turmaA = pedidos.front().getTurmaA();

    string istoeumnome = "nome";
    list<UcTurma> istoeumhorario;
    Estudante tmp = Estudante(studentCode, istoeumnome, istoeumhorario);
    auto studentIt = estudantes.find(tmp);

    if(studentIt == estudantes.end()) return;
    Estudante student(*studentIt);


    for(int i = 0; i < uCs.size(); i++) {
        string uc = uCs[i];
        string turmaRem = turmaR[i];
        string turmaAdd = turmaA[i];
        for(Horario& hor : horario) {
            if(hor.getcodTurma() == turmaRem && hor.getcodUC() == uc)
                hor.incrementS();
            if(hor.getcodTurma() == turmaAdd && hor.getcodUC() == uc)
                hor.decrementS();
        }

        student.addUCTurma(UcTurma(uc, turmaRem));
        student.delUCTurma(UcTurma(uc, turmaAdd));
    }

    estudantes.erase(studentIt);
    estudantes.insert(student);
}

/**
 * Este ficheiro limpa o ficheiro "student_classes.csv", para voltar a escrevê-lo com as alterações feitas, guardando assim,
 * as alterações quando o programa termina\n
 * Complexidade: O(n)
 */
void Gestor::writeEstudantes() {
    ofstream file("../schedule/students_classes.csv");
    file << "StudentCode,StudentName,UcCode,ClassCode" << endl;
    for(Estudante estudante : estudantes) {
        string nome = estudante.getnome();
        int codigo = estudante.getcodigo();
        list<UcTurma> turmas = estudante.gethorario();
        for(const UcTurma& ucTurma : turmas) {
            string codUC =  ucTurma.getcodUC();
            string turma = ucTurma.getcodTurma();
            file << codigo << ',' << nome << ',' << codUC << ',' << turma << endl;
        }
    }
}

/**
 * Retorna uma lista de Horarios correspondentes as UcTurmas
 * passadas por parametro\n
 * Complexidade: O(nlog(m))
 * @param turmas lista com todas as UcTurma
 * @return lista com todas os Horario homólogos à UcTurma
 */
list<Horario> Gestor::getHorario(const list<UcTurma>& turmas) {
    list<Horario> hor;
    for(const UcTurma& ucTurma : turmas) {
        hor.push_back(getHorariobyUcTurma(ucTurma));
    }
    return hor;
}
/**
 * Verifica que o numero de alunos não passou de CAP
 * @param turma Objeto da classe UcTurma a ser verficado
 * @return Retorna true, se houver menos estudantes na turma, do que a capacidade máxima desta\n
 * Complexidade: O(log(m)) em que m é o número de Horários
 */
bool Gestor::verifyCap(UcTurma turma) {
    Horario horario = getHorariobyUcTurma(turma);
    if (horario.getNumEstudantes()+1 > turma.getCap()) return false;
    else return true;
}

/**
 * Verifica que o número de alunos não superou o CAP, num vetor de UcTurma
 * @param turma Vetor de UcTurma
 * @return Retorna true, todas as turmas não estiverem com mais alunos do que o seu Cap\n
 * Complexidade: O(nlog(m)) em que m é o número de horários
 */
bool Gestor::verifyCapvector(vector<UcTurma> turma){
    for (UcTurma i : turma){
        if (!Gestor::verifyCap(i)){
            return false;
        }
    }
    return true;
}


/**
 * Verifca se a sobreposições de horarios\n
 * Complexidade: O(n^2)
 * @param horario A lista de Horario a verificar
 * @return Falso se houver sobreposição, verdadeiro em qualquer outro caso
 */
bool Gestor::verifyOverlap(const list<Horario>& horario)  {
    list<Slot> slots = getSlots(horario);
    filterTP(slots);
    for(auto it1 = slots.begin(); it1 != slots.end(); it1++) {
        auto it2 = it1;
        for(auto it2=it1; it2 != slots.end(); it2++) {
            if(it1->getDiaDaSemana() == it2->getDiaDaSemana()) {
                float start1 = it1->gethoraini(), start2 = it2->gethoraini();
                float end1 = start1 + it1->getduaracao(), end2 = start2 + it2->getduaracao();
                if(start2 < end1 && start1 < end2 ) return false;
            }
        }
    }

    return true;
}

/**
 * Cria lista com todos os Slot de uma lista
 * de Horarios\n
 * Complexidade: O(n*m)
 * @param horario Lista de objetos Horario
 * @return Lista com todos os Slot contidos em cada objeto Horario na lista passada por parâmetro
 */
list<Slot> Gestor::getSlots(const list<Horario>& horario) {
    list<Slot> slots;
    for(const Horario& hor : horario) {
        for(const Slot& slot : hor.getaulas()) {
            slots.push_back(slot);
        }
    }
    return slots;
}

/**
 * Retira slots que não correspondam a aulas TP
 * Complexidade: O(n)
 * @param horario lista de Slot (associado a uma UC)
 */
void Gestor::filterTP(list<Slot>& horario) {
    auto it = horario.begin();
    while(it != horario.end()) {
        if(it->gettipo() != "TP") {
            it = horario.erase(it);
        } else {
            it++;
        }
    }
}

/**
 * Verifica se não há desiquilibrio entre turmas\n
 * Complexidade: O(n)
 * @param temp Horario a ser verificado
 * @param toAdd Turmas que se pretendem adicionar ao horário
 * @param toRem Turmas que se pretendem remover ao horºario
 * @return Retorna true se não houver desiquilibrio entre turmas
 */
bool Gestor::verifyClasses(vector<Horario> temp, vector<UcTurma> toAdd, vector<UcTurma> toRem){
    list<string> ucs;

    for(Horario& hor : temp) {
        if(containsUC(hor, toAdd)) hor.incrementS();
        else if(containsUC(hor, toRem)) hor.decrementS();
        if(find(ucs.begin(), ucs.end(), hor.getcodUC()) == ucs.end()){
            ucs.push_back(hor.getcodUC());
        }
    }

    return testCap(temp, ucs);
}

/**
 * Verifica se não há desiquilibrio entre as turmas\n
 * Complexidade: O(n*m)
 * @param temp Horário a ser verificado
 * @param ucs Unidades curriculares onde ocorreram as mudanças de turma
 * @return Retorna falso se pelo menos uma UC estiver em desiquilibrio, retorna verdadeiro em qualquer outro caso
 */
bool Gestor::testCap(const vector<Horario>& temp, const list<string>& ucs) {
    vector<int> numeroEstudantes;
    for(const string& uc : ucs) {
        numeroEstudantes.clear();
        for(const Horario& hor : temp) {
            if(hor.getcodUC() == uc)
                numeroEstudantes.push_back(hor.getNumEstudantes());
        }
        if(numeroEstudantes.size() > 1) {
            sort(numeroEstudantes.begin(), numeroEstudantes.end());
            if (abs(numeroEstudantes.back() - numeroEstudantes.front()) >= 4)
                return false;
        }
    }
    return true;
}

/**
 * Método que verifica se um objeto Horario está contido num vetor de UcTurma, usando o objeto UcTurma homólogo\n
 * Complexidade: O(n)
 * @param horario Objeto da classe Horário a ser verificado
 * @param ucTurmas Vetor de verificação
 * @return Retorna verdadeiro, se o horário pertencer ao vetor e falso caso contrário
 */
bool Gestor::containsUC(const Horario& horario, vector<UcTurma>& ucTurmas) {
    auto it = ucTurmas.begin();
    while (it != ucTurmas.end()) {
        if(it->getcodUC() == horario.getcodUC() && it->getcodTurma() == horario.getcodTurma()) {
            ucTurmas.erase(it);
            return true;
        }
        it++;
    }
    return false;
}


