// Biblioteca contendo implementações para interface de console
// Aluno: Hérick Vitor Vieira Bittencourt
// Estrutura de dados 2023

#include <iostream>
#include <string>
#include "parte1.h"

using namespace std;

#ifndef INTERFACE_H
#define INTERFACE_H

int lerInt(int min = 0, int max = 0, string msg = "Forneca um valor inteiro: "){
    int valor;
    bool condicaoFalhou;
    do {
        cout << msg;
        cin >> valor;

        // Int nos limites
        condicaoFalhou = (valor < min || valor > max);

        // Sem requisito de espaço
        if (min == max) condicaoFalhou = false;

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
    system("pause");
}

bool retornarComPausa(bool valor, string msg = "Esta funcao nao esta implementada"){
    cout << msg << endl;
    esperarInput();
    return valor;
}

Lista* escolherPolinomio(Lista **listaPolinomios, int tamListaPolinomios){
    cout << "Escolha um polinomio:" << endl;
    for (int i = 0; i < tamListaPolinomios; i++){
        cout << "Polinomio " << i+1 << " = ";
        lerPolinomio(listaPolinomios[i]);
    }

    int escolha;
    escolha = lerInt(1, tamListaPolinomios-1, "Polinomio escolhido: ") - 1;
    return listaPolinomios[escolha];
}

void limparTela(){
    system("cls");
}

#endif