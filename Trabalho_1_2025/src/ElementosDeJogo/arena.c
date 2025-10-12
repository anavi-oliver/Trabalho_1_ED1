#include "arena.h"
#include <stdio.h>
#include <stdlib.h>

struct Arena_t {
    double largura;
    double altura;
    Queue filaDeFormas; 
};


/*________________________________ FUNÇÕES DE CRIAÇÃO E DESTRUIÇÃO ________________________________*/

Arena criaArena(double largura, double altura) {
    //aloca memória para a estrutura principal da Arena
    Arena a = malloc(sizeof(struct Arena_t));
    if (a == NULL) {
        printf("ERRO: Falha ao alocar memoria para a Arena.\n");
        return NULL;
    }

    //inicializa a fila interna que contera as formas
    a->filaDeFormas = createQueue();
    if (a->filaDeFormas == NULL) {
        printf("ERRO: Falha ao criar a fila interna da Arena.\n");
        free(a); //libera a memória da arena já alocada
        return NULL;
    }

    //define as dimensões da arena
    a->largura = largura;
    a->altura = altura;

    return a;
}

void destroiArena(Arena a) {
    if (a == NULL) {
        return;
    }

    //obs: aena é "dona" das formas.
    //antes de destruir a fila, precisamos destruir cada forma dentro dela.
    while (!estaVaziaFila(a->filaDeFormas)) {
        Forma f = desenfileira(a->filaDeFormas);
        destroiForma(f); 
    }

    //agora que a fila está vazia, destroi a estrutura da fila.
    destroiFila(a->filaDeFormas);

    //liberar a memória da própria estrutura da Arena.
    free(a);
}


/*________________________________ FUNÇÕES DE MANIPULAÇÃO DE FORMAS ________________________________*/

void insereFormaArena(Arena a, Forma f) {
    if (a == NULL || f == NULL) {
        return;
    }
    enfileira(a->filaDeFormas, f);
}

void iteraFormasArena(const Arena a, void (*executa)(Forma f, void *auxData), void *auxData) {
    if (a == NULL || executa == NULL) {
        return;
    }

    int tamanhoOriginal = getTamanhoFila(a->filaDeFormas);
    if (tamanhoOriginal == 0) {
        return;
    }

    //obs: loop processa cada elemento da fila uma vez, sem destruir
    //ele retira um elemento do início, executa a função e o coloca de volta no fim.
    for (int i = 0; i < tamanhoOriginal; i++) {
        Forma f = desenfileira(a->filaDeFormas);

        //executa a função fornecida pelo usuário para a forma atual
        executa(f, auxData);

        //coloca a forma de volta na fila
        enfileira(a->filaDeFormas, f);
    }
}


/*___________________________ FUNÇÕES DE CONSULTA E MODIFICAÇÃO DE ATRIBUTOS ___________________________*/

double getArenaLargura(const Arena a) {
    if (a == NULL) {
        return -1.0; //= erro
    }
    return a->largura;
}

double getArenaAltura(const Arena a) {
    if (a == NULL) {
        return -1.0; //= erro
    }
    return a->altura;
}

void setArenaLargura(Arena a, double novaLargura) {
    if (a != NULL) {
        a->largura = novaLargura;
    }
}

void setArenaAltura(Arena a, double novaAltura) {
    if (a != NULL) {
        a->altura = novaAltura;
    }
}

int getArenaNumFormas(const Arena a) {
    if (a == NULL) {
        return 0;
    }
    // contagem para a fila (TAD)
    return getTamanhoFila(a->filaDeFormas);
}