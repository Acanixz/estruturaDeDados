// Biblioteca contendo implementações para interface de console
// Aluno: Hérick Vitor Vieira Bittencourt
// Estrutura de dados 2023

#include <iostream>
#include <string>
#include "parte1.h"
#define UseSystem true // Impede o system("") p/ evitar bugs em terminais integrados do vscode

using namespace std;

#ifndef INTERFACE_H
#define INTERFACE_H

int lerInt(int min = -1, int max = -1, string msg = "Forneca um valor inteiro: "){
    int valor;
    bool condicaoFalhou;
    do {
        cout << msg;
        cin >> valor;

        // Int nos limites
        condicaoFalhou = (valor < min || valor > max);

        // Sem requisito de espaço
        if (min == -1 && max == -1) condicaoFalhou = false;

        // Falhou?
        if (!cin.good()) { 
            condicaoFalhou = true;
            cin.clear();
            cin.ignore(10000, '\n');
        } 

        if (condicaoFalhou) cout << "Valor invalido!\n" << endl;
    } while (condicaoFalhou);

    return valor;
}

void esperarInput(){
    cout << endl;
    if (!UseSystem) return;
    system("pause");
}

bool retornarComPausa(bool valor, string msg = "Esta funcao nao esta implementada"){
    cout << msg << endl;
    esperarInput();
    return valor;
}

// Oferece uma lista para escolha de polinomios, sendo necessário a implementação
// do comportamento em caso NULL para retornar ao menu toda vez que for chamado
Lista* escolherPolinomio(Lista **listaPolinomios, int tamListaPolinomios){
    cout << "Escolha um polinomio:\n0 = Voltar ao menu principal" << endl;
    for (int i = 0; i < tamListaPolinomios; i++){
        cout << "Polinomio " << i+1 << " = ";
        mostrarPolinomio(listaPolinomios[i]);
    }

    int escolha;
    escolha = lerInt(0, tamListaPolinomios, "Polinomio escolhido: ") - 1;
    if (escolha != -1) return listaPolinomios[escolha];
    else return NULL;
}

// Adiciona um polinomio na lista de polinomios, utilizado nas operações que resultam em um polinomio novo
bool adicionarPolinomio(Lista *polinomio, Lista **listaPolinomios, int &tamListaPolinomios, int limite){
    if (tamListaPolinomios < limite-1){
        listaPolinomios[tamListaPolinomios++] = polinomio;
        return false;
    } else {
        return retornarComPausa(false, "Nao foi possivel adicionar o polinomio a lista pois a mesma esta cheia!");
    }
}

void limparTela(){
    if (UseSystem) system("cls");
    else cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
}

#endif