#include "chao.h"      

#include "fila.h"    
#include "formas.h"

#include <stdio.h>    
#include <stdlib.h>
#include <stdbool.h>

struct Chao_t {
    Queue fila_de_formas;
};


/*________________________________ FUNÇÕES DE CRIAÇÃO E DESTRUIÇÃO ________________________________*/

Chao criaChao() {
    Chao c = (Chao) malloc(sizeof(struct Chao_t));
    if (c == NULL) {
        printf("\nERRO: Falha ao alocar memória para o Chão.\n");
        return NULL;
    }

    c->fila_de_formas = createQueue();
    if (c->fila_de_formas == NULL) {
        printf("\nERRO: Falha ao criar a fila interna do Chão.\n");
        free(c);
        return NULL;
    }

    return c;
}

void destroiChao(Chao c) {
    if (c == NULL) {
        return;
    }


    while (!chaoEstaVazio(c)) {
        Forma f = removeFormaChao(c);
        destroiForma(f);
    }

    destroiFila(c->fila_de_formas);

    free(c);
}


/*________________________________ FUNÇÕES DE MANIPULAÇÃO ________________________________*/

void adicionaFormaChao(Chao c, Forma f) {
    if (c == NULL || f == NULL) {
        return;
    }

    // Adicionar uma forma no chão é simplesmente enfileirar na nossa fila interna.
    enfileira(c->fila_de_formas, f);
}

Forma removeFormaChao(Chao c) {
    if (c == NULL || chaoEstaVazio(c)) {
        return NULL;
    }

    // Remover uma forma do chão é simplesmente desenfileirar da nossa fila interna.
    return (Forma) desenfileira(c->fila_de_formas);
}


/*________________________________ FUNÇÕES DE CONSULTA ________________________________*/

bool chaoEstaVazio(const Chao c) {
    if (c == NULL) {
        return true; // Um chão que não existe pode ser considerado vazio.
    }
    return estaVaziaFila(c->fila_de_formas);
}

int getChaoTamanho(const Chao c) {
    if (c == NULL) {
        return 0;
    }
    
    return getTamanhoFila(c->fila_de_formas);
}