#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

// nó interno da pilha
typedef struct aux {
    Item item;
    struct aux *prox;
} AUX;

// estrutura da pilha
typedef struct stack {
    AUX *top;    
    int size;    // NOVO: contador de elementos
} pilhaC;

// cria uma pilha vazia
Stack createStk() {
    pilhaC *p = (pilhaC*) malloc(sizeof(pilhaC));
    if (p == NULL) {
        printf("Erro: falha na alocação de memória.\n");
        exit(1);
    }
    p->top = NULL;
    p->size = 0;
    return (Stack) p;
}

// insere no topo
void empilha(Stack p, Item i) {
    pilhaC *pilha = (pilhaC*) p;
    AUX *novo = (AUX*) malloc(sizeof(AUX));
    if (novo == NULL) {
        printf("Erro: falha na alocação de memória.\n");
        exit(1);
    }
    novo->item = i;
    novo->prox = pilha->top;  
    pilha->top = novo;        
    pilha->size++;  // ATUALIZA contador
}

// remove o elemento do topo e retorna
Item desempilha(Stack p) {
    pilhaC *pilha = (pilhaC*) p;
    if (pilha->size == 0) {
        return NULL;  
    }
    AUX *temp = pilha->top;
    Item info = temp->item;
    pilha->top = pilha->top->prox;  
    free(temp);
    pilha->size--;  // ATUALIZA contador
    return info;
}

// retorna o elemento do topo sem remover
Item topoPilha(Stack p) {
    pilhaC *pilha = (pilhaC*) p;
    if (pilha->top == NULL) {
        return NULL;
    }
    return pilha->top->item;
}

// verifica se a pilha está vazia
bool estaVaziaPilha(Stack p) {
    pilhaC *pilha = (pilhaC*) p;
    return (pilha->size == 0);
}

int getTamanhoPilha(Stack p) {
    if (p == NULL) {
        return 0;
    }
    pilhaC *pilha = (pilhaC*) p;
    return pilha->size;
}

// libera toda a pilha
void destroiPilha(Stack p) {
    pilhaC *pilha = (pilhaC*) p;
    AUX *atual = pilha->top;
    while (atual != NULL) {
        AUX *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(pilha);
}