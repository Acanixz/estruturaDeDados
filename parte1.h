// Biblioteca contendo as implementações da lista duplamente encadeada e polinomios
// Aluno: Hérick Vitor Vieira Bittencourt
// Estrutura de dados 2023

#include <iostream>
#include <string>
#include <math.h>
using namespace std;


#ifndef PARTE1_H
#define PARTE1_H

#pragma region Structs
struct No{ // Monômio
    int K; // Constante K
    bool letra; // Tem X?
    int exp; // Expoente
    No* frontElo; // Próximo monômio ou NULL
    No* backElo; // Monômio anterior ou NULL
};

struct Lista{ // Polinomio
    No *start, *end;
};
#pragma endregion

#pragma region Declaracoes_Polinomios
// Inicializa a lista, setando os ponteros pra NULL
void inicializarLista(Lista *lista){
    lista->start = NULL;
    lista->end = NULL;
}

// Mostra o polinômio na tela
// Utilizando uma condição ternária absurdamente longa
void lerPolinomio(Lista *lista){
    No *aux = lista->start;
    bool primeiroValor = true;
    while (aux != NULL){
        // Fiz em duas versões diferentes para comparar performance, elas fazem a mesma coisa na prática
        // Versão 1 - Um unico cout com uma condição ternaria enorme
        // Versão 2 - sequencia de cout com if statements
        // Conclusão: V1 é mais rápido que V2 pois tem menos operações no total, porém é menos legivel
        // deixei a versão legivel comentada

        cout << ((!primeiroValor && aux->K > 0) ? "+" : "") // simbolo + é renderizado caso não seja o primeiro valor e a constante seja positivo
        
        << (((!aux->letra && aux->K != 0) || (aux->letra && (aux->K < -1 || aux->K > 1))) ? to_string(aux->K) : "") // constante é renderizada caso (não haja base e o expoente seja diferente de zero) OU (haja base e a constante seja menor que -1 ou maior que 1)
        
        << ((aux->letra && aux->K != 0) ? "X" : "") // se tiver uma base e o constante for diferente de zero, X é renderizado
        
        << (((aux->exp < 0 || aux->exp > 1) && aux->K != 0) ? "^" + std::to_string(aux->exp) : "") // se (o expoente for maior que 1 ou menor que zero) e o constante é diferente de zero, o simbolo ^ é renderizado junto ao expoente
        
        << ((aux->K != 0) ? " " : ""); // se a constante for diferente de zero, cria um espaço para o próximo numero


        // VERSÃO LEGIVEL
        /*if (!primeiroValor && aux->K > 0) cout << "+"; // simbolo + é renderizado caso não seja o primeiro valor e a constante seja positivo

        if ((!aux->letra && aux->K != 0) || (aux->letra && (aux->K < -1 || aux->K > 1))) cout << to_string(aux->K); // constante é renderizada caso (não haja base e o expoente seja diferente de zero) OU (haja base e a constante seja menor que -1 ou maior que 1)

        if (aux->letra && aux->K != 0) cout << "X"; // se tiver uma base e o constante for diferente de zero, X é renderizado

        if ((aux->exp < 0 || aux->exp > 1) && aux->K != 0) cout << "^" + std::to_string(aux->exp); // se (o expoente for maior que 1 ou menor que zero) e o constante é diferente de zero, o simbolo ^ é renderizado junto ao expoente

        if (aux->K != 0) cout << " "; // se a constante for diferente de zero, cria um espaço para o próximo numero*/


        if (primeiroValor) primeiroValor = false;
        aux = aux->frontElo;
    }
    cout << endl;
}

// Procura o primeiro valor com o mesmo expoente (e opcionalmente mesma letra), retornando o alvo ou NULL
No* acharExpoente(Lista *lista, int exp, int mesmaLetra = -1){
    // O parametro padrão mesmaLetra pode ter 3 estados e afeta diretamente a pesquisa
    // -1 = Não configurado, a pesquisa normal para se achar o mesmo expoente, independente do estado da letra
    // 0 = A pesquisa apenas para se achar o mesmo expoente e não houver variavel X
    // 1 = A pesquisa apenas para se achar o mesmo expoente e HOUVER variavel X
    if (lista->start == NULL) return NULL;
    No *aux = lista->start;
    if (mesmaLetra == -1){
        while (aux != NULL && exp != aux->exp)
        {
            aux = aux->frontElo;
        }
    } else {
        while ((aux != NULL) && (exp != aux->exp || aux->letra != static_cast<bool>(mesmaLetra)))
        // Para a condição funcionar foi necessário converter mesmaLetra p/ booleano usando static_cast
        {
            aux = aux->frontElo;
        }
    }
    return aux;
}

// Insere o monômio seguindo ordem de expoênte
bool inserirMonomio(Lista *lista, int K, bool letra = false, int exp = 0){
    if( lista == NULL || K == 0) return false;
    No *monomio = new No;
    monomio->K = K;
    monomio->letra = letra;
    monomio->exp = (letra && exp == 0) ? 1 : (!letra && exp == 1) ? 0 : exp;
    monomio->backElo = NULL;
    monomio->frontElo = NULL;

    // Se já houver um valor com mesmo expoente, soma automatica
    No *soma = acharExpoente(lista, exp, letra);
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
    // O monomio novo possui base e possui um expoente maior ou igual que o atual, ele vem primeiro
    if (exp > lista->start->exp || (exp == lista->start->exp && letra)){
        monomio->frontElo = lista->start;
        lista->start->backElo = monomio;
        lista->start = monomio;
        return true;
    } else if (exp == lista->start->exp){
        // monomio novo tem mesmo exp, mas não possui base, ele vem depois
        if (lista->start->frontElo) {
            lista->start->frontElo->backElo = monomio;
        }
        monomio->frontElo = lista->start->frontElo;
        monomio->backElo = lista->start;
        lista->start->frontElo = monomio;
        return true;
    }

    // Inserir no final da lista
    if( exp <= lista->end->exp ){
        lista->end->frontElo = monomio;
        monomio->backElo = lista->end;
        lista->end = monomio;
        return true;
    }

    // Inserir no meio da lista
    No *aux = lista->start;
    while( aux->exp > exp && aux->frontElo->exp > exp )
        aux = aux->frontElo;

    if (!letra){
        while (aux->exp >= exp && aux->frontElo != NULL){
            aux = aux->frontElo;
        }

        aux->backElo->frontElo = monomio;
        monomio->backElo = aux->backElo;
        monomio->frontElo = aux;
        aux->backElo = monomio;
    } else {
        aux->frontElo->backElo = monomio;
        monomio->frontElo = aux->frontElo;
        monomio->backElo = aux;
        aux->frontElo = monomio;
    }
    
    
    return true;
}

// Insere o monômio no final
bool inserirMonomioFinal(Lista *lista, int K, bool letra = false, int exp = 0){
    if( lista == NULL || K == 0) return false;
    No *novo = new No;
    novo->exp = exp;
    novo->K = K;
    novo->letra = letra;
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
    while (aux != NULL){
        inserirMonomio(soma, aux->K, aux->letra, aux->exp);
        aux = aux->frontElo;
    }

    aux = lista2->start;
    while (aux != NULL){
        inserirMonomio(soma, aux->K, aux->letra, aux->exp);
        aux = aux->frontElo;
    }

    return soma;
}

// Subtrai os polinomios, criando um novo polinomio
Lista *subtrairPolinomios(Lista *lista1,Lista *lista2){
    Lista *soma = new Lista;
    inicializarLista(soma);
    No *aux = lista1->start;
    while (aux != NULL){
        inserirMonomio(soma, aux->K, aux->letra, aux->exp);
        aux = aux->frontElo;
    }

    aux = lista2->start;
    while (aux != NULL){
        inserirMonomio(soma, -aux->K, aux->letra, aux->exp);
        aux = aux->frontElo;
    }

    return soma;
}

// Multiplica o polinomio fornecido pelo valor escaler
Lista *multiplicacaoEscalar(Lista *lista, int valor){
    Lista *resultado = new Lista;
    inicializarLista(resultado);
    No *aux = lista->start;
    while (aux != NULL){
        inserirMonomioFinal(resultado, aux->K * valor, aux->letra, aux->exp);
        aux = aux->frontElo;
    }
    return resultado;
}

// Multiplica os polinomios, criando um novo polinomio
Lista *multiplicarPolinomios(Lista *lista1,Lista *lista2){
    Lista *multiplicada = new Lista;
    inicializarLista(multiplicada);
    No *aux = lista1->start;
    while (aux != NULL){
        No *aux2 = lista2->start;
        while (aux2 != NULL){
            inserirMonomio(multiplicada, aux->K * aux2->K, (aux->letra || aux2->letra), aux->exp + aux2->exp);
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
        if (aux->letra){ // Se tiver base, constante é multiplicada por valorX na potencia de (aux->exp)
            resultado += (aux->K * (pow(valorX, aux->exp)));
        } else { // Se não tiver base, constante na potência de (aux->exp)
            if (aux->exp != 0){
                resultado += (pow(aux->K, aux->exp));
            } else {
                resultado += aux->K;
            }
        }

        aux = aux->frontElo;
    }

    return resultado;
}

#pragma endregion

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

    inserirMonomio(listaTemp1, 4, true, 2); // 4X^2 (Inserção conforme expoente)
    lerPolinomio(listaTemp1);
    inserirMonomioFinal(listaTemp1, 2, true, 4); // 2X^4 (Inserção no final da lista)
    lerPolinomio(listaTemp1);
    inserirMonomio(listaTemp1, 3, true, 3); // 3X^3 (Inserção conforme expoente, meio da lista)
    lerPolinomio(listaTemp1);
    cout << "\n\n";
    
    cout << "[DEMO] Pesquisa e remocao de monomio" << endl;
    lerPolinomio(listaTemp1);
    cout << (acharExpoente(listaTemp1, 10) ? "Expoente 10 foi encontrado no polinomio" : "Expoente 10 nao encontrado") << endl;
    cout << (acharExpoente(listaTemp1, 4) ? "Expoente 4 foi encontrado no polinomio" : "Expoente 4 nao encontrado") << endl;
    
    lerPolinomio(listaTemp1);
    deletarExpoente(listaTemp1, 4);
    lerPolinomio(listaTemp1);


    cout << "\n[DEMO Adicional] Pesquisa por expoente com opcional de possuir base ou nao" << endl;
    lerPolinomio(listaTemp1);
    cout << (acharExpoente(listaTemp1, 2, 1) ? "Expoente 2 (com base) foi encontrado no polinomio" : "Expoente 2 (com base) nao encontrado") << endl;
    cout << (acharExpoente(listaTemp1, 2, 0) ? "Expoente 2 (sem base) foi encontrado no polinomio" : "Expoente 2 (sem base) nao encontrado") << endl;
    cout << "\n\n";

    cout << "[DEMO] Soma de dois polinomios" << endl;
    inserirMonomio(listaTemp2, -7, true, 3); // -7X^3
    inserirMonomio(listaTemp2, -4, true, 2); // -4X^2
    inserirMonomio(listaTemp2, 10, true); // 10X
    inserirMonomio(listaTemp2, 20); // 20
    lerPolinomio(listaTemp2);

    inserirMonomio(listaTemp3, 2, true, 2); // 2X^2
    inserirMonomio(listaTemp3, -5, true); // -5X
    inserirMonomio(listaTemp3, 15, true, 5); // 15X^5
    inserirMonomio(listaTemp3, -10); // -10
    lerPolinomio(listaTemp3);

    cout << "Resultado: ";
    resultado1 = somarPolinomios(listaTemp2, listaTemp3);
    lerPolinomio(resultado1);
    cout << "\n\n";

    cout << "[DEMO] Subtracao de dois polinomios" << endl;
    lerPolinomio(listaTemp2);
    lerPolinomio(listaTemp3);

    cout << "Resultado: ";
    resultado2 = subtrairPolinomios(listaTemp2, listaTemp3);
    lerPolinomio(resultado2);
    cout << "\n\n";

    cout << "[DEMO] Multiplicacao de polinomio por um escalar" << endl;
    lerPolinomio(listaTemp2);

    cout << "Multiplicacao escalar por 3: ";
    resultado3 = multiplicacaoEscalar(listaTemp2, 3);
    lerPolinomio(resultado3);
    cout << "Multiplicacao escalar por -3: ";
    resultado4 = multiplicacaoEscalar(listaTemp2, -3);
    lerPolinomio(resultado4);
    cout << "\n\n";

    cout << "[DEMO] Multiplicacao de dois polinomios" << endl;
    lerPolinomio(listaTemp2);
    lerPolinomio(listaTemp3);

    cout << "Resultado: ";
    resultado5 = multiplicarPolinomios(listaTemp2, listaTemp3);
    lerPolinomio(resultado5);
    cout << "\n\n";

    cout << "[DEMO] Calculo do valor numerico do polinomio" << endl;
    lerPolinomio(listaTemp2);

    cout << "Resultado quando f(x) = 2: ";
    int resultadoFinal = determinarValor(listaTemp2, 2);
    // Calculadora cientifica resultou em -32
    cout << resultadoFinal;
    cout << "\n\n";
}

#endif