#include <iostream>
#include <cstdlib> // permite acessar rand, para gerar numeros aleatorios
#include <ctime> // permite acessar time, para acessar o horario da maquina e a partir da "seed" do horario acessado novos numeros são gerados

#define MAX 10

using namespace std;

// tutor
struct Tutor {
    int id;
    string nome;
    string endereco;
};

// animal
struct Animal {
    int id;
    string nome;
    string especie;
    int idade;
    int idTutor;
};

// mostrar menu
void mostrarMenu() {
    cout << "\n############ MENU ############\n";
    cout << "1 - Cadastrar tutor\n";
    cout << "2 - Cadastrar animal\n";
    cout << "3 - Listar tutores\n";
    cout << "4 - Listar animais\n";
    cout << "5 - Buscar animais por tutor\n";
    cout << "6 - Relatorio geral\n";
    cout << "7 - Sair\n";
    cout << "##############################\n";
    cout << "Digite sua opcao: ";
}

// ver se o id tem um tutor correspondente
bool existeTutor(Tutor vet[], int n, int id) {
    for (int i = 0; i < n; i++) {
        if (vet[i].id == id) {
            return true;
        }
    }

    return false;
}

// função que gera id aleatorio p/ tutor
int gerarID(Tutor vet[], int n) {
    int id;

    do {
        id = rand() % 9000 + 1000; //resultado entre 1000 e 9999

    } while (existeTutor(vet, n, id));

    return id;
}

// valida tem esse animal cadastrado
bool existeAnimal(Animal vet[], int n, int id) { // bool = armazena true/false
    for (int i = 0; i < n; i++) {
        if (vet[i].id == id) {
            return true;
        }
    }

    return false;
}

// função que gera id aleatorio p/ bicho
int gerarCodigoAnimal(Animal vet[], int n) {
    int codigo;

    do {
        codigo = rand() % 9000 + 1000;

    } while (existeAnimal(vet, n, codigo));

    return codigo;
}

// cad do tutor
void CadTutor(Tutor vet[], int i, int id) {

    vet[i].id = id;

    cin.ignore();

    cout << "Digite o nome do tutor: ";
    getline(cin, vet[i].nome);

    cout << "Digite o endereco do tutor: ";
    getline(cin, vet[i].endereco);

    cout << "\nTutor cadastrado com sucesso!\n";
    cout << "ID gerado: " << vet[i].id << endl;
}

// cad do animal
bool CadAnimal(Animal vet[], int i, Tutor tutores[], int n) {

    if (n == 0) {
        cout << "Cadastre um tutor primeiro!\n"; // se tentar cadastrar o animall antes do tutor
        return false;
    }

    // gerad codigo aleatorio
    vet[i].id = gerarCodigoAnimal(vet, i);

    cout << "Codigo do animal gerado: "
         << vet[i].id << endl;

    cin.ignore();

    cout << "Digite o nome do animal: ";
    getline(cin, vet[i].nome);

    cout << "Digite a especie: ";
    getline(cin, vet[i].especie);

    cout << "Digite a idade: ";
    cin >> vet[i].idade;

    cout << "Digite o ID do tutor: ";
    cin >> vet[i].idTutor;

    // valida se o tutor ta cadastrado/existe
    if (!existeTutor(tutores, n, vet[i].idTutor)) {
        cout << "Tutor nao encontrado! Cadastro cancelado.\n";
        return false;
    }

    cout << "\nAnimal cadastrado com sucesso!\n";

    return true;
}

// listar tutores
void mostrarTutores(Tutor vet[], int n) {

    if (n == 0) {
        cout << "Nenhum tutor cadastrado.\n";
        return;
    }

    for (int i = 0; i < n; i++) {

        cout << "\n-----------------------------\n";
        cout << "ID: " << vet[i].id << endl;
        cout << "Nome: " << vet[i].nome << endl;
        cout << "Endereco: " << vet[i].endereco << endl;
    }

    cout << "-----------------------------\n";
}

// listar animais e os seus tutores
void mostrarAnimais(Animal vet[], int n,
                    Tutor tutores[], int qtdTutores) {

    if (n == 0) {
        cout << "Nenhum animal cadastrado.\n";
        return;
    }

    for (int i = 0; i < n; i++) {

        cout << "\n-----------------------------\n";
        cout << "Codigo: " << vet[i].id << endl;
        cout << "Nome: " << vet[i].nome << endl;
        cout << "Especie: " << vet[i].especie << endl;
        cout << "Idade: " << vet[i].idade << endl;

        for (int j = 0; j < qtdTutores; j++) {

            if (vet[i].idTutor == tutores[j].id) {
                cout << "Tutor: " << tutores[j].nome << endl;
                break;
            }
        }
    }

    cout << "-----------------------------\n";
}

// buscar animal pelo id do tutor
void buscarAnimais(Animal vet[], int n,
                   Tutor tutores[], int qtdTutores) {

    int id;
    bool encontrou = false;

    cout << "Digite o ID do tutor: ";
    cin >> id;

    if (!existeTutor(tutores, qtdTutores, id)) {
        cout << "Tutor nao encontrado!\n";
        return;
    }

    cout << "\nAnimais do tutor:\n";

    for (int i = 0; i < n; i++) {

        if (vet[i].idTutor == id) {

            cout << "\nCodigo: " << vet[i].id << endl;
            cout << "Nome: " << vet[i].nome << endl;
            cout << "Especie: " << vet[i].especie << endl;
            cout << "Idade: " << vet[i].idade << endl;

            encontrou = true;
        }
    }

    if (!encontrou) {
        cout << "Esse tutor ainda nao possui animais cadastrados.\n";
    }
}

// relatorio geral
void relatorioGeral(Tutor tutores[], int qtdTutores,
                    Animal animais[], int qtdAnimais) {

    if (qtdTutores == 0) {
        cout << "Ainda nao temos cadastros.\n";
        return;
    }

    for (int i = 0; i < qtdTutores; i++) {

        int quantidade = 0;

        for (int j = 0; j < qtdAnimais; j++) {

            if (animais[j].idTutor == tutores[i].id) {
                quantidade++;
            }
        }

        cout << "\n-----------------------------\n";
        cout << "Tutor: " << tutores[i].nome << endl;
        cout << "ID: " << tutores[i].id << endl;
        cout << "Quantidade de animais: "
             << quantidade << endl;
    }

    cout << "-----------------------------\n";
}

int main() {

    // inicia gerador de numeros aleatorios
    srand(time(0));

    Tutor listaTutor[MAX];
    Animal listaAnimal[MAX];

    // para os contadores iniciarem sempre em 0
    int contTutores = 0;
    int contAnimais = 0;
    int opcao;

    while (true) {

        mostrarMenu();
        cin >> opcao;

        switch (opcao) {

            case 1:
                if (contTutores < MAX) {

                    int id = gerarID(listaTutor, contTutores);

                    CadTutor(listaTutor, contTutores, id);

                    contTutores++;

                } else {
                    cout << "Limite de tutores atingido!\n";
                }
                break;

            case 2:
                if (contAnimais < MAX) {

                    if (CadAnimal(listaAnimal, contAnimais,
                                  listaTutor, contTutores)) {

                        contAnimais++;
                    }

                } else {
                    cout << "Limite de animais atingido!\n";
                }
                break;

            case 3:
                mostrarTutores(listaTutor, contTutores);
                break;

            case 4:
                mostrarAnimais(listaAnimal, contAnimais,
                               listaTutor, contTutores);
                break;

            case 5:
                buscarAnimais(listaAnimal, contAnimais,
                              listaTutor, contTutores);
                break;

            case 6:
                relatorioGeral(listaTutor, contTutores,
                               listaAnimal, contAnimais);
                break;

            case 7:
                cout << "Programa encerrado.";
                return 0;

            default:
                cout << "Opcao invalida.\n";
                break;
        }
    }

    return 0;
}
