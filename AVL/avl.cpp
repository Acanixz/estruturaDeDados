#include <iostream>
using namespace std;

struct No{
    int chave;
    int altura;
    No *esq=NULL, *dir=NULL;
};

struct Arvore{
    No * raiz=NULL;
};

void prefixado( No *raiz ){
    if( raiz == NULL ) return;
    cout << raiz->chave << " (" << raiz->altura << ") ";
    prefixado( raiz->esq );
    prefixado( raiz->dir );
}

void infixado( No *raiz ){
    if( raiz == NULL ) return;
    infixado( raiz->esq );
    cout << raiz->chave << " (" << raiz->altura << ") ";
    infixado( raiz->dir );
}

void posfixado( No *raiz ){
    if( raiz == NULL ) return;
    posfixado( raiz->esq );
    posfixado( raiz->dir );
    cout << raiz->chave << " (" << raiz->altura << ") ";
}

int buscar_altura( No *raiz ){
    return (raiz == NULL) ? 0 : raiz->altura;
}

void buscar_maior( No *&raiz, int &chave ){
    if( raiz == NULL ) return;
    if( raiz->dir != NULL )
        buscar_maior( raiz->dir, chave);
    else
        chave = raiz->chave;
}

int calcular_altura( No *raiz ){
    int alt_e = buscar_altura(raiz->esq);
    int alt_d = buscar_altura(raiz->dir);
    return (alt_e > alt_d) ? alt_e+1 : alt_d+1;
}

No * rotacao_simples_direita( No *k ){
    No *x = k->esq;
    No *t2 = x->dir;

    x->dir = k;
    k->esq = t2;
    k->altura = calcular_altura(k);
    x->altura = calcular_altura(x);
    return x;
}

No * rotacao_dupla_direita( No *k ){
    return NULL;
}

No * rotacao_simples_esquerda( No *k ){
    return NULL;
}

No * rotacao_dupla_esquerda( No *k ){
    return NULL;
}

No * rotacao_avl( No * k ){
    if( buscar_altura(k->esq) > buscar_altura(k->dir) ){ // Rotação a direita
        No * x = k->esq;
        if( buscar_altura(x->dir) > buscar_altura(x->esq) )
            return rotacao_dupla_direita(k);
        else
            return rotacao_simples_direita(k);
    }
    else{ // Rotação a esquerda
        No * y = k->dir;
        if( buscar_altura(y->esq) > buscar_altura(y->dir) )
            return rotacao_dupla_esquerda(k);
        else
            return rotacao_simples_esquerda(k);
    }
}

No * inserirArvore( No *raiz, int chave ){
    if( raiz == NULL ){
        raiz = new No;
        raiz->chave = chave;
        raiz->altura = 1;
        return raiz;
    }
    if( chave < raiz->chave )
        raiz->esq = inserirArvore( raiz->esq, chave );
    else
        raiz->dir = inserirArvore( raiz->dir, chave );
    int alt_e = buscar_altura(raiz->esq);
    int alt_d = buscar_altura(raiz->dir);
    if( alt_e-alt_d == 2 || alt_e-alt_d == -2 ) raiz = rotacao_avl(raiz);
    else raiz->altura = (alt_e > alt_d) ? alt_e+1 : alt_d+1;
    return raiz;
}

void inserirArvore( Arvore &a, int chave ){
    a.raiz = inserirArvore( a.raiz, chave );
}

No * retirarArvore( No *&raiz, int chave ){
    if( raiz == NULL ) return NULL;

    if( raiz->chave == chave ){
        if( raiz->esq == NULL && raiz->dir == NULL ) return NULL;
        if( raiz->esq != NULL && raiz->dir == NULL ) return raiz->esq;
        if( raiz->esq == NULL && raiz->dir != NULL ) return raiz->dir;
        int ch_aux;
        buscar_maior(raiz->esq, ch_aux);
        raiz->chave = ch_aux;
        raiz->esq = retirarArvore(raiz->esq, ch_aux);
        return raiz;
    }

    if( chave < raiz->chave )
        raiz->esq = retirarArvore(raiz->esq, chave );
    if( chave > raiz->chave )
        raiz->dir = retirarArvore(raiz->dir, chave );

    int alt_e = buscar_altura(raiz->esq);
    int alt_d = buscar_altura(raiz->dir);
    if( alt_e-alt_d == 2 || alt_e-alt_d == -2 ) raiz = rotacao_avl(raiz);
    else raiz->altura = (alt_e > alt_d) ? alt_e+1 : alt_d+1;

    return raiz;
}

void retirarArvore( Arvore &a, int chave ){
    a.raiz = retirarArvore( a.raiz, chave );
}

int altura( No *raiz ){
    if( raiz == NULL ) return 0;
    return raiz->altura;
}

int altura( Arvore a ){
    return altura( a.raiz );
}

int main(){
    Arvore a;
    int chave, op, cont;

    do{
        cout << endl << "Menu de opcoes:" << endl;
        cout << "\t 1 - Inserir na arvore" << endl;
        cout << "\t 2 - Retirar da arvore" << endl;
        cout << "\t 3 - Caminhamento prefixado" << endl;
        cout << "\t 4 - Caminhamento infixado" << endl;
        cout << "\t 5 - Caminhamento posfixado" << endl;
        cout << "\t 6 - Calcular a altura" << endl;
        cout << "\t 0 - fim" << endl;
        cout << "\t\tOpcao: ";
        cin >> op;

        switch( op ){
            case 1: // Inserir
                    cout << "Insercao:" << endl;
                    cout << "\tDigite a chave (int): ";
                    cin >> chave;
                    inserirArvore(a, chave);
                    cout << "Valor inserido com sucesso" << endl;
                    break;
            case 2: // Retirar a chave
                    cout << "Retirada:" << endl;
                    cout << "Digite a chave (int): ";
                    cin >> chave;
                    retirarArvore(a, chave);
                    cout << "Valor retirado (se existir)" << endl;
                    break;
            case 3: // Caminhamento prefixado
                    cout << "Prefixado => ";
                    prefixado( a.raiz );
                    cout << endl;
                    break;
            case 4: // Caminhamento infixado
                    cout << "Infixado => ";
                    infixado( a.raiz );
                    cout << endl;
                    break;
            case 5: // Caminhamento posfixado
                    cout << "Posfixado => ";
                    posfixado( a.raiz );
                    cout << endl;
                    break;
            case 6: // Calcular a altura da arvore
                    cont = altura(a);
                    cout << "A altura da arvore eh " << cont << " niveis" << endl;
                    break;
            case 0 : // Somente para não dar msg de erro
                    break;
            default:
                    cout << "Erro: Opcao invalida!";
                    break;
        }
    }while( op != 0 );
    cout << endl;
}
