#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

// nó interno da fila
typedef struct aux {
    Item item;
    struct aux *prox;
} AUX;

// estrutura da fila
typedef struct queue {
    AUX *first;
    AUX *last;
    int size;
} filaC;

// cria uma fila vazia
Queue createQueue() {
    filaC *f = (filaC*) malloc(sizeof(filaC));
    if (f == NULL) {
        printf("Erro: falha na alocação de memória.\n");
        exit(1);
    }
    f->first = NULL;
    f->last = NULL;
    f->size = 0;
    return (Queue) f;
}

// insere no final
void enfileira(Queue q, Item i) {
    filaC *f = (filaC*) q;
    AUX *novo = (AUX*) malloc(sizeof(AUX));
    if (novo == NULL) {
        printf("Erro: falha na alocação de memória.\n");
        exit(1);
    }
    novo->item = i;
    novo->prox = NULL;
    
    if (f->size == 0) {
        f->first = novo;
        f->last = novo;
    } else {
        f->last->prox = novo;
        f->last = novo;
    }
    f->size++;
}

// remove o primeiro elemento e retorna
Item desenfileira(Queue q) {
    filaC *f = (filaC*) q;
    if (f->size == 0) {
        return NULL;
    }
    AUX *temp = f->first;
    Item info = temp->item;
    f->first = f->first->prox;
    if (f->first == NULL) {
        f->last = NULL;
    }
    free(temp);
    f->size--;
    return info;
}

// retorna o primeiro elemento sem remover
Item inicioFila(const Queue q) {
    filaC *f = (filaC*) q;
    if (f->first == NULL) {
        return NULL;
    }
    return f->first->item;
}

// retorna o último elemento sem remover
Item fimFila(const Queue q) {
    filaC *f = (filaC*) q;
    if (f->last == NULL) {
        return NULL;
    }
    return f->last->item;
}

// verifica se a fila está vazia
bool estaVaziaFila(const Queue q) {
    filaC *f = (filaC*) q;
    return (f->size == 0);
}

// NOVA FUNÇÃO ADICIONADA
// retorna o número de elementos na fila
int getTamanhoFila(const Queue q) {
    filaC *f = (filaC*) q;
    if (f == NULL) {
        return 0;
    }
    return f->size;
}

// libera toda a fila
void destroiFila(Queue q) {
    if (q == NULL) {
        return;
    }
    filaC *f = (filaC*) q;
    AUX *atual = f->first;
    while (atual != NULL) {
        AUX *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(f);
}