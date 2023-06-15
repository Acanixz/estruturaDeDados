// Gerenciador de usuarios com arvore AVL
// Aluno: Hérick Vitor Vieira Bittencourt
// Estrutura de dados 2023

// Histórico de desenvolvimento disponivel em:
// https://github.com/Acanixz/estruturaDeDados
// (apenas após fechamento da M2)

#include <iostream>
using namespace std;

// Struct das informações do usuario
struct Info{
    unsigned long long int cpf;
    string nome;
    string profissao;
};

// Struct Nó da arvore
struct No{
    Info *info;
    int altura;
    No *esq=NULL, *dir=NULL;
};

// Struct da arvore
struct Arvore{
    No * raiz=NULL;
};

// Usado para listagem
void infixado( No *raiz, int tipo){
    if( raiz == NULL ) return;
    infixado( raiz->esq, tipo);

    // A listagem deixa no topo o valor cujo foi usado para listagem
    // 0 = CPF
    // 1 = Nome
    if (tipo == 0){
        cout << "\nCPF: " << raiz->info->cpf <<  " (" << raiz->altura <<  ") " << endl;
        cout << "Nome: " << raiz->info->nome << endl;
        cout << "Profissão: " << raiz->info->profissao << endl;
    } else {
        cout << "\nNome: " << raiz->info->nome <<  " (" << raiz->altura <<  ") " << endl;
        cout << "CPF: " << raiz->info->cpf << endl;
        cout << "Profissão: " << raiz->info->profissao << endl;
    }

    infixado( raiz->dir, tipo);
}

// Retorna altura da raiz ou 0
int buscar_altura( No *raiz ){
    return (raiz == NULL) ? 0 : raiz->altura;
}

// Busca o maior nó na raiz especificada
void buscar_maior( No *&raiz, Info *&info ){ // 
    if( raiz == NULL ) return;
    if( raiz->dir != NULL )
        buscar_maior( raiz->dir, info);
    else
        info = raiz->info;
}

// Calcula a altura do no levando em base os nós filhos
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
    No *x = k->esq;
    No *w = x->dir;
    No *t2 = w->esq;
    No *t3 = w->dir;

    w->dir = k;
    k->esq = t3;
    x->dir = t2;


    k->altura = calcular_altura(k);
    x->altura = calcular_altura(x);
    return w;
}

No * rotacao_simples_esquerda( No *k ){
    No *y = k->dir;
    No *t2 = y->esq;

    y->esq = k;
    k->dir = t2;
    k->altura = calcular_altura(k);
    y->altura = calcular_altura(y);
    return y;
}

No * rotacao_dupla_esquerda( No *k ){
    No *y = k->dir;
    No *z = y->esq;
    No *t2 = z->dir;
    No *t3 = z->esq;

    z->esq = k;
    z->dir = y;
    k->dir = t2;
    y->esq = t3;

    k->altura = calcular_altura(k);
    y->altura = calcular_altura(y);
    z->altura = calcular_altura(z);
    return z;
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

// Insere um Nó na arvore
No * inserirArvore( No *raiz, Info *info, int tipo){
    if( raiz == NULL ){ // Local de inserção encontrado
        raiz = new No;
        raiz->info = info;
        raiz->altura = 1;
        return raiz;
    }

    switch (tipo){
        case 0:{ // Inserir em uma arvore ordenada por CPF
            if( info->cpf < raiz->info->cpf ) // Precisa ir p/ esquerda (valor menor que atual)
                raiz->esq = inserirArvore( raiz->esq, info, tipo);
            else // Precisa ir p/ direita (valor maior que atual)
                raiz->dir = inserirArvore( raiz->dir, info, tipo);

            // Checagem de altura dos nós filhos por desequilibrio
            int alt_e = buscar_altura(raiz->esq);
            int alt_d = buscar_altura(raiz->dir);

            if( alt_e-alt_d == 2 || alt_e-alt_d == -2 ) raiz = rotacao_avl(raiz);
            else raiz->altura = (alt_e > alt_d) ? alt_e+1 : alt_d+1;
            break;
        }

        case 1:{ // Inserir em uma arvore ordenada por Nome
            if( info->nome < raiz->info->nome) // Precisa ir p/ esquerda (valor menor que atual)
                raiz->esq = inserirArvore( raiz->esq, info, tipo);
            else // Precisa ir p/ direita (valor maior que atual)
                raiz->dir = inserirArvore( raiz->dir, info, tipo);

            // Checagem de altura dos nós filhos por desequilibrio
            int alt_e = buscar_altura(raiz->esq);
            int alt_d = buscar_altura(raiz->dir);

            if( alt_e-alt_d == 2 || alt_e-alt_d == -2 ) raiz = rotacao_avl(raiz);
            else raiz->altura = (alt_e > alt_d) ? alt_e+1 : alt_d+1;
            break;
        }

    }
    return raiz;
}

void inserirArvore( Arvore &a, Info *info, int tipo){
    a.raiz = inserirArvore( a.raiz, info, tipo);
}

// Busca por informação nas arvores via métodos com sobrecarga (CPF e Nome)
Info * buscarArvore(No *&raiz, unsigned long long int CPF){  // Busca na arvore por CPF
    if( raiz == NULL ) return NULL;

    if( raiz->info->cpf == CPF )
        return raiz->info;

    if( CPF < raiz->info->cpf )
        return buscarArvore(raiz->esq, CPF );

    if( CPF > raiz->info->cpf )
        return buscarArvore(raiz->dir, CPF );

    return NULL; // Evita aviso de end of non-void function
}

Info * buscarArvore( Arvore &a, unsigned long long int CPF ){
    return buscarArvore(a.raiz, CPF);
}

Info * buscarArvore(No *&raiz, string nome){  // Busca na arvore por Nome
    if( raiz == NULL ) return NULL;

    if( raiz->info->nome == nome )
        return raiz->info;

    if( nome < raiz->info->nome )
        return buscarArvore(raiz->esq, nome );

    if( nome > raiz->info->nome )
        return buscarArvore(raiz->dir, nome );

    return NULL; // Evita aviso de end of non-void function
}

Info * buscarArvore( Arvore &a, string nome ){
    return buscarArvore(a.raiz, nome);
}

// Remoção de um valor da arvore (também possui sobrecarga p/ localizar corretamente)
No * retirarArvore( No *&raiz, unsigned long long int CPF ){ // Remoção da arvore por CPF
    if( raiz == NULL ) return NULL;

    if( raiz->info->cpf == CPF ){
        if( raiz->esq == NULL && raiz->dir == NULL ) return NULL;
        if( raiz->esq != NULL && raiz->dir == NULL ) return raiz->esq;
        if( raiz->esq == NULL && raiz->dir != NULL ) return raiz->dir;
        Info* ch_aux;
        buscar_maior(raiz->esq, ch_aux);
        raiz->info = ch_aux;
        raiz->esq = retirarArvore(raiz->esq, ch_aux->cpf);
        return raiz;
    }

    if( CPF < raiz->info->cpf )
        raiz->esq = retirarArvore(raiz->esq, CPF );
    if( CPF > raiz->info->cpf )
        raiz->dir = retirarArvore(raiz->dir, CPF );

    int alt_e = buscar_altura(raiz->esq);
    int alt_d = buscar_altura(raiz->dir);
    if( alt_e-alt_d == 2 || alt_e-alt_d == -2 ) raiz = rotacao_avl(raiz);
    else raiz->altura = (alt_e > alt_d) ? alt_e+1 : alt_d+1;

    return raiz;
}

void retirarArvore( Arvore &a, unsigned long long int CPF ){
    a.raiz = retirarArvore( a.raiz, CPF );
}

No * retirarArvore( No *&raiz, string nome ){ // Remoção da arvore por Nome
    if( raiz == NULL ) return NULL;

    if( raiz->info->nome == nome ){
        if( raiz->esq == NULL && raiz->dir == NULL ) return NULL;
        if( raiz->esq != NULL && raiz->dir == NULL ) return raiz->esq;
        if( raiz->esq == NULL && raiz->dir != NULL ) return raiz->dir;
        Info* ch_aux;
        buscar_maior(raiz->esq, ch_aux);
        raiz->info = ch_aux;
        raiz->esq = retirarArvore(raiz->esq, ch_aux->nome);
        return raiz;
    }

    if( nome < raiz->info->nome )
        raiz->esq = retirarArvore(raiz->esq, nome );
    if( nome > raiz->info->nome )
        raiz->dir = retirarArvore(raiz->dir, nome );

    int alt_e = buscar_altura(raiz->esq);
    int alt_d = buscar_altura(raiz->dir);
    if( alt_e-alt_d == 2 || alt_e-alt_d == -2 ) raiz = rotacao_avl(raiz);
    else raiz->altura = (alt_e > alt_d) ? alt_e+1 : alt_d+1;

    return raiz;
}

void retirarArvore( Arvore &a, string nome ){
    a.raiz = retirarArvore( a.raiz, nome );
}

// Retorna a altura do Nó ou 0
int altura( No *raiz ){
    if( raiz == NULL ) return 0;
    return raiz->altura;
}

int altura( Arvore a ){
    return altura( a.raiz );
}

// Deleta uma informação da memoria
void deletarInfo(Info *info){
    delete info;
}

// Deletação da arvore por completo seguindo o algoritmo de busca posfixado
// caso deletarTudo seja true, a informação é deletada também
void deletarArvore( No *raiz, bool deletarTudo = false){
    if( raiz == NULL ) return;
    deletarArvore( raiz->esq, deletarTudo);
    deletarArvore( raiz->dir, deletarTudo);
    if (deletarTudo){
        deletarInfo(raiz->info);
    }

    delete raiz;
}

int main(){
    Arvore arvore_CPF, arvore_Nome; // Arvores AVL
    int tipo, op; // tipo de busca e operação do menu
    unsigned long long int CPF;
    string nome, profissao;

    do{
        cout << endl << "Menu de opcoes:" << endl;
        cout << "\t 1 - Inserir novo usuario" << endl;
        cout << "\t 2 - Remover usuario" << endl;
        cout << "\t 3 - Pesquisar usuario" << endl;
        cout << "\t 4 - Listar todos os usuarios" << endl;
        cout << "\t 5 - Sair" << endl;
        cout << "\t\tOpcao: ";
        cin >> op;

        switch( op ){
            case 1:{ // Inserir usuario
                    cout << "Insercao:" << endl;
                    cout << "\tDigite o nome (string): ";
                    cin >> nome;
                    cout << "\tDigite o CPF (int):";
                    cin >> CPF;
                    cout << "\tDigite a profissao (string): ";
                    cin >> profissao;

                    // Geração da Info na memoria
                    Info* info = new Info;
                    info->nome = nome;
                    info->cpf = CPF;
                    info->profissao = profissao;

                    inserirArvore(arvore_CPF, info, 0); // Inserção arvore CPF
                    inserirArvore(arvore_Nome, info, 1); // Inserção arvore Nome

                    cout << "Usuario adicionado com sucesso" << endl;
                    break;
                }
            case 2:{ // Remover usuario
                    cout << "Retirada:" << endl;
                    do {
                        cout << "Procurar por\n1 - Nome\n0 - CPF" << endl;
                        cout << "\t\tOpcao: ";
                        cin >> tipo;
                    } while (tipo < 0 || tipo > 1);
                    
                    Info *alvo;

                    if (tipo == 0) {
                        cout << "digite o CPF (int): ";
                        cin >> CPF;
                        alvo = buscarArvore(arvore_CPF, CPF);
                    } else {
                        cout << "digite o Nome (string): ";
                        cin >> nome;
                        alvo = buscarArvore(arvore_Nome, nome);
                    }

                    if (alvo != NULL){ // Nó alvo encontrado
                        retirarArvore(arvore_CPF, alvo->cpf);
                        retirarArvore(arvore_Nome, alvo->nome);
                        cout << "Usuario removido" << endl;
                    } else {
                        cout << "Usuario nao foi encontrado" << endl;
                    }
                    
                    break;
                }

            case 3: { // Pesquisa de usuario
                cout << "Pesquisar usuario:" << endl;
                 do {
                        cout << "Procurar por\n1 - Nome\n0 - CPF" << endl;
                        cout << "\t\tOpcao: ";
                        cin >> tipo;
                } while (tipo < 0 || tipo > 1);

                Info *alvo;
                    

                if (tipo == 0) {
                    cout << "digite o CPF (int): ";
                    cin >> CPF;
                    alvo = buscarArvore(arvore_CPF, CPF);
                } else {
                    cout << "digite o Nome (string): ";
                    cin >> nome;
                    alvo = buscarArvore(arvore_Nome, nome);
                }

                if (alvo != NULL){
                    cout << "Usuario encontrado com sucesso" << endl;
                    cout << "Nome: " << alvo->nome << endl;
                    cout << "CPF: " << alvo->cpf << endl;
                    cout << "Profissao: " << alvo->profissao << endl;
                } else {
                    cout << "Usuario nao encontrado" << endl;
                }
                break;
            }

            case 4: { // Listagem total por Nome ou CPF
                cout << "Listar todos os usuarios:" << endl;
                 do {
                        cout << "Listar por\n1 - Nome\n0 - CPF" << endl;
                        cout << "\t\tOpcao: ";
                        cin >> tipo;
                } while (tipo < 0 || tipo > 1);

                if (tipo == 0) {
                    cout << "\nLista de usuarios por CPF: " << endl;
                    infixado(arvore_CPF.raiz, 0);
                } else {
                    cout << "\nLista de usuarios por nome: " << endl;
                    infixado(arvore_Nome.raiz, 1);
                }

                if (arvore_CPF.raiz == NULL) cout << "Lista vazia!" << endl;
                break;
            }
            case 5 : // Saida do programa, ambas arvores são deletadas primeiro
                    deletarArvore(arvore_CPF.raiz);
                    deletarArvore(arvore_Nome.raiz, true); // Info já pode ser deletada nesse ponto
                    break;
            default:
                    cout << "Erro: Opcao invalida!";
                    break;
        }
    }while( op != 5 );
    cout << endl;
}
