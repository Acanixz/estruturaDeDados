// Manipulador de polinômios
// Aluno: Hérick Vitor Vieira Bittencourt
// Estrutura de dados 2023
// TODO: remover pragma regions

#include <iostream>
#include <math.h>
#include <windows.h> // usado para pausas
#include <string>
#include "parte1.h"
#include "interface.h"
#define pausarNoFinal true // system('pause') ao final do código
using namespace std;

#pragma region Declaracoes_Menu
Lista **listaPolinomios = new Lista*[50];
int tamListaPolinomios = 0;
int tamMaxLista = 50;
#pragma endregion

#pragma region Funcoes_Menu
/*bool Menu(int Id = 0){
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
#pragma endregion*/

bool Menu(int id = 0){
    //int escolha;
    limparTela();
    switch (id){
        default: // Funções não implementadas
            return retornarComPausa(false);
            break;

        case 0: // Menu principal
            cout << "Manipulador de polinomios\nEscrito por Herick Vitor Vieira Bittencourt\n" << endl;
            cout << "1) Operacoes com a lista (TAD)" << endl;
            cout << "2) Operacoes de polinomios" << endl;
            cout << "3) Executar codigo exemplo (parte 1)" << endl;
            cout << "4) Sair" << endl;
            return Menu(lerInt(1, 4, "Opcao escolhida: ")); // Escolhe IDs de 1 - 4
            break;

        case 1: // Operações com a lista (TAD)
            cout << "Operacoes com a lista (TAD):\n" << endl;
            cout << "1) Nova lista (novo polinomio)" << endl;
            cout << "2) Inserir monomio" << endl;
            cout << "3) Remover por expoente" << endl;
            cout << "4) Encontrar expoente em polinomio" << endl;
            cout << "5) Imprimir lista" << endl;
            cout << "6) Voltar ao menu principal" << endl;
            return Menu(lerInt(1,6, "Opcao escolhida: ") * 10 ); // Escolhe IDs de 10 - 60
            break;

        case 2:
            cout << "Operacoes de polinomios:\n" << endl;
            cout << "1) - Somar polinomios" << endl;
            cout << "2) - Subtrair polinomios" << endl;
            cout << "3) - Multiplicar polinomio por escalar" << endl;
            cout << "4) - Multiplicar polinomios" << endl;
            cout << "5) - Determinar o valor numerico do polinomio" << endl;
            cout << "6) - Voltar ao menu principal" << endl;
            return Menu(lerInt(1,6, "Opcao escolhida: ") * 100); // Escolhe IDs 100 - 600
            break;

        case 3:
            funcaoExemplo();
            return retornarComPausa(true, "Fim da demonstracao");
            break;

        case 4:
            return true;
            break;


        case 10: // Nova lista (novo polinomio)
            if (tamListaPolinomios >= tamMaxLista) return retornarComPausa(false, "Limite de possiveis polinomios para armazenar excedido");
                listaPolinomios[tamListaPolinomios] = new Lista;
                inicializarLista(listaPolinomios[tamListaPolinomios++]);
                return retornarComPausa(false,"Polinomio criado com sucesso");
                break;

        case 20:{ // Inserir monomio
            if (tamListaPolinomios > 0){
                Lista* polinomioEscolhido = escolherPolinomio(listaPolinomios, tamListaPolinomios);
                if (polinomioEscolhido == NULL) return false;

                cout << "\nCriando monomio: " << endl;
                int K = lerInt(-1, -1,"Forneca um valor para a constante: ");

                int exp = lerInt(-1, -1, "Escolha um valor para o expoente: ");

                inserirMonomio(polinomioEscolhido, K, exp);
                return  retornarComPausa(false, "Monomio adicionado com sucesso");
            } else {
                return retornarComPausa(false, "Nao ha polinomios na memoria, crie um primeiro!");
            }
            break;
        }

        case 30:{ // Remover por expoente
            if (tamListaPolinomios > 0){
                cout << "Removendo monomio de polinomio a partir de expoente: " << endl;
                Lista* polinomioEscolhido = escolherPolinomio(listaPolinomios, tamListaPolinomios);
                if (polinomioEscolhido == NULL) return false;

                int expEscolhido = lerInt(-1, -1, "Escolha um expoente para encontrar: ");

                bool result = deletarExpoente(polinomioEscolhido, expEscolhido);
                return retornarComPausa(false, (result) ? "O expoente fornecido foi encontrado e o valor foi deletado\n" : "Expoente nao encontrado no polinomio\n");
            } else {
                return retornarComPausa(false, "Nao ha polinomios na memoria, crie um primeiro!");
            }
            break;
        }

        case 40: // Encontrar expoente em polinomio
            if (tamListaPolinomios > 0){
                cout << "Procurando em polinomio a partir de expoente: " << endl;
                Lista* polinomioEscolhido = escolherPolinomio(listaPolinomios, tamListaPolinomios);
                if (polinomioEscolhido == NULL) return false;

                int expEscolhido = lerInt(-1, -1, "Escolha um expoente para encontrar: ");
                No* result = acharExpoente(polinomioEscolhido, expEscolhido);

                if (result != NULL) return retornarComPausa(false, "Encontrado o expoente " + to_string(expEscolhido) + " no polinomio");
                return retornarComPausa(false , "O expoente " + to_string(expEscolhido) + " nao foi encontrado no polinomio");
            } else {
                return retornarComPausa(false, "Nao ha polinomios na memoria, crie um primeiro!");
            }
            break;

        case 50: // Imprimir lista
            if (tamListaPolinomios > 0){
                cout << "Imprimir lista: " << endl;
                Lista* polinomioEscolhido = escolherPolinomio(listaPolinomios, tamListaPolinomios);
                if (polinomioEscolhido == NULL) return false;

                limparTela();
                lerPolinomio(polinomioEscolhido);
                return retornarComPausa(false, "");
            } else {
                return retornarComPausa(false, "Nao ha polinomios na memoria, crie um primeiro!");
            }
            break;

        case 60: // Retornar ao menu principal
            return false;
            break;


        

        case 600: // Retornar ao menu principal
            return false;
            break;
    }
}

int main(){
    bool saindo;
    do saindo = Menu(); while (saindo == false);
    if (pausarNoFinal) system("pause");
    return 0;
}