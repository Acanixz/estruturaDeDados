#include <iostream>
using namespace std;

struct No{
    char info;
    No *elo;
};

struct LUE{
    No *comeco, *fim;
};

void inicializarLUE(LUE &lista){
    lista.comeco = NULL;
    lista.fim = NULL;
}

void mostrarLUE(LUE lista, char frase[]){
    cout << frase << ": ";
    if( lista.comeco == NULL ) cout << " vazia";

    No *aux = lista.comeco;
    while( aux != NULL ){
        cout << aux->info << " ";
        aux = aux->elo;
    }
}

bool inserirLUE( LUE &lista, char valor ){
    No *novo = new No;

    if( novo == NULL ) return false;
    novo->info = valor;
    novo->elo = NULL;

    // Inserir em lista vazia
    if( lista.comeco == NULL ){
        lista.comeco = novo;
        lista.fim = novo;
        return true;
    }

    // Inserir no inicio da lista
    if( valor < lista.comeco->info ){
        novo->elo = lista.comeco;
        lista.comeco = novo;
        return true;
    }

    // Inserir no final da lista
    if( valor > lista.fim->info ){
        lista.fim->elo = novo;
        lista.fim = novo;
        return true;
    }

    // Inserir no meio da lista
    No *aux = lista.comeco;
    while( aux->info < valor && aux->elo->info < valor )
        aux = aux->elo;
    novo->elo = aux->elo;
    aux->elo = novo;
    return true;
}

bool inserirFinalLUE( LUE &lista, char valor ){
    No *novo = new No;

    if( novo == NULL ) return false;
    novo->info = valor;
    novo->elo = NULL;

    // Inserir em lista vazia
    if( lista.comeco == NULL ){
        lista.comeco = novo;
        lista.fim = novo;
    } else {
        lista.fim->elo = novo;
        lista.fim = novo;
    }
    return true;
}

No *buscarLUE( LUE lista, char valor ){
    No *aux = lista.comeco;
    while( aux != NULL ){
        if( aux->info == valor ) return aux;
        aux = aux->elo;
    }
    return NULL;
}

bool retirarLUE( LUE &lista, char valor ){
    No *ant=NULL, *pos;

    pos = lista.comeco;
    while( pos != NULL && pos->info != valor ){
        ant = pos;
        pos = pos->elo;
    }
    if( pos == NULL ) return false;  // Lista vazia ou valor não encontrado

    // Retirada no inicio da lista
    if( pos == lista.comeco ){
        lista.comeco = lista.comeco->elo;
        if( pos == lista.fim ) lista.fim = NULL;
    }
    else{
        ant->elo = pos->elo;
        if( pos == lista.fim ) lista.fim = ant;
    }
    delete( pos );
    return true;
}

int main(){
    /*
    LUE lista1;

    inicializarLUE(lista1);
    inserirLUE(lista1, 'P');
    inserirLUE(lista1, 'E');
    inserirLUE(lista1, 'R');
    inserirLUE(lista1, 'N');
    inserirLUE(lista1, 'A');
    inserirLUE(lista1, 'M');
    inserirLUE(lista1, 'B');
    inserirLUE(lista1, 'U');
    inserirLUE(lista1, 'C');
    inserirLUE(lista1, 'O');
    mostrarLUE( lista1, "Lista 1" );

    cout << endl;
    */

    LUE lista2;

    inicializarLUE(lista2);
    inserirFinalLUE(lista2, 'P');
    inserirFinalLUE(lista2, 'E');
    inserirFinalLUE(lista2, 'R');
    inserirFinalLUE(lista2, 'N');
    inserirFinalLUE(lista2, 'A');
    inserirFinalLUE(lista2, 'M');
    inserirFinalLUE(lista2, 'B');
    inserirFinalLUE(lista2, 'U');
    inserirFinalLUE(lista2, 'C');
    inserirFinalLUE(lista2, 'O');
    mostrarLUE( lista2, "Lista 2" );
    cout << endl;

    retirarLUE( lista2, 'A' );
    retirarLUE( lista2, 'E' );
    retirarLUE( lista2, 'U' );
    retirarLUE( lista2, 'B' );
    retirarLUE( lista2, 'M' );
    retirarLUE( lista2, 'C' );
    mostrarLUE( lista2, "Lista 2 (apos retirar)" );
    cout << endl;
    retirarLUE( lista2, 'P' );
    retirarLUE( lista2, 'R' );
    retirarLUE( lista2, 'N' );
    retirarLUE( lista2, 'O' );
    mostrarLUE( lista2, "Lista 2 (apos retirar)" );
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
