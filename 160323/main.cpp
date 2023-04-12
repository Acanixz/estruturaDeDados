#include <iostream>
using namespace std;

// Lista unicamente encadeada
struct Node{
    char info;
    Node* elo;
};

struct LUE{
    Node *start, *end;
};

void InicializarLUE(LUE &lista){
    lista.start = NULL;
    lista.end = NULL;
}

void mostrarLista(LUE &lista){
    if (lista.start == NULL) cout << "Lista vazia\n" << endl;
    else {
        cout << "Mostrando lista: \n" << endl;
        int cont = 0;
        Node *aux;
        aux = lista.start;
        while (aux != NULL){
            cout << "index " << cont << ": " << aux->info << endl;
            aux = aux->elo;
            cont++;
        }
        cout << endl;
        cout << "COMECO: " << lista.start->info << endl;
        cout << "FIM: " << lista.end->info << endl;
        cout << endl;
    }
}

bool inserir(LUE &lista, char valor){
    Node* novoNode = new Node;
    novoNode->info = valor;

    if (lista.start == NULL){ // Lista vazia
        novoNode->elo = NULL;
        lista.start = novoNode;
        lista.end = novoNode;
        return true;
    }

    if (valor < lista.start->info) { // Inserir no começo
        novoNode->elo = lista.start;
        lista.start = novoNode;
        return true;
    }

    if (valor > lista.end->info) { // Inserir no final
        novoNode->elo = NULL;
        lista.end->elo = novoNode;
        lista.end = novoNode;
        return true;
    }

    // Inserir no meio
    Node* aux = lista.start;

    while (valor > aux->elo->info){
        aux = aux->elo;
    }
    novoNode->elo = aux->elo;
    aux->elo = novoNode;
    return true;
}

bool inserirFinal(LUE &lista, char valor){
    Node* novoNode = new Node;
    novoNode->info = valor;

    if (lista.start == NULL){ // Lista vazia
        novoNode->elo = NULL;
        lista.start = novoNode;
        lista.end = novoNode;
        return true;
    } else {
        novoNode->elo = NULL;
        lista.end->elo = novoNode;
        lista.end = novoNode;
        return true;
    }
}

Node* buscarLUE(LUE &lista, char valor){
    Node* aux = lista.start;
    while (aux != NULL)
    {
        if (aux->info == valor) {
            return aux;
        }
        aux = aux->elo;
    }
    
    return NULL;
}

bool retirarLista(LUE &lista, char valor){
    if ((lista.start == lista.end) && lista.start->info == valor){
        delete lista.start;
        lista.start = NULL;
        lista.end = NULL;
        return true;
    }

    if (lista.start->info == valor){
        Node* aux;
        aux = lista.start;
        lista.start = lista.start->elo;
        delete aux;
    }

    Node *aux = lista.start, *backAux = aux;
    while (aux != NULL){
        if (aux->info == valor) {
            backAux->elo = aux->elo;

            if (lista.end == aux){
                lista.end = backAux;
            }
            delete aux;
            return true;
        }
        backAux = aux;
        aux = aux->elo;
    }
    
    return false;
}

int tamanhoLista(LUE &lista){
    int tam = 0;
    Node *aux = lista.start;
    while (aux != NULL)
    {
        tam++;
        aux = aux->elo;
    }
    return tam;
}

LUE obterRepetidos(LUE lista1, LUE lista2){
    LUE listaRepetida;
    InicializarLUE(listaRepetida);

    Node *L1Aux = lista1.start;
    while (L1Aux != NULL)
    {
        Node *L2Aux = lista2.start;
        while (L2Aux != NULL)
        {
            if (L1Aux->info == L2Aux->info){
                inserir(listaRepetida, L1Aux->info);
            }
            L2Aux = L2Aux->elo;
        }
        
        L1Aux = L1Aux->elo;
    }
    return listaRepetida;
}

int main(){
    LUE lista1;
    InicializarLUE(lista1);
    mostrarLista(lista1);
    inserir(lista1, 'P');
    inserir(lista1, 'E');
    inserir(lista1, 'R');
    inserir(lista1, 'N');
    inserir(lista1, 'A');
    inserir(lista1, 'M');
    inserir(lista1, 'B');
    inserir(lista1, 'U');
    inserir(lista1, 'C');
    inserir(lista1, 'O');
    mostrarLista(lista1);

    LUE lista2;
    InicializarLUE(lista2);
    mostrarLista(lista2);
    inserirFinal(lista2, 'P');
    inserirFinal(lista2, 'E');
    inserirFinal(lista2, 'R');
    inserirFinal(lista2, 'N');
    inserirFinal(lista2, 'A');
    inserirFinal(lista2, 'M');
    inserirFinal(lista2, 'B');
    inserirFinal(lista2, 'U');
    inserirFinal(lista2, 'C');
    inserirFinal(lista2, 'O');
    mostrarLista(lista2);
    retirarLista(lista2, 'P');
    retirarLista(lista2, 'R');
    retirarLista(lista2, 'O');
    mostrarLista(lista2);

    LUE listaRepetida = obterRepetidos(lista1, lista2);
    mostrarLista(listaRepetida);
    return 0;
}