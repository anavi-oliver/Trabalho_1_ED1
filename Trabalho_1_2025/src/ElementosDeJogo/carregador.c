#include "carregador.h"
#include <stdio.h>
#include <stdlib.h>

struct Carregador_t {
    int id;
    Stack pilhaDeFormas; // carregador = pilha de formas
};


/*________________________________ FUNÇÕES DE CRIAÇÃO E DESTRUIÇÃO ________________________________*/

Carregador criaCarregador(int id) {
    struct Carregador_t *c = malloc(sizeof(struct Carregador_t));
    if (c == NULL) {
        printf("ERRO: Falha ao alocar memoria para o Carregador.\n");
        return NULL;
    }

    c->pilhaDeFormas = createStk();
    if (c->pilhaDeFormas == NULL) {
        printf("ERRO: Falha ao criar a pilha interna do Carregador.\n");
        free(c);
        return NULL;
    }

    c->id = id;
        
    return (Carregador)c;
}

void destroiCarregador(Carregador c) {
    if (c == NULL) {
        return;
    }

    struct Carregador_t *carr = (struct Carregador_t *)c;

    // Libera a pilha (mas não as formas)
    destroiPilha(carr->pilhaDeFormas);

    free(carr);
}


/*________________________________ FUNÇÕES DE MANIPULAÇÃO ________________________________*/

void carregaFormasDoChao(Carregador carregadorAlvo, Chao chaoOrigem, int n) {
    if (carregadorAlvo == NULL || chaoOrigem == NULL) {
        printf("AVISO: Carregador ou Chao nulo passado para carregaFormasDoChao.\n");
        return;
    }

    if (n <= 0) {
        return; //faz nada
    }

    struct Carregador_t *carr = (struct Carregador_t *)carregadorAlvo;

    //loop para transferir 'n' formas
    for (int i = 0; i < n; i++) {
        // Verifica se o chão ainda tem formas
        if (chaoEstaVazio(chaoOrigem)) {
            //se chao = vazio, apenas para de carregar
            break;
        }

        //tira forma do chao
        Forma formaMovida = removeFormaChao(chaoOrigem);

        //insere a forma removida no carregador (empilha)
        if (formaMovida != NULL) {
            empilha(carr->pilhaDeFormas, formaMovida);
        }
    }//loop pra transferir n
}

Queue carregaFormasDoChaoComRastreio(Carregador carregadorAlvo, Chao chaoOrigem, int n) {
    //cria fila para rastrear formas carregadas
    Queue filaRastreio = createQueue();
    
    if (filaRastreio == NULL) {
        printf("ERRO: Falha ao criar fila de rastreio.\n");
        return NULL;
    }

    if (carregadorAlvo == NULL || chaoOrigem == NULL) {
        printf("AVISO: Carregador ou Chao nulo passado para carregaFormasDoChaoComRastreio.\n");
        return filaRastreio; 
    }

    if (n <= 0) {
        return filaRastreio; 
    }

    struct Carregador_t *carr = (struct Carregador_t *)carregadorAlvo;

    for (int i = 0; i < n; i++) {
        //verifica se o chão ainda tem formas
        if (chaoEstaVazio(chaoOrigem)) {
            break; //chão vazio, para de carregar
        }

        //tira forma do chão
        Forma formaMovida = removeFormaChao(chaoOrigem);

        if (formaMovida != NULL) {
            empilha(carr->pilhaDeFormas, formaMovida);
            enfileira(filaRastreio, formaMovida); // registra na fila
        }
    }

    return filaRastreio;
}

Forma descarregaForma(Carregador c) {
    if (c == NULL) {
        return NULL;
    }

    struct Carregador_t *carr = (struct Carregador_t *)c;

    if (estaVaziaPilha(carr->pilhaDeFormas)) {
        return NULL;
    }

    return desempilha(carr->pilhaDeFormas);
}

void insereFormaCarregador(Carregador c, Forma f) {
    if (c == NULL || f == NULL) {
        return;
    }

    struct Carregador_t *carr = (struct Carregador_t *)c;
    empilha(carr->pilhaDeFormas, f);
}


/*________________________________ FUNÇÕES GET ________________________________*/

int getCarregadorId(const Carregador c) {
    if (c == NULL) {
        return -1; //retorna um ID inválido em caso de erro
    }

    struct Carregador_t *carr = (struct Carregador_t *)c;
    return carr->id;
}

int getCarregadorTamanho(const Carregador c) {
    if (c == NULL) {
        return 0;
    }

    struct Carregador_t *carr = (struct Carregador_t *)c;
    return getTamanhoPilha(carr->pilhaDeFormas);
}

bool carregadorEstaVazio(const Carregador c) {
    if (c == NULL) {
        return true; 
    }

    struct Carregador_t *carr = (struct Carregador_t *)c;
    return estaVaziaPilha(carr->pilhaDeFormas);
}