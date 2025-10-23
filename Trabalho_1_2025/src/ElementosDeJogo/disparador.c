#include "disparador.h"
#include <stdio.h>
#include <stdlib.h>

// #define DEBUG_MODE //descomente para ativar modo de debug

#ifdef DEBUG_MODE
    #define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
    #define DEBUG_PRINT(...) // Não faz nada quando debug está desativado
#endif

/*_______________________ ESTRUTURA INTERNA DO DISPARADOR _______________________*/
struct Disparador_t {
    int id;
    double x;
    double y;
    Carregador carregadorEsq;
    Carregador carregadorDir;
    Forma formaPronta;
};


/*________________________________ FUNÇÕES DE CRIAÇÃO E DESTRUIÇÃO ________________________________*/

Disparador criaDisparador(int id, double x, double y, Carregador esq, Carregador dir) {
    // Permite criar disparador sem carregadores (conectados depois com 'atch')
    struct Disparador_t *d = malloc(sizeof(struct Disparador_t));
    if (d == NULL) {
        printf("ERRO: Falha ao alocar memoria para o Disparador.\n");
        return NULL;
    }

    // Inicializa os atributos
    d->id = id;
    d->x = x;
    d->y = y;
    d->carregadorEsq = esq;  // Pode ser NULL inicialmente
    d->carregadorDir = dir;  // Pode ser NULL inicialmente
    d->formaPronta = NULL;

    DEBUG_PRINT("Disparador %d criado com sucesso!\n", d->id);

    return (Disparador)d;
}

void destroiDisparador(Disparador d) {
    if (d == NULL) {
        return;
    }

    struct Disparador_t *disp = (struct Disparador_t *)d;

    // Se houver uma forma na posição de disparo, libera
    if (disp->formaPronta != NULL) {
        DEBUG_PRINT("AVISO: Disparador %d tinha forma ID=%d em posicao de disparo nao utilizada\n",
                   disp->id, getFormaId(disp->formaPronta));
        destroiForma(disp->formaPronta);
    }

    free(disp);
}


/*________________________________ FUNÇÕES DE CONSULTA (GETTERS) ________________________________*/

int getDisparadorId(const Disparador d) {
    if (d == NULL) {
        return -1;
    }
    struct Disparador_t *disp = (struct Disparador_t *)d;
    return disp->id;
}

double getDisparadorX(const Disparador d) {
    if (d == NULL) {
        return 0.0;
    }
    struct Disparador_t *disp = (struct Disparador_t *)d;
    return disp->x;
}

double getDisparadorY(const Disparador d) {
    if (d == NULL) {
        return 0.0;
    }
    struct Disparador_t *disp = (struct Disparador_t *)d;
    return disp->y;
}

Forma getDisparadorFormaPronta(const Disparador d) {
    if (d == NULL) {
        return NULL;
    }
    struct Disparador_t *disp = (struct Disparador_t *)d;
    return disp->formaPronta;
}


/*________________________________ FUNÇÕES DE MODIFICAÇÃO (SETTERS) ________________________________*/

void setDisparadorPosicao(Disparador d, double x, double y) {
    if (d == NULL) {
        printf("AVISO: Disparador nulo passado para setDisparadorPosicao.\n");
        return;
    }
    struct Disparador_t *disp = (struct Disparador_t *)d;
    disp->x = x;
    disp->y = y;
}


/*________________________________ FUNÇÕES AUXILIARES ADICIONAIS ________________________________*/

void reconectaCarregadores(Disparador d, Carregador esq, Carregador dir) {
    if (d == NULL) {
        printf("ERRO: Disparador NULL passado para reconectaCarregadores.\n");
        return;
    }

    if (esq == NULL || dir == NULL) {
        printf("ERRO: Carregador NULL passado para reconectaCarregadores.\n");
        return;
    }

    struct Disparador_t *disp = (struct Disparador_t *)d;

    DEBUG_PRINT("DEBUG ATTACH: Disparador %d reconectado: esq=%d, dir=%d\n",
                disp->id, getCarregadorId(esq), getCarregadorId(dir));

    disp->carregadorEsq = esq;
    disp->carregadorDir = dir;
}


/*_______________________________________ AÇÕES PRINCIPAIS _______________________________________*/

void preparaDisparo(Disparador d, char lado, int n) {
    if (d == NULL) {
        return;
    }

    struct Disparador_t *disp = (struct Disparador_t *)d;

    // Valida carregadores
    if (disp->carregadorEsq == NULL || disp->carregadorDir == NULL) {
        printf("ERRO: Disparador %d não possui carregadores conectados.\n", disp->id);
        return;
    }

    // Valida o parâmetro 'lado'
    if (lado != 'E' && lado != 'D' && lado != 'e' && lado != 'd') {
        printf("AVISO: Lado invalido '%c' passado para preparaDisparo. Use 'E' ou 'D'.\n", lado);
        return;
    }

    if (n <= 0) {
        return;
    }

    // Normaliza para maiúsculas
    char ladoNormalizado = (lado == 'e') ? 'E' : (lado == 'd') ? 'D' : lado;

    DEBUG_PRINT("DEBUG PREP: Ordem de preparo - Lado: %c, n=%d\n", ladoNormalizado, n);

    // ========== CORREÇÃO CRÍTICA: Lógica de seleção de carregadores ==========
    // 'D' (direito) → pega do carregador ESQUERDO
    // 'E' (esquerdo) → pega do carregador DIREITO
    Carregador carregadorOrigem = (ladoNormalizado == 'D') ? disp->carregadorEsq : disp->carregadorDir;
    Carregador carregadorOposto = (ladoNormalizado == 'D') ? disp->carregadorDir : disp->carregadorEsq;

    // Repete a operação 'n' vezes para "ciclar" as formas
    for (int i = 0; i < n; i++) {
        DEBUG_PRINT("DEBUG PREP: Iteracao %d - Forma atual em disparo: %p\n", 
                   i, (void*)disp->formaPronta);

        // Se já há uma forma pronta, move ela para o carregador oposto
        if (disp->formaPronta != NULL) {
            DEBUG_PRINT("DEBUG PREP: Movendo forma ID=%d do disparo para carregador oposto\n",
                       getFormaId(disp->formaPronta));
            
            insereFormaCarregador(carregadorOposto, disp->formaPronta);
            disp->formaPronta = NULL;
        }

        // Verifica se o carregador de origem tem formas
        if (carregadorEstaVazio(carregadorOrigem)) {
            DEBUG_PRINT("DEBUG PREP: Carregador de origem vazio. Nenhuma forma movida para disparo.\n");
            break;
        }

        // Pega a próxima forma do carregador de origem
        disp->formaPronta = descarregaForma(carregadorOrigem);
        
        if (disp->formaPronta != NULL) {
            DEBUG_PRINT("DEBUG PREP: Forma ID=%d colocada em posicao de disparo\n",
                       getFormaId(disp->formaPronta));
        }
    }
}

Forma dispara(Disparador d, double dx, double dy) {
    if (d == NULL) {
        printf("ERRO: Disparador inexistente passado para dispara.\n");
        return NULL;
    }

    struct Disparador_t *disp = (struct Disparador_t *)d;

    DEBUG_PRINT("DEBUG DISP: Tentando disparar. formaPronta=%p\n", (void*)disp->formaPronta);
    
    if (disp->formaPronta != NULL) {
        DEBUG_PRINT("DEBUG DISP: Forma ID=%d esta em posicao de disparo\n", 
                   getFormaId(disp->formaPronta));
    }

    // Verifica se há uma forma pronta para disparo
    if (disp->formaPronta == NULL) {
        printf("AVISO: Nenhuma forma esta na posicao de disparo.\n");
        return NULL;
    }

    // Pega a forma que será disparada
    Forma formaDisparada = disp->formaPronta;
    disp->formaPronta = NULL;

    // Calcula a posição final da forma
    double posX_final = disp->x + dx;
    double posY_final = disp->y + dy;

    // Atualiza a posição da forma
    setFormaPosicao(formaDisparada, posX_final, posY_final);

    DEBUG_PRINT("DEBUG DISP: Forma ID=%d disparada para (%.2f, %.2f)\n",
               getFormaId(formaDisparada), posX_final, posY_final);

    return formaDisparada;
}