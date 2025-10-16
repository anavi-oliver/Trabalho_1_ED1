#include "carregador.h"
#include <stdio.h>
#include <stdlib.h>


struct Carregador_t {
    int id;
    Queue filaDeFormas; // carregador = fila
};


/*________________________________ FUNÇÕES DE CRIAÇÃO E DESTRUIÇÃO ________________________________*/

Carregador criaCarregador(int id){

    Carregador c = malloc(sizeof(struct Carregador_t));
    if (c == NULL) {
        printf("ERRO: Falha ao alocar memoria para o Carregador.\n");
        return NULL;
    }

    // Inicializa a fila do carregador
    c->filaDeFormas = createQueue();
    if (c->filaDeFormas == NULL) {

        printf("ERRO: Falha ao criar a fila interna do Carregador.\n");
        free(c);
        return NULL;
    }

    c->id = id;
    return c;
}

void destroiCarregador(Carregador c){
    if (c == NULL) {
        return;
    }

    destroiFila(c->filaDeFormas);

    free(c);
}


/*________________________________ FUNÇÕES DE MANIPULAÇÃO ________________________________*/

void carregaFormasDoChao(Carregador carregadorAlvo, Chao chaoOrigem, int n){

    if (carregadorAlvo == NULL || chaoOrigem == NULL) {
        printf("AVISO: Carregador ou Chao nulo passado para carregaFormasDoChao.\n");
        return;
    }

    if (n <= 0) {
        return; //faz nada
    }

    //loop para transferir 'n' formas
    for (int i = 0; i < n; i++) {
        // Verifica se o chão ainda tem formas
        if (chaoEstaVazio(chaoOrigem)) {
            //se chao = vazio, apenas para de carregar
            break;
        }

        //tira forma do chao
        Forma formaMovida = removeFormaChao(chaoOrigem);

        //insere a forma removida no carregador
        if (formaMovida != NULL) {
            enfileira(carregadorAlvo->filaDeFormas, formaMovida);
        }
    }//loop pra transferir n
} //carregaFormas

Forma descarregaForma(Carregador c) {
    if (carregadorEstaVazio(c)) {
        return NULL;
    }
    return desenfileira(c->filaDeFormas);
}


/*________________________________ FUNÇÕES GET ________________________________*/

int getCarregadorId(const Carregador c) {
    if (c == NULL) {
        return -1; //retorna um ID inválido em caso de erro
    }
    return c->id;
}

int getCarregadorTamanho(const Carregador c) {
    if (c == NULL) {
        return 0;
    }
    // Delega a contagem para a função da TAD Fila
    return getTamanhoFila(c->filaDeFormas);
}

bool carregadorEstaVazio(const Carregador c) {
    if (c == NULL) {
        return true; // Um carregador nulo é considerado vazio
    }
    // Delega a verificação para a função da TAD Fila
    return estaVaziaFila(c->filaDeFormas);
}

void insereFormaCarregador(Carregador c, Forma f) {
    if (c == NULL || f == NULL) {
        return;
    }
    enfileira(c->filaDeFormas, f);
}