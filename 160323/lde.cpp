#include <iostream>
using namespace std;

struct No{
    char info;
    No *eloA, *eloP;
};

struct LDE{
    No *comeco, *fim;
};

void inicializarLDE(LDE &lista){
    lista.comeco = NULL;
    lista.fim = NULL;
}

// A variável sentido pode ser C(crescente) ou D(decrescente)
void mostrarLDE(LDE lista, char frase[], char sentido){
    cout << frase << ": ";
    if( lista.comeco == NULL ) cout << " vazia";

    No *aux = (sentido == 'C') ? lista.comeco : lista.fim;
    while( aux != NULL ){
        cout << aux->info << " ";
        aux = (sentido == 'C') ? aux->eloP : aux->eloA;
    }
}

bool inserirLDE( LDE &lista, char valor ){
    No *novo = new No;

    if( novo == NULL ) return false;
    novo->info = valor;
    novo->eloA = NULL;
    novo->eloP = NULL;

    // Inserir em lista vazia
    if( lista.comeco == NULL ){
        lista.comeco = novo;
        lista.fim = novo;
        return true;
    }

    // Inserir no inicio da lista
    if( valor < lista.comeco->info ){
        novo->eloP = lista.comeco;
        lista.comeco->eloA = novo;
        lista.comeco = novo;
        return true;
    }

    // Inserir no final da lista
    if( valor > lista.fim->info ){
        lista.fim->eloP = novo;
        novo->eloA = lista.fim;
        lista.fim = novo;
        return true;
    }

    // Inserir no meio da lista
    No *aux = lista.comeco;
    while( aux->info < valor && aux->eloP->info < valor )
        aux = aux->eloP;
    novo->eloP = aux->eloP;
    novo->eloA = aux;
    aux->eloP->eloA = novo;
    aux->eloP = novo;
    return true;
}

bool inserirFinalLDE( LDE &lista, char valor ){
    No *novo = new No;

    if( novo == NULL ) return false;
    novo->info = valor;
    novo->eloA = NULL;
    novo->eloP = NULL;

    // Inserir em lista vazia
    if( lista.comeco == NULL ){
        lista.comeco = novo;
        lista.fim = novo;
    } else {
        lista.fim->eloP = novo;
        novo->eloA = lista.fim;
        lista.fim = novo;
    }
    return true;
}

No *buscarLDE( LDE lista, char valor ){
    No *aux = lista.comeco;
    while( aux != NULL ){
        if( aux->info == valor ) return aux;
        aux = aux->eloP;
    }
    return NULL;
}

bool retirarLDE( LDE &lista, char valor ){
    No *pos;

    pos = buscarLDE(lista,valor);
    if( pos == NULL ) return false;  // Lista vazia ou valor não encontrado

    // Retirada no inicio da lista
    if( pos == lista.comeco ){
        No *prox = pos->eloP; // Pega o próximo nó
        lista.comeco = prox;
        if( prox != NULL ) prox->eloA = NULL;
        if( pos == lista.fim ) lista.fim = NULL;
    }
    else{
        No *ant = pos->eloA; // Pega o nó anterior
        No *prox = pos->eloP; // Pega o nó seguinte
        if( ant != NULL ) ant->eloP = prox;
        if( prox != NULL ) prox->eloA = ant;
        if( pos == lista.fim ) lista.fim = ant;
    }
    delete( pos );
    return true;
}

int main(){

    LDE lista1;

    inicializarLDE(lista1);
    inserirLDE(lista1, 'P');
    inserirLDE(lista1, 'E');
    inserirLDE(lista1, 'R');
    inserirLDE(lista1, 'N');
    inserirLDE(lista1, 'A');
    inserirLDE(lista1, 'M');
    inserirLDE(lista1, 'B');
    inserirLDE(lista1, 'U');
    inserirLDE(lista1, 'C');
    inserirLDE(lista1, 'O');
    mostrarLDE( lista1, "Lista 1", 'C' );

    cout << endl;


    LDE lista2;

    inicializarLDE(lista2);
    inserirFinalLDE(lista2, 'P');
    inserirFinalLDE(lista2, 'E');
    inserirFinalLDE(lista2, 'R');
    inserirFinalLDE(lista2, 'N');
    inserirFinalLDE(lista2, 'A');
    inserirFinalLDE(lista2, 'M');
    inserirFinalLDE(lista2, 'B');
    inserirFinalLDE(lista2, 'U');
    inserirFinalLDE(lista2, 'C');
    inserirFinalLDE(lista2, 'O');
    mostrarLDE( lista2, "Lista 2", 'C' );
    cout << endl;

    retirarLDE( lista2, 'A' );
    retirarLDE( lista2, 'E' );
    retirarLDE( lista2, 'U' );
    retirarLDE( lista2, 'B' );
    retirarLDE( lista2, 'M' );
    retirarLDE( lista2, 'C' );
    mostrarLDE( lista2, "Lista 2 (apos retirar)", 'C' );
    cout << endl;
    retirarLDE( lista2, 'P' );
    retirarLDE( lista2, 'R' );
    retirarLDE( lista2, 'N' );
    retirarLDE( lista2, 'O' );
    mostrarLDE( lista2, "Lista 2 (apos retirar)", 'C' );
    cout << endl;

    /*
    No *aux = buscarLUE(lista2, 'A');
    if( aux == NULL )
        cout << "Elemento nao encontrado";
    else
        cout << "Elemento presente na lista";

        */
    cout << endl;
}
