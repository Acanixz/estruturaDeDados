// Atividade de Implementação 3 – Ordenação
// Aluno: Hérick Vitor Vieira Bittencourt
// Estrutura de dados 2023

// Código fonte disponivel em:
// https://github.com/Acanixz/estruturaDeDados
// (apenas após fechamento da M3)

#include <iostream>
#include <chrono>

using namespace std;

// Struct utilizado p/ armazenamento do pior/melhor vetor de um algoritmo
struct recorde{
    double tempo = 0;
    int *vetor = nullptr;
};

// Cria valores aleatórios em cada indice do vetor
void aleatorizar(int* vetor, int tam, int valorMax){
    for (int i = 0; i < tam; i++){
        int val;
        val = rand() % valorMax;
        vetor[i] = val;
    }
}

// Cria um vetor ordenado de forma crescente (melhor caso)
void crescente(int* vetor, int tam){
    for (int i = 0; i < tam; i++){
        vetor[i] = i + 1;
    }
}

// Cria um vetor ordenado de forma decrescente (pior caso)
void decrescente(int* vetor, int tam){
    for (int i = 0; i < tam; i++){
        vetor[i] = tam - i;
    }
}

// Mostra o vetor na tela
void mostrarVetor(int* vetor, int tam){
    cout << "[";
    for (int i = 0; i < tam; i++){
        cout << vetor[i] << ((i+1 < tam) ? ", " : "");
    }
    cout << "]\n";
}

// Ordenacao por insercao direta
// Descricao:
//            for loop (comeca em j=1 e vai até o final do vetor)
//            o valor de vetor[j] é armazenado na chave
//              while loop (comeca em j-1 e vai até o comeco do vetor)
//              o loop vai movendo os valores para suas posicões a frente
//              até encontrar um valor que é menor que a chave ou i chegar em -1
//            ao sair do while loop, o valor que estava na chave é colocado em seu lugar definitivo
void insercaoDireta(int* vetor, int tam){
    int chave, i;
    for( int j=1; j < tam; j++ ){
        chave = vetor[j];
        i = j - 1;
        while( i >= 0 && vetor[i] > chave ){
            vetor[i+1] = vetor[i];
            i--;
        }
        vetor[i+1] = chave;
    }
}

// Ordenacao bubble sort
// Descrição:
//            Percorre o array em busca de um valor fora da ordem crescente
//            se encontrar, ele troca de posição com o valor a frente e o processo
//            repete até que o array seja percorrido sem valores fora da ordem crescente
void bubbleSort(int* vetor, int tam) {
    bool trocou = true;
    int limite = tam - 1;
    int k = 0;
    while (trocou)
    {
        trocou = false;
        for (int i = 0; i < limite; i++) {
            if (vetor[i] > vetor[i + 1]) {
                int temp = vetor[i + 1];
                vetor[i + 1] = vetor[i];
                vetor[i] = temp;
                k = i;
                trocou = true;
            }
        }
        limite = k;
    }
}

// Ordenacao por selection sort
// Descricao:
//            A funcao realiza dois for loops, o primeiro para certificar que a ordenacao
//            ocorrerá no vetor completo, no segundo for loop, o código tenta encontrar o menor valor
//            possivel, ao final do segundo for, o valor do indice atual (i) e o do menor valor trocam de lugar
//            o primeiro for loop entao repete o processo até chegar ao final, onde o vetor estará ordenado
void selecao(int* vetor, int tam){
    int pos_menor, temp;

    for( int i=0; i < tam-1; i++ ){
        pos_menor = i;
        for( int j=i+1; j < tam; j++ ){
            if( vetor[j] < vetor[pos_menor] ) pos_menor = j;
        }
        temp = vetor[i];
        vetor[i] = vetor[pos_menor];
        vetor[pos_menor] = temp;
    }
}

// Orndecao por merge sort
// Descricao:
//            Merge sort visa dividir o vetor de forma recursiva em partes menores
//            até que seja possivel retornar e ordenar os valores, avaliando os pedacos menores
//            enquanto retorna, ao voltar para o comeco da stack, haverá apenas uma avaliacao de dois vetores
//            ordenados p/ realizar, merge sort possui a complexidade de O(n log n) em todos os cenários
void combinar( int* vetor, int comeco, int meio, int fim ){
    int com1 = comeco, com2 = meio+1, comAux = 0, tam = fim-comeco+1;
    int *vetAux = new int[tam];

    while(com1 <= meio && com2 <= fim){
        if(vetor[com1] < vetor[com2]) {
            vetAux[comAux] = vetor[com1];
            com1++;
        } else {
            vetAux[comAux] = vetor[com2];
            com2++;
        }
        comAux++;
    }

    while(com1 <= meio){
        vetAux[comAux] = vetor[com1];
        comAux++;
        com1++;
    }

    while(com2 <= fim) {
        vetAux[comAux] = vetor[com2];
        comAux++;
        com2++;
    }

    for(comAux = comeco; comAux <= fim; comAux++){
        vetor[comAux] = vetAux[comAux-comeco];
    }

    delete []vetAux;
}

void mergeSort(int* vetor, int inicio, int fim ){
    if( inicio == fim ) return;

    int meio = (inicio+fim) / 2;
    mergeSort( vetor, inicio, meio );
    mergeSort( vetor, meio+1, fim );
    combinar(vetor, inicio, meio, fim );
}

// Realiza o algortimo com o ID fornecido e retorna o tempo delta para realizar a ordenação
double ordenar(int algoritmoOrdenacao, int* vetor, int tam){
    int* tempVetor = new int[tam]; // Vetor temporario p/ armazenar o estado original pre-odernação

    for (int i = 0; i < tam; i++){
        tempVetor[i] = vetor[i];
    }

    auto comecoTimer = chrono::high_resolution_clock::now();
    switch (algoritmoOrdenacao) {
        default:
            cout << "ALGORITMO DE ORDENACAO COM ID: " << algoritmoOrdenacao << " NAO IMPLEMENTADO" << endl;
            break;

        case 0: { // Insertion
            insercaoDireta(vetor, tam);
            break;
        }

        case 1: { // Bubble Sort
            bubbleSort(vetor, tam);
            break;
        }

        case 2: { // Selection Sort
            selecao(vetor, tam);
            break;
        }

        case 3: { // Merge Sort
            mergeSort(vetor, 0, tam-1);
            break;
        }
    }
    auto fimTimer = chrono::high_resolution_clock::now();

    for (int i = 0; i < tam; i++){ // Restauração do vetor p/ estado original
        vetor[i] = tempVetor[i];
    }

    delete[] tempVetor; // Remoção do vetor temporário da memória

    // Retorno do tempo delta em milisegundos
    return chrono::duration_cast<chrono::milliseconds>(fimTimer - comecoTimer).count();
}

int main() {
    // Quantidade de arrays (melhor/pior caso nao inclusos)
    int M = 0;
    // Tamanho dos arrays
    int N = 0;
    // Vezes que cada array deve ser submetido aos algoritmos
    int X = 0;

    do {
        cout << "Forneca a quantidade de arrays aleatorios (MIN: 1)" << endl;
        cin >> M;

        if (M <= 0){
            cout << "Valor invalido, tente novamente\n" << endl;
        }
    } while (M <= 0);

    do {
        cout << "Forneca o tamanho dos arrays (MIN: 2)" << endl;
        cin >> N;

        if (N <= 1){
            cout << "Tamanho invalido invalido, tente novamente\n" << endl;
        }
    } while (N <= 1);

    do {
        cout << "Quantas vezes os arrays devem ser submetidos a cada algoritmo de ordenacao? (MIN: 1)" << endl;
        cin >> X;

        if (X <= 0){
            cout << "Valor invalido, tente novamente\n" << endl;
        }
    } while (X <= 0);

    auto tempoTotalInicio = chrono::high_resolution_clock::now();

    M += 2; // Quantidade de arrays += 2 (melhor e pior caso)
    int** arrays = new int* [M];

    for (int i = 0; i < M; i++){ // Alocação dinamica dos arrays
        arrays[i] = new int[N];
        bool ordenado = false;

        if (i == 0) {
            crescente(arrays[i], N); // arrays[0] = melhor caso
            ordenado = true;
        }

        if (i == M-1){
            decrescente(arrays[i], N); // arrays[ultimo index] = pior caso
            ordenado = true;
        }

        if (!ordenado){
            aleatorizar(arrays[i], N, N); // arrays[entre melhor e pior] = caso médio
        }
    }

    // Alocação de um vetor tridimensional p/ armazenamento dos resultados
    // 1 = Algoritmo
    // 2 = Array
    // 3 = Resultado da tentativa n° Z com o array Y
    auto ***timings = new double** [4]; // 1

    for (int i = 0; i < 4; i++){
        timings[i] = new double*[M]; // 2

        for (int j = 0; j < M; j++){
            timings[i][j] = new double[X]; // 3
        }
    }

    // Alocacao de um vetor bidimensional p/ o armazenamento dos vetores com tempo recorde de melhor/pior
    // 1 = Algoritmo
    // 2 = 0 - melhor caso / 1 - pior caso
    auto ***recordes = new recorde** [4]; // 1

    for (int i = 0; i < 4; i++){
        recordes[i] = new recorde *[2]; // 2

        for (int j = 0; j < 2; j++){
            recordes[i][j] = new recorde; // 3
        }
    }



    // Armazena o numero de elementos correspondentes a N * 4, utilizado para display de progresso
    float totalOperacoes = 4.0f * M;
    int operacoesRealizadas = 0;
    float porcentagemOperacao = 0;

    // Operação de ordenação p/ cada caso possível
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < X; k++) {
                // Ordenação e armazenamento do tempo delta no algoritmo X no array J na K° tentativa
                timings[i][j][k] = ordenar(i, arrays[j], N);
            }

            // Média aritmética p/ verificar com valor recorde
            double somaTimingsVetor = 0;
            for (int k = 0; k < X; k++) {
                somaTimingsVetor += timings[i][j][k];
            }
            float mediaTimingsVetor = somaTimingsVetor/X;

            if (j == 0){ // Primeiro vetor do algoritmo, armazenar timing p/ ser base inicial
                recordes[i][0]->tempo = mediaTimingsVetor; // Melhor caso base
                recordes[i][0]->vetor = arrays[j];
                recordes[i][1]->tempo = mediaTimingsVetor; // Pior caso base
                recordes[i][1]->vetor = arrays[j];
            } else {
                if (recordes[i][0]->tempo > mediaTimingsVetor){ // Novo melhor caso
                    recordes[i][0]->tempo = mediaTimingsVetor;
                    recordes[i][0]->vetor = arrays[j];
                }

                if (recordes[i][1]->tempo < mediaTimingsVetor){ // Novo pior caso
                    recordes[i][1]->tempo = mediaTimingsVetor;
                    recordes[i][1]->vetor = arrays[j];
                }
            }

            // Calculo da porcentagem de conclusão
            operacoesRealizadas += 1;
            porcentagemOperacao = (operacoesRealizadas/totalOperacoes) * 100;
            system("cls");
            cout << "Ordenacao em progresso.. | PROGRESSO TOTAL: " << porcentagemOperacao << "%" << endl;
        }
    }

    // Alocação de vetor bidimensional contendo a média aritmetica dos resultados
    // 1 - Algoritmo
    // 2 - Resultado de caso (0 (melhor) - 2 (pior))
    auto** resultados = new double* [4];
    for (int i = 0; i < 4; i++) { // Para cada algoritmo
        resultados[i] = new double[3]; // há 3 possibilidades de casos
        for (int j = 0; j < 3; j++){
            resultados[i][j] = 0; // todos começam com zero
        }
    }

    // Compressão dos resultados para os 3 casos
    for (int i = 0; i < 4; i++) { // Para cada algoritmo
        int dividendoCasoMedio = 0;

        for (int j = 0; j < M; j++) { // Para cada array
            for (int k = 0; k < X; k++) { // Para cada tentativa em array j

                // Condição ternária do caso alvo:
                // 0 = melhor caso (primeiro array)
                // 2 = pior caso (ultimo array)
                // 1 = caso médio (todos os arrays restantes)
                int casoAlvo = (j == 0) ? 0 : (j == M-1) ? 2 : 1;

                if (casoAlvo == 1){
                    // Incremento do total de elementos no caso médio p/ calculo da média no final
                    dividendoCasoMedio++;
                }

                // No algoritmo i no caso alvo (0 até 2), o resultado do timing no algoritmo i, no array j, na tentativa k é armazenado
                resultados[i][casoAlvo] += timings[i][j][k];

                //cout << "Algoritmo " << i << " | Array: " << j << " | Tentativa " << k+1 << ": " << timings[i][j][k] << "ms" << endl;
            }
        }

        // Média aritmética da soma dos timings com o numero de elementos
        resultados[i][0] = resultados[i][0]/X; // melhor caso
        resultados[i][1] = resultados[i][1]/dividendoCasoMedio; // caso médio
        resultados[i][2] = resultados[i][2]/X; // pior caso
    }

    // Desalocação do array tridimensional, não é mais necessário
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < M; j++){
            delete[] timings[i][j];
        }
        delete[] timings[i];
    }

    auto tempoTotalFim = chrono::high_resolution_clock::now();
    auto tempoTotalDelta = chrono::duration_cast<chrono::minutes>(tempoTotalFim - tempoTotalInicio).count();
    system("cls");
    cout << "ESTATISTICAS DE ORDENACAO GERADAS APOS " << tempoTotalDelta << " MINUTOS" << endl;
    cout << "--------------------\n";
    cout << "Dados fornecidos pelo usuario:" << endl;
    cout << "Quantidade de arrays aleatorios: " << M-2 << endl;
    cout << "Tamanho dos arrays: " << N << endl;
    cout << "Vezes que cada array deve ser submetido aos algoritmos: " << X << endl;
    cout << "--------------------\n";
    cout << "RESULTADOS FINAIS:" << endl;

    for (int i = 0; i < 4; i++){
        cout << "--------------------\n";
        switch (i) {
            case 0:
                cout << "Insertion Sort:" << endl;
                break;
            case 1:
                cout << "Bubble Sort:" << endl;
                break;
            case 2:
                cout << "Selection Sort:" << endl;
                break;
            case 3:
                cout << "Merge Sort:" << endl;
                break;
        }

        for (int j = 0; j < 3; j++){
            switch (j){
                case 0:
                    cout << "Melhor caso: ";
                    break;
                case 1:
                    cout << "Caso medio: ";
                    break;
                case 2:
                    cout << "Pior caso: ";
                    break;
            }
            cout << resultados[i][j] << "ms" << endl;
        }

        for (int j = 0; j < 2; j++){
            cout << "Tempo do ";
            switch (j){
                case 0:
                    cout << "melhor vetor: ";
                    break;
                case 1:
                    cout << "pior vetor: ";
                    break;
            }
            cout << recordes[i][j]->tempo << "ms" << endl;
        }
    }
    return 0;
}
