#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "chao.h"
#include "fila.h" 

/*_______________________ ESTRUTURA INTERNA DO TAD CHÃO _______________________*/
/*
* A estrutura opaca Chao_t é revelada aqui, no arquivo .c.
* Como planejado, ela é um invólucro simples que contém um único
* ponteiro para a nossa Fila genérica. Toda a lógica de "Chão" será
* traduzida para operações de Fila.
*/
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

    // Cria a fila interna que irá armazenar as formas
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

    // PONTO CRÍTICO: Como o 'destroiFila' não libera os elementos,
    // é preciso fazer isso manualmente.Enquanto o chão (fila) não estiver vazio...
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

    enfileira(c->fila_de_formas, f);
}

Forma removeFormaChao(Chao c) {
    if (c == NULL || chaoEstaVazio(c)) {
        return NULL;
    }
    return (Forma) desenfileira(c->fila_de_formas);
}


/*________________________________ FUNÇÕES DE CONSULTA ________________________________*/

bool chaoEstaVazio(const Chao c) {
    if (c == NULL) {
        return true; // um chão que não existe pode ser considerado vazio.
    }

    return estaVaziaFila(c->fila_de_formas);
}

int getChaoTamanho(const Chao c) {
    if (c == NULL) {
        return 0;
    }
    
    // ATENÇÃO: A sua interface 'fila.h' não possui uma função para
    // retornar o tamanho. Para que esta função funcione corretamente,
    // você precisará adicionar uma função 'getTamanhoFila(Queue q)'
    // ao seu módulo de Fila.
    //
    // Por enquanto, esta é uma implementação de placeholder.
    // return getTamanhoFila(c->fila_de_formas);

    printf("AVISO: A função getChaoTamanho() requer uma função getTamanhoFila() em fila.h/fila.c\n");
    return -1; // Retornando -1 para indicar que a função não está implementada.
}