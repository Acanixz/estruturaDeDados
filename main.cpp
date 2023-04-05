// Manipulador de polinômios
// Aluno: Hérick Vitor Vieira Bittencourt
// Estrutura de dados 2023
// TODO: remover pragma regions

#include <iostream>
#include <math.h>
#include <windows.h> // usado para pausas
#include <string>
#include "parte1.h"
#define UseCLS false // Impede o system('cls') p/ evitar bugs em terminais integrados do vscode
#define StopBeforeEnd true // system('pause') ao final do código
using namespace std;

#pragma region Declaracoes_Menu
Lista **listaPolinomios = new Lista*[50];
int tamListaPolinomios = 0;
int tamMaxLista = 50;
#pragma endregion

#pragma region Funcoes_Menu
void limparTela(){
    /* 
        cls é definido pelo UseCLS pois no vscode o terminal integrado
        possui bugs relacionados ao tentar limpa-lo, caso vá usar o EXE é
        recomendado ativar o UseCLS para melhor legibilidade ao fazer a build
    */
    if (UseCLS) system("cls");
    else cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

int lerInt(string msg = "Opcao escolhida: "){
    int temp;
    bool firstTrigger = true;
    do
    {
        if (!firstTrigger) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Valor invalido, tente novamente!" << endl;
        } else firstTrigger = false;
        cout << msg;
        cin >> temp;
    } while (!cin.good());
    return temp;
}

bool RetornarMenu(string msg = "Esta funcao nao esta implementada, retornando ao menu principal em 2 segundos"){
    limparTela();
    cout << msg << endl;
    Sleep(2000);
    return false;
}

Lista* escolherPolinomio(){
    cout << "ESCOLHA UM POLINOMIO:" << endl;
    for (int i = 0; i < tamListaPolinomios; i++){
        cout << "Polinomio " << i+1 << ": ";
        lerPolinomio(listaPolinomios[i]);
    }
    int escolha = -1;
    do
    {
        escolha = lerInt() - 1;
    } while (escolha < 0 || escolha > tamListaPolinomios-1);

    return listaPolinomios[escolha];
}

bool Menu(int Id = 0){
    // Menu retorna um booleano p/ evitar stackoverflow devido recursão infinita sem retorno
    // Por ir e voltar uma opção
    // Humanamente é díficil chegar a esse ponto, mas nunca se sabe
    limparTela();
    int escolha = -1;
    switch (Id)
    {
    
    // FUNÇÃO INEXISTENTE
    default:
        return RetornarMenu();
    break;
    
    // MENU PRINCIPAL
    case 0:
        cout << "Manipulador de polinomios\nEscrito por Herick Vitor Vieira Bittencourt" << endl;
        cout << "Escolha uma opcao:" << endl;
        cout << "1) Operacoes com a lista (TAD)" << endl;
        cout << "2) Operacoes de polinomios" << endl;
        cout << "3) Executar codigo exemplo (parte 1)" << endl;
        cout << "4) Sair" << endl;
        do
        {
            escolha = lerInt();
        } while (escolha < 1 || escolha > 4);
        
        return Menu(escolha);
        break;
    case 1:
        cout << "OPERACOES COM A LISTA:" << endl;
        cout << "1) Nova lista (novo polinomio)" << endl;
        cout << "2) Inserir monomio" << endl;
        cout << "3) Remover por expoente" << endl;
        cout << "4) Encontrar expoente em polinomio" << endl;
        cout << "5) Imprimir lista" << endl;
        cout << "6) Voltar ao menu principal" << endl;

        do
        {
            escolha = lerInt();
        } while (escolha < 1 || escolha > 6);

        return Menu(escolha * 10); //10-60
        break;

    case 2:
        cout << "OPERACOES DE POLINOMIOS:" << endl;
        cout << "1) - Somar polinomios" << endl;
        cout << "2) - Subtrair polinomios" << endl;
        cout << "3) - Multiplicar polinomio por escalar" << endl;
        cout << "4) - Multiplicar polinomios" << endl;
        cout << "5) - Determinar o valor numerico do polinomio" << endl;
        cout << "6) - Voltar ao menu principal" << endl;

        do
        {
            escolha = lerInt();
        } while (escolha < 1 || escolha > 6);

        return Menu(escolha * 100); //100-600
        break;
    case 3:
    {
        funcaoExemplo();
        return true;
        break;
    }

    case 4:
        return true;
        break;


    // OPERAÇÕES COM A LISTA (TAD)
    case 10: // CRIAR POLINOMIO
        if (tamListaPolinomios >= tamMaxLista) return RetornarMenu("Limite de possiveis polinomios para armazenar excedido");
        listaPolinomios[tamListaPolinomios] = new Lista;
        inicializarLista(listaPolinomios[tamListaPolinomios++]);
        return RetornarMenu("Polinomio criado com sucesso");
        break;

    case 20: // ADICIONAR MONOMIO
        if (tamListaPolinomios > 0){
            Lista* polinomioEscolhido = escolherPolinomio();
            bool firstTry = true;

            cout << "Criando monomio: " << endl;
            int K = lerInt("Escolha um valor para a constante: ");

            int letra = -1;
            do {
                cout << (!firstTry ? "Valor invalido, tente novamente!" : "");
                firstTry = false;
                cout << "Tem X?" << endl;
                cout << "1 - Sim\n0 - Nao" << endl;
                cout << "Opcao escolhida: ";
                cin >> letra;
            } while (letra < 0 || letra > 1);

            int exp = lerInt("Escolha um valor para o expoente: ");

            inserirMonomio(polinomioEscolhido, K, letra, exp);
            return RetornarMenu("Monomio adicionado com sucesso");
        } else {
            return RetornarMenu("Nao ha polinomios na memoria, crie um primeiro!");
        }
        break;

    case 30: // Remover por expoente
    {
        if (tamListaPolinomios > 0){
            cout << "Removendo monomio de polinomio a partir de expoente: " << endl;
            Lista* polinomioEscolhido = escolherPolinomio();
            int expEscolhido = lerInt("Escolha um expoente para encontrar: ");
            bool result = deletarExpoente(polinomioEscolhido, expEscolhido);
            return RetornarMenu((result) ? "O expoente fornecido foi encontrado e o valor foi deletado\n" : "Expoente nao encontrado no polinomio\n");
        } else {
            return RetornarMenu("Nao ha polinomios na memoria, crie um primeiro!");
        }
        break;
    }

    case 40: // Encontrar expoente em polinomio
        if (tamListaPolinomios > 0){
            cout << "Procurando em polinomio a partir de expoente: " << endl;
            Lista* polinomioEscolhido = escolherPolinomio();
            int expEscolhido = lerInt("Escolha um expoente para encontrar");
            No* result = acharExpoente(polinomioEscolhido, expEscolhido);
            //return RetornarMenu((result != NULL) ? );
        } else {
            return RetornarMenu("Nao ha polinomios na memoria, crie um primeiro!");
        }
        break;

    case 50: // Imprimir lista
        break;

    case 60: // Voltar ao menu principal (REMOVER)
        break;


    // OPERACOES COM POLINOMIOS
    case 600: // Voltar ao menu principal (REMOVER)
        break;
    
    }

    return false;
}
#pragma endregion

int main(){
    bool exitting = false;
    do exitting = Menu(); while (exitting == false);
    if (StopBeforeEnd) system("pause");
    return 0;
}