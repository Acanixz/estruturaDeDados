// Manipulador de polinômios
// Aluno: Hérick Vitor Vieira Bittencourt
// Estrutura de dados 2023

#include <iostream>
#include <math.h>
#include <windows.h> // usado para pausas
#include <string>

#include "parte1.h"
#include "interface.h"
#define pausarNoFinal true // system('pause') ao final do código
using namespace std;

// ---------- Declaracoes_Menu
Lista **listaPolinomios = new Lista*[50];
int tamListaPolinomios = 0;
int tamMaxLista = 50;

// ---------- Funcoes_Menu
bool Menu(int id = 0){
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

        case 1: // Submenu 1 - Operações com a lista (TAD)
            cout << "Operacoes com a lista (TAD):\n" << endl;
            cout << "1) Nova lista (novo polinomio)" << endl;
            cout << "2) Inserir monomio" << endl;
            cout << "3) Remover por expoente" << endl;
            cout << "4) Encontrar expoente em polinomio" << endl;
            cout << "5) Imprimir lista" << endl;
            cout << "6) Voltar ao menu principal" << endl;
            return Menu(lerInt(1,6, "Opcao escolhida: ") * 10 ); // Escolhe IDs de 10 - 60
            break;

        case 2: // Submenu 2 - Operaçoes de polinomios
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


        // Submenu 1 - Operações com a lista (TAD)
        case 10:{ // Nova lista (novo polinomio)
            if (tamListaPolinomios >= tamMaxLista) return retornarComPausa(false, "Limite de possiveis polinomios para armazenar excedido");
                listaPolinomios[tamListaPolinomios] = new Lista;
                inicializarLista(listaPolinomios[tamListaPolinomios++]);
                return retornarComPausa(false,"Polinomio criado com sucesso");
            break;
        }

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

        case 40:{ // Encontrar expoente em polinomio
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
        }

        case 50:{ // Imprimir lista
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
        }

        case 60: // Retornar ao menu principal
            return false;
            break;


        // Submenu 2 - Operações de polinomios
        case 100:{ // Somar polinomios
            if (tamListaPolinomios >= 2){
                cout << "Soma de polinomios: " << endl;
                Lista* polinomioEscolhido1 = escolherPolinomio(listaPolinomios, tamListaPolinomios);
                cout << endl;
                Lista* polinomioEscolhido2 = escolherPolinomio(listaPolinomios, tamListaPolinomios);
                if (polinomioEscolhido1 == NULL || polinomioEscolhido2 == NULL) return false;

                adicionarPolinomio(somarPolinomios(polinomioEscolhido1, polinomioEscolhido2), listaPolinomios, tamListaPolinomios, tamMaxLista);
                return retornarComPausa(false, "Operacao concluida");
            } else return retornarComPausa(false, "Nao ha polinomios o suficiente para esta operacao | Minimo: 2 / Armazenado: " + to_string(tamListaPolinomios));
            break;
        }

        case 200:{ // Subtrair polinomios
            if (tamListaPolinomios >= 2){
                cout << "Subtracao de polinomios: " << endl;
                Lista* polinomioEscolhido1 = escolherPolinomio(listaPolinomios, tamListaPolinomios);
                cout << endl;
                Lista* polinomioEscolhido2 = escolherPolinomio(listaPolinomios, tamListaPolinomios);
                if (polinomioEscolhido1 == NULL || polinomioEscolhido2 == NULL) return false;

                adicionarPolinomio(subtrairPolinomios(polinomioEscolhido1, polinomioEscolhido2), listaPolinomios, tamListaPolinomios, tamMaxLista);
                return retornarComPausa(false, "Operacao concluida");
            } else return retornarComPausa(false, "Nao ha polinomios o suficiente para esta operacao | Minimo: 2 / Armazenado: " + to_string(tamListaPolinomios));
            break;
        }

        case 300:{ // Multiplicar polinomio por escalar
            if (tamListaPolinomios > 0){
                cout << "Multiplicacao de polinomio por escalar: " << endl;
                Lista* polinomioEscolhido = escolherPolinomio(listaPolinomios, tamListaPolinomios);
                if (polinomioEscolhido == NULL) return false;

                int escalar = lerInt(-1, -1);

                adicionarPolinomio(multiplicacaoEscalar(polinomioEscolhido, escalar), listaPolinomios, tamListaPolinomios, tamMaxLista);
                return retornarComPausa(false, "Operacao concluida");
            } else return retornarComPausa(false, "Nao ha polinomios na memoria, crie um primeiro!");
            break;
        }

        case 400:{ // Multiplicar polinomios
            if (tamListaPolinomios >= 2){
                cout << "Multiplicacao de polinomios: " << endl;
                Lista* polinomioEscolhido1 = escolherPolinomio(listaPolinomios, tamListaPolinomios);
                cout << endl;
                Lista* polinomioEscolhido2 = escolherPolinomio(listaPolinomios, tamListaPolinomios);
                if (polinomioEscolhido1 == NULL || polinomioEscolhido2 == NULL) return false;

                adicionarPolinomio(multiplicarPolinomios(polinomioEscolhido1, polinomioEscolhido2), listaPolinomios, tamListaPolinomios, tamMaxLista);
                return retornarComPausa(false, "Operacao concluida");
            } else return retornarComPausa(false, "Nao ha polinomios o suficiente para esta operacao | Minimo: 2 / Armazenado: " + to_string(tamListaPolinomios));
            break;
        }
        
        case 500:{ // Determinar o valor numerico
            if (tamListaPolinomios > 0){
                cout << "Determinar valor numerico do polinomio: " << endl;
                Lista* polinomioEscolhido = escolherPolinomio(listaPolinomios, tamListaPolinomios);
                if (polinomioEscolhido == NULL) return false;

                int valorX = lerInt(-1, -1, "Forneca um valor para X: ");

                int result = determinarValor(polinomioEscolhido, valorX);

                cout << "f(" << valorX << ") = " << result << endl;
                return retornarComPausa(false, "Operacao concluida");
            } else return retornarComPausa(false, "Nao ha polinomios na memoria, crie um primeiro!");
            break;
        }

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