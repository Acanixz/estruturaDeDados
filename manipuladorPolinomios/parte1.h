// Biblioteca contendo as implementações da lista duplamente encadeada e polinomios
// Aluno: Hérick Vitor Vieira Bittencourt
// Estrutura de dados 2023

#include <iostream>
#include <string>
#include <math.h>
using namespace std;


#ifndef PARTE1_H
#define PARTE1_H

// ---------- Structs
struct No{ // Monômio
    int K; // Constante K
    int exp; // Expoente
    No* frontElo; // Próximo monômio ou NULL
    No* backElo; // Monômio anterior ou NULL
};

struct Lista{ // Polinomio
    No *start, *end;
};

// ---------- Declaracoes_Polinomios
// Inicializa a lista, setando os ponteros pra NULL
void inicializarLista(Lista *lista){
    lista->start = NULL;
    lista->end = NULL;
}

// Mostra o polinômio na tela
// Utilizando uma condição ternária absurdamente longa
void mostrarPolinomio(Lista *lista){
    No *aux = lista->start;
    bool primeiroValor = true;
    while (aux != NULL){
        // simbolo + é renderizado caso não seja o primeiro valor e a constante seja positivo
        cout << ((!primeiroValor && aux->K > 0) ? "+" : "")
        
        // simbolo - é renderizado caso -X, já que a constante não renderiza no caso de K < -1 e exp != 0, levando a não aparecer o - 
        << ((aux->exp != 0 && aux->K == -1) ? "-" : "")

        // constante é renderizada caso o expoente seja zero ou tenha expoente, mas que a constante seja menor que -1 ou maior que 1
        << (((aux->exp == 0) || (aux->exp != 0 && (aux->K < -1 || aux->K > 1))) ? to_string(aux->K) : "")
        
        // se o expoente for diferente de zero, X é renderizado
        << ((aux->exp != 0 && aux->K != 0) ? "X" : "")
        
        // se (o expoente for menor que 0 ou maior que 1) e o constante é diferente de 0, o simbolo ^ é renderizado junto ao expoente
        << (((aux->exp < 0 || aux->exp > 1) && aux->K != 0) ? "^" + std::to_string(aux->exp) : "")
        
        // Espaço para o proximo monomio e finalização do cout
        << ((aux->K != 0) ? " " : "");

        if (primeiroValor) primeiroValor = false;
        aux = aux->frontElo;
    }
    cout << endl;
}

// Procura o primeiro valor com o mesmo expoente, retornando o alvo ou NULL
No* acharExpoente(Lista *lista, int exp){
    if (lista->start == NULL) return NULL;
    No *aux = lista->start;
    while (aux != NULL && exp != aux->exp)
    {
        aux = aux->frontElo;
    }
    return aux;
}

// Insere o monômio seguindo ordem de expoênte
bool inserirMonomio(Lista *lista, int K, int exp = 0){
    if( lista == NULL || K == 0) return false;
    No *monomio = new No;
    monomio->K = K;
    monomio->exp = exp;
    monomio->backElo = NULL;
    monomio->frontElo = NULL;

    // Se já houver um valor com mesmo expoente, soma automatica
    No *soma = acharExpoente(lista, exp);
    if (soma != NULL){
        soma->K += K;
        return true;
    }

    // Inserir em lista vazia
    if( lista->start == NULL ){
        lista->start = monomio;
        lista->end = monomio;
        return true;
    }

    // Inserir no inicio da lista
    if (exp > lista->start->exp){
        monomio->frontElo = lista->start;
        lista->start->backElo = monomio;
        lista->start = monomio;
        return true;
    }

    // Inserir no final da lista
    if( exp < lista->end->exp){
        lista->end->frontElo = monomio;
        monomio->backElo = lista->end;
        lista->end = monomio;
        return true;
    }

    // Inserir no meio da lista
    No *aux = lista->start;
    while( aux->exp > exp && aux->frontElo->exp > exp )
        aux = aux->frontElo;

    aux->frontElo->backElo = monomio;
    monomio->frontElo = aux->frontElo;
    monomio->backElo = aux;
    aux->frontElo = monomio;
    
    return true;
}

// Insere o monômio no final
bool inserirMonomioFinal(Lista *lista, int K, int exp = 0){
    if( lista == NULL || K == 0) return false;
    No *novo = new No;
    novo->exp = exp;
    novo->K = K;
    novo->backElo = NULL;
    novo->frontElo = NULL;

    // Inserir em lista vazia
    if( lista->start == NULL ){
        lista->start = novo;
        lista->end = novo;
    } else {
        lista->end->frontElo = novo;
        novo->backElo = lista->end;
        lista->end = novo;
    }
    return true;
}

// Deleta o primeiro valor com o mesmo expoente encontrado
bool deletarExpoente(Lista *lista, int exp = 0){
    No* alvo = acharExpoente(lista, exp);
    if (alvo == NULL) return false;
    if (alvo->frontElo != NULL && alvo->backElo != NULL){ // Alvo no meio
        alvo->backElo->frontElo = alvo->frontElo;
        alvo->frontElo->backElo = alvo->backElo;
    } else {
        if (alvo == lista->start) { // Alvo no começo
            lista->start = alvo->frontElo;
            if (lista->start != NULL) lista->start->backElo = NULL;
        }
        if (alvo == lista->end) { // Alvo no fim
            lista->end = alvo->backElo;
            if (lista->end != NULL) lista->end->frontElo = NULL;
        }
    }
    delete alvo;
    return true;
}

// Soma os polinomios, criando um novo polinomio
Lista *somarPolinomios(Lista *lista1,Lista *lista2){
    Lista *soma = new Lista;
    inicializarLista(soma);
    No *aux = lista1->start;
    while (aux != NULL){ // Inserção da lista 1
        inserirMonomio(soma, aux->K, aux->exp);
        aux = aux->frontElo;
    }

    aux = lista2->start;
    while (aux != NULL){ // Inserção da lista 2
        inserirMonomio(soma, aux->K, aux->exp);
        aux = aux->frontElo;
    }

    return soma;
}

// Subtrai os polinomios, criando um novo polinomio
Lista *subtrairPolinomios(Lista *lista1,Lista *lista2){
    Lista *soma = new Lista;
    inicializarLista(soma);
    No *aux = lista1->start;
    while (aux != NULL){ // Inserção da lista 1
        inserirMonomio(soma, aux->K, aux->exp);
        aux = aux->frontElo;
    }

    aux = lista2->start;
    while (aux != NULL){ // Inserção da lista 2 com constantes invertidas
        inserirMonomio(soma, -aux->K, aux->exp);
        aux = aux->frontElo;
    }

    return soma;
}

// Multiplica o polinomio fornecido pelo valor escaler
Lista *multiplicacaoEscalar(Lista *lista, int valor){
    Lista *resultado = new Lista;
    inicializarLista(resultado);
    No *aux = lista->start;
    while (aux != NULL){ // Valores da lista são inseridos enquanto constantes são multiplicados pelo escalar
        inserirMonomioFinal(resultado, aux->K * valor, aux->exp);
        aux = aux->frontElo;
    }
    return resultado;
}

// Multiplica os polinomios, criando um novo polinomio
Lista *multiplicarPolinomios(Lista *lista1,Lista *lista2){
    Lista *multiplicada = new Lista;
    inicializarLista(multiplicada);
    No *aux = lista1->start;
    while (aux != NULL){ // Propriedade distributiva
        No *aux2 = lista2->start;
        while (aux2 != NULL){ // Constantes são multiplicados e expoentes são somados
            inserirMonomio(multiplicada, aux->K * aux2->K, aux->exp + aux2->exp);
            aux2 = aux2->frontElo;
        }
        aux = aux->frontElo;
    }

    return multiplicada;
}

// Resolve o polinomio fornecido, dado o valor de X
int determinarValor(Lista *lista, int valorX){
    int resultado = 0;

    No *aux = lista->start;
    while (aux != NULL){
        if (aux->exp != 0){
            resultado += aux->K * (pow(valorX, aux->exp)); // K + X^exp
            } else {
                resultado += aux->K; // X^0 = 1 * K = K
            }

        aux = aux->frontElo;
    }

    return resultado;
}

// Função utilizada para demonstrar o uso de todas as funções desta biblioteca
void funcaoExemplo(){
    cout << "Codigo de exemplo para apresentacao da parte 1:\n" << endl;

    cout << "[DEMO] Inicializacao da lista, insercao e leitura do polinomio" << endl;
    Lista *listaTemp1 = new Lista, *listaTemp2 = new Lista, *listaTemp3 = new Lista;
    Lista *resultado1 = new Lista, *resultado2 = new Lista, *resultado3 = new Lista, *resultado4 = new Lista, *resultado5 = new Lista;
    inicializarLista(listaTemp1);
    inicializarLista(listaTemp2);
    inicializarLista(listaTemp3);
    inicializarLista(resultado1);

    inserirMonomio(listaTemp1, 4, 2); // 4X^2 (Inserção conforme expoente)
    mostrarPolinomio(listaTemp1);
    inserirMonomioFinal(listaTemp1, 2, 4); // 2X^4 (Inserção no final da lista)
    mostrarPolinomio(listaTemp1);
    inserirMonomio(listaTemp1, 3, 3); // 3X^3 (Inserção conforme expoente, meio da lista)
    mostrarPolinomio(listaTemp1);
    cout << "\n\n";
    
    cout << "[DEMO] Pesquisa e remocao de monomio" << endl;
    mostrarPolinomio(listaTemp1);
    cout << (acharExpoente(listaTemp1, 10) ? "Expoente 10 foi encontrado no polinomio" : "Expoente 10 nao encontrado") << endl;
    cout << (acharExpoente(listaTemp1, 4) ? "Expoente 4 foi encontrado no polinomio" : "Expoente 4 nao encontrado") << endl;
    
    mostrarPolinomio(listaTemp1);
    deletarExpoente(listaTemp1, 4);
    mostrarPolinomio(listaTemp1);
    cout << "\n\n";

    cout << "[DEMO] Soma de dois polinomios" << endl;
    inserirMonomio(listaTemp2, -7, 3); // -7X^3
    inserirMonomio(listaTemp2, -4, 2); // -4X^2
    inserirMonomio(listaTemp2, 10, 1); // 10X
    inserirMonomio(listaTemp2, 20); // 20
    mostrarPolinomio(listaTemp2);

    inserirMonomio(listaTemp3, 2, 2); // 2X^2
    inserirMonomio(listaTemp3, -5, 1); // -5X
    inserirMonomio(listaTemp3, 15, 5); // 15X^5
    inserirMonomio(listaTemp3, -10); // -10
    mostrarPolinomio(listaTemp3);

    cout << "Resultado: ";
    resultado1 = somarPolinomios(listaTemp2, listaTemp3);
    mostrarPolinomio(resultado1);
    cout << "\n\n";

    cout << "[DEMO] Subtracao de dois polinomios" << endl;
    mostrarPolinomio(listaTemp2);
    mostrarPolinomio(listaTemp3);

    cout << "Resultado: ";
    resultado2 = subtrairPolinomios(listaTemp2, listaTemp3);
    mostrarPolinomio(resultado2);
    cout << "\n\n";

    cout << "[DEMO] Multiplicacao de polinomio por um escalar" << endl;
    mostrarPolinomio(listaTemp2);

    cout << "Multiplicacao escalar por 3: ";
    resultado3 = multiplicacaoEscalar(listaTemp2, 3);
    mostrarPolinomio(resultado3);
    cout << "Multiplicacao escalar por -3: ";
    resultado4 = multiplicacaoEscalar(listaTemp2, -3);
    mostrarPolinomio(resultado4);
    cout << "\n\n";

    cout << "[DEMO] Multiplicacao de dois polinomios" << endl;
    mostrarPolinomio(listaTemp2);
    mostrarPolinomio(listaTemp3);

    cout << "Resultado: ";
    resultado5 = multiplicarPolinomios(listaTemp2, listaTemp3);
    mostrarPolinomio(resultado5);
    cout << "\n\n";

    cout << "[DEMO] Calculo do valor numerico do polinomio" << endl;
    mostrarPolinomio(listaTemp2);

    cout << "Resultado quando f(x) = 2: ";
    int resultadoFinal = determinarValor(listaTemp2, 2);
    // Calculadora cientifica resultou em -32
    cout << resultadoFinal;
    cout << "\n\n";
}

#endif