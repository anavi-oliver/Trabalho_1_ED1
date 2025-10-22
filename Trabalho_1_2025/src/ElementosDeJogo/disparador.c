#include "disparador.h"
#include <stdio.h>
#include <stdlib.h>

// #define DEBUG_MODE //apaga ou comenta pra desativar modo de debug

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
    // Pré-condição: Carregadores devem ser válidos
    if (esq == NULL || dir == NULL) {
        printf("ERRO: Carregadores invalidos passados para criaDisparador.\n");
        return NULL;
    }

    // Aloca memória para a estrutura do Disparador
    Disparador d = malloc(sizeof(struct Disparador_t));
    if (d == NULL) {
        printf("ERRO: Falha ao alocar memoria para o Disparador.\n");
        return NULL;
    }

    // Inicializa os atributos
    d->id = id;
    d->x = x;
    d->y = y;
    d->carregadorEsq = esq;
    d->carregadorDir = dir;
    d->formaPronta = NULL;

    DEBUG_PRINT("Disparador %d criado com sucesso!\n", d->id);

    return d;
}

void destroiDisparador(Disparador d) {
    if (d == NULL) {
        return;
    }

    // Se houver uma forma na posição de disparo, avisa e libera
    if (d->formaPronta != NULL) {
        DEBUG_PRINT("AVISO: Disparador %d tinha forma ID=%d em posicao de disparo nao utilizada\n",
                   d->id, getFormaId(d->formaPronta));
        destroiForma(d->formaPronta);
    }

    free(d);
}


/*________________________________ FUNÇÕES DE CONSULTA (GETTERS) ________________________________*/

int getDisparadorId(const Disparador d) {
    if (d == NULL) {
        return -1;
    }
    return d->id;
}

double getDisparadorX(const Disparador d) {
    if (d == NULL) {
        return 0.0;
    }
    return d->x;
}

double getDisparadorY(const Disparador d) {
    if (d == NULL) {
        return 0.0;
    }
    return d->y;
}

Forma getDisparadorFormaPronta(const Disparador d) {
    if (d == NULL) {
        return NULL;
    }
    return d->formaPronta;
}


/*________________________________ FUNÇÕES DE MODIFICAÇÃO (SETTERS) ________________________________*/

void setDisparadorPosicao(Disparador d, double x, double y) {
    if (d == NULL) {
        printf("AVISO: Disparador nulo passado para setDisparadorPosicao.\n");
        return;
    }
    d->x = x;
    d->y = y;
}


/*________________________________ FUNÇÕES AUXILIARES ADICIONAIS ________________________________*/

/*
 Reconecta o Disparador a novos Carregadores. Útil para reconfigurar
 o sistema de munição dinamicamente.
 
 * d: O Disparador a ser reconfigurado.
 * esq: Novo Carregador esquerdo.
 * dir: Novo Carregador direito.
 
 * Pré-condição: Todos os ponteiros devem ser válidos.
 * Pós-condição: O Disparador agora usa os novos Carregadores.
 * A forma em posição de disparo é mantida.
 */
void reconectaCarregadores(Disparador d, Carregador esq, Carregador dir) {
    if (d == NULL) {
        printf("ERRO: Disparador NULL passado para reconectaCarregadores.\n");
        return;
    }

    if (esq == NULL || dir == NULL) {
        printf("ERRO: Carregador NULL passado para reconectaCarregadores.\n");
        return;
    }

    DEBUG_PRINT("DEBUG ATTACH: Disparador %d reconectado: esq=%d, dir=%d\n",
                d->id, getCarregadorId(esq), getCarregadorId(dir));

    d->carregadorEsq = esq;
    d->carregadorDir = dir;
}

/*
 Limpa a forma da posição de disparo sem destruí-la. Útil quando
 a forma precisa ser movida para outro lugar sem ser disparada.
 
 * d: O Disparador.
 * f: A Forma a ser removida (deve ser a mesma que está em disparo).
 
 * Pré-condição: 'd' e 'f' devem ser válidos.
 * Pós-condição: Se 'f' estava em posição de disparo, é removida.
 */
void limpaFormaPronta(Disparador d, Forma f) {
    if (d == NULL || f == NULL) {
        return;
    }

    if (d->formaPronta == f) {
        DEBUG_PRINT("DEBUG LIMPA: Removendo forma ID=%d da posicao de disparo do disparador ID=%d\n",
                   getFormaId(f), d->id);
        d->formaPronta = NULL;
    }
}


/*_______________________________________ AÇÕES PRINCIPAIS _______________________________________*/

void preparaDisparo(Disparador d, char lado, int n) {
    if (d == NULL) {
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

    // Seleciona os carregadores baseado no lado: 'd' pega do esquerdo, 'e' pega do direito
Carregador carregadorOrigem = (ladoNormalizado == 'D') ? d->carregadorEsq : d->carregadorDir;
Carregador carregadorOposto = (ladoNormalizado == 'D') ? d->carregadorDir : d->carregadorEsq;

    // Repete a operação 'n' vezes para "ciclar" as formas
    for (int i = 0; i < n; i++) {
        DEBUG_PRINT("DEBUG PREP: Iteracao %d - Forma atual em disparo: %p\n", 
                   i, (void*)d->formaPronta);

        // Se já há uma forma pronta, move ela para o carregador oposto
        if (d->formaPronta != NULL) {
            DEBUG_PRINT("DEBUG PREP: Movendo forma ID=%d do disparo para carregador oposto\n",
                       getFormaId(d->formaPronta));
            
            // Você precisa implementar esta função no carregador.c:
            // void insereFormaCarregador(Carregador c, Forma f);
            insereFormaCarregador(carregadorOposto, d->formaPronta);
            d->formaPronta = NULL;
        }

        // Verifica se o carregador de origem tem formas
        if (carregadorEstaVazio(carregadorOrigem)) {
            DEBUG_PRINT("DEBUG PREP: Carregador de origem vazio. Nenhuma forma movida para disparo.\n");
            break;
        }

        // Pega a próxima forma do carregador de origem
        d->formaPronta = descarregaForma(carregadorOrigem);
        
        if (d->formaPronta != NULL) {
            DEBUG_PRINT("DEBUG PREP: Forma ID=%d colocada em posicao de disparo\n",
                       getFormaId(d->formaPronta));
        }
    }
}

Forma dispara(Disparador d, double dx, double dy) {
    if (d == NULL) {
        printf("ERRO: Disparador inexistente passado para dispara.\n");
        return NULL;
    }

    DEBUG_PRINT("DEBUG DISP: Tentando disparar. formaPronta=%p\n", (void*)d->formaPronta);
    
    if (d->formaPronta != NULL) {
        DEBUG_PRINT("DEBUG DISP: Forma ID=%d esta em posicao de disparo\n", 
                   getFormaId(d->formaPronta));
    }

    // Verifica se há uma forma pronta para disparo
    if (d->formaPronta == NULL) {
        printf("AVISO: Nenhuma forma esta na posicao de disparo.\n");
        return NULL;
    }

    // Pega a forma que será disparada
    Forma formaDisparada = d->formaPronta;
    d->formaPronta = NULL;

    // Calcula a posição final da forma
    double posX_final = d->x + dx;
    double posY_final = d->y + dy;

    // Atualiza a posição da forma
    setFormaPosicao(formaDisparada, posX_final, posY_final);

    DEBUG_PRINT("DEBUG DISP: Forma ID=%d disparada para (%.2f, %.2f)\n",
               getFormaId(formaDisparada), posX_final, posY_final);

    return formaDisparada;
}


/*________________________________ FUNÇÃO AVANÇADA: RAJADA ________________________________*/

/*
 Dispara múltiplas formas em sequência, criando um padrão de tiro.
 A cada disparo, o deslocamento aumenta segundo os incrementos (ix, iy).
 
 * d: O Disparador que executará a rajada.
 * lado: De qual Carregador pegar as formas ('E' ou 'D').
 * dx, dy: Deslocamento inicial do primeiro disparo.
 * ix, iy: Incremento de deslocamento a cada novo disparo.
 * a: A Arena onde as formas serão inseridas.
 
 * Pré-condição: 'd' e 'a' devem ser válidos.
 * Pós-condição: Retorna uma fila com todas as formas disparadas.
 * As formas são automaticamente inseridas na Arena.
 */
Queue rajadaDisparo(Disparador d, char lado, double dx, double dy, 
                    double ix, double iy, Arena a) {
    if (d == NULL || a == NULL) {
        printf("ERRO: Parametros nulos passados para rajadaDisparo.\n");
        return NULL;
    }

    // Salva a posição original do disparador
    double x_original = d->x;
    double y_original = d->y;

    // Cria fila para armazenar as formas disparadas
    Queue fila_disparos = createQueue();
    if (fila_disparos == NULL) {
        printf("ERRO: Falha ao criar fila de disparos.\n");
        return NULL;
    }

    int formas_disparadas = 0;

    DEBUG_PRINT("DEBUG RAJADA: Iniciando rajada. Posicao original: (%.2f, %.2f)\n", 
               x_original, y_original);
    DEBUG_PRINT("DEBUG RAJADA: dx=%.2f, dy=%.2f, ix=%.2f, iy=%.2f\n", dx, dy, ix, iy);

    // Loop infinito - para quando acabar a munição
    for (int i = 0; ; i++) {
        DEBUG_PRINT("DEBUG RAJADA: Iteracao %d\n", i);

        // Prepara a próxima forma
        preparaDisparo(d, lado, 1);
        
        // Se não há forma pronta, acabou a munição
        if (d->formaPronta == NULL) {
            DEBUG_PRINT("DEBUG RAJADA: Fim da rajada - carregador vazio\n");
            break;
        }

        // Calcula o deslocamento atual (aumenta a cada iteração)
        double dx_atual = dx + (i * ix);
        double dy_atual = dy + (i * iy);

        DEBUG_PRINT("DEBUG RAJADA: Deslocamento para forma %d: (%.2f, %.2f)\n",
                   getFormaId(d->formaPronta), dx_atual, dy_atual);

        // Dispara a forma
        Forma formaDisparada = dispara(d, dx_atual, dy_atual);

        if (formaDisparada != NULL) {
            DEBUG_PRINT("DEBUG RAJADA: Forma %d disparada para (%.2f, %.2f)\n",
                       getFormaId(formaDisparada),
                       getFormaX(formaDisparada),
                       getFormaY(formaDisparada));

            // Insere na arena e na fila de  
            insereFormaArena(a, formaDisparada);
            enfileira(fila_disparos, formaDisparada);
            formas_disparadas++;
        }
    }

    // Restaura a posição original do disparador
    setDisparadorPosicao(d, x_original, y_original);

    DEBUG_PRINT("DEBUG RAJADA: Rajada completa. %d formas disparadas\n", formas_disparadas);
    
    return fila_disparos;
}