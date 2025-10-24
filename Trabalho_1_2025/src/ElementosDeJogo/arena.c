
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "arena.h"
#include "chao.h"
#include "fila.h"
#include "formas.h"

#define PI 3.14159265358979323846

struct Arena_t {
    double largura;
    double altura;
    Queue filaDeFormas; 
};


/*________________________________ FUNÇÕES DE CRIAÇÃO E DESTRUIÇÃO ________________________________*/

Arena criaArena(double largura, double altura) {
    struct Arena_t *a = (struct Arena_t*) malloc(sizeof(struct Arena_t));
    if (a == NULL) {
        printf("ERRO: Falha ao alocar memória para a Arena.\n");
        return NULL;
    }

    a->filaDeFormas = createQueue();
    if (a->filaDeFormas == NULL) {
        printf("ERRO: Falha ao criar a fila interna da Arena.\n");
        free(a);
        return NULL;
    }

    a->largura = largura;
    a->altura = altura;

    return a;
}

void destroiArena(Arena a) {
    if (a == NULL) {
        return;
    }

    struct Arena_t *arena = (struct Arena_t*) a;

    // Arena é "dona" das formas - destruir cada forma antes de destruir a fila
    while (!estaVaziaFila(arena->filaDeFormas)) {
        Forma f = desenfileira(arena->filaDeFormas);
        destroiForma(f);
    }

    destroiFila(arena->filaDeFormas);
    free(arena);
}


/*________________________________ FUNÇÕES DE MANIPULAÇÃO DE FORMAS ________________________________*/

void insereFormaArena(Arena a, Forma f) {
    if (a == NULL || f == NULL) {
        return;
    }
    
    struct Arena_t *arena = (struct Arena_t*) a;
    enfileira(arena->filaDeFormas, f);
}

Forma removeFormaArena(Arena a) {
    if (a == NULL) {
        return NULL;
    }
    
    struct Arena_t *arena = (struct Arena_t*) a;
    if (estaVaziaFila(arena->filaDeFormas)) {
        return NULL;
    }
    
    return desenfileira(arena->filaDeFormas);
}

void iteraFormasArena(const Arena a, void (*executa)(Forma f, void *auxData), void *auxData) {
    if (a == NULL || executa == NULL) {
        return;
    }

    struct Arena_t *arena = (struct Arena_t*) a;

    int tamanhoOriginal = getTamanhoFila(arena->filaDeFormas);
    if (tamanhoOriginal == 0) {
        return;
    }

    // Loop processa cada elemento da fila uma vez
    // Retira um elemento do início, executa a função e coloca de volta no fim
    for (int i = 0; i < tamanhoOriginal; i++) {
        Forma f = desenfileira(arena->filaDeFormas);
        executa(f, auxData);
        enfileira(arena->filaDeFormas, f);
    }
}


/*________________________________ FUNÇÃO DE CLONAGEM COM CORES INVERTIDAS ________________________________*/

static Forma clonarFormaInvertida(Forma f1) {
    if (f1 == NULL) return NULL;

    TipoForma tipo = getFormaTipo(f1);
    
    // ✅ CÓPIA SEGURA DAS CORES
    char corBorda_original[64];
    char corPreench_original[64];
    
    strncpy(corBorda_original, getFormaCorBorda(f1), 63);
    corBorda_original[63] = '\0';
    
    strncpy(corPreench_original, getFormaCorPreenchimento(f1), 63);
    corPreench_original[63] = '\0';
    
    printf("DEBUG CLONE - Cores originais: borda='%s', preench='%s'\n", 
           corBorda_original, corPreench_original);

    // Inverter as cores: borda ↔ preenchimento
    char novaCorBorda[64], novaCorPreench[64];
    strcpy(novaCorBorda, corPreench_original);    // nova borda = antigo preenchimento
    strcpy(novaCorPreench, corBorda_original);     // novo preenchimento = antiga borda
    
    printf("DEBUG CLONE - Cores invertidas: borda='%s', preench='%s'\n", 
           novaCorBorda, novaCorPreench);

    int novoId = getFormaId(f1) + 100000; // Novo ID seguro
    void *dados = NULL;

    switch (tipo) {
        case TIPO_CIRCULO: {
            Circulo c = getFormaAssoc(f1);
            double x = getXCirculo(c);
            double y = getYCirculo(c);
            double r = getRCirculo(c);
            dados = criarCirculo(novoId, x, y, r, novaCorBorda, novaCorPreench, false, 0);
            break;
        }

        case TIPO_RETANGULO: {
            Retangulo r = getFormaAssoc(f1);
            double x = getXRetangulo(r);
            double y = getYRetangulo(r);
            double w = getLarguraRetangulo(r);
            double h = getAlturaRetangulo(r);
            dados = criarRetangulo(novoId, x, y, w, h, novaCorBorda, novaCorPreench, false, 0);
            break;
        }

        case TIPO_LINHA: {
            Linha l = getFormaAssoc(f1);
            double x1 = getX1Linha(l);
            double y1 = getY1Linha(l);
            double x2 = getX2Linha(l);
            double y2 = getY2Linha(l);
            dados = criarLinha(novoId, x1, y1, x2, y2, novaCorBorda, false, 0);
            break;
        }

        case TIPO_TEXTO: {
            Texto t = getFormaAssoc(f1);
            double x = getXTexto(t);
            double y = getYTexto(t);
            char ancora = getAncora(t);
            char *conteudo = getTexto(t);
            Estilo est = getEstiloTexto(t);
            dados = criarTexto(novoId, x, y, novaCorBorda, novaCorPreench, ancora, conteudo, est);
            break;
        }

        default:
            return NULL;
    }

    if (dados != NULL) {
        return criaForma(novoId, tipo, dados);
    }

    return NULL;
}



/*________________________________ VERIFICAÇÃO DE SOBREPOSIÇÃO ________________________________*/

static bool formasSobrepoem(Forma f1, Forma f2) {
    if (f1 == NULL || f2 == NULL) {
        return false;
    }

    TipoForma tipo1 = getFormaTipo(f1);
    TipoForma tipo2 = getFormaTipo(f2);

    // CASO 1: Círculo vs Círculo
    if (tipo1 == TIPO_CIRCULO && tipo2 == TIPO_CIRCULO) {
        Circulo c1 = getFormaAssoc(f1);
        Circulo c2 = getFormaAssoc(f2);
        
        double x1 = getXCirculo(c1);
        double y1 = getYCirculo(c1);
        double r1 = getRCirculo(c1);
        
        double x2 = getXCirculo(c2);
        double y2 = getYCirculo(c2);
        double r2 = getRCirculo(c2);
        
        double dx = x1 - x2;
        double dy = y1 - y2;
        double distQuadrada = dx * dx + dy * dy;
        double somaRaios = r1 + r2;
        
        return distQuadrada <= (somaRaios * somaRaios);
    }

    // CASO 2: Retângulo vs Retângulo
    if (tipo1 == TIPO_RETANGULO && tipo2 == TIPO_RETANGULO) {
        Retangulo r1 = getFormaAssoc(f1);
        Retangulo r2 = getFormaAssoc(f2);
        
        double x1 = getXRetangulo(r1);
        double y1 = getYRetangulo(r1);
        double w1 = getLarguraRetangulo(r1);
        double h1 = getAlturaRetangulo(r1);
        
        double x2 = getXRetangulo(r2);
        double y2 = getYRetangulo(r2);
        double w2 = getLarguraRetangulo(r2);
        double h2 = getAlturaRetangulo(r2);
        
        // Teste AABB correto
        bool overlapX = (x1 < x2 + w2) && (x1 + w1 > x2);
        bool overlapY = (y1 < y2 + h2) && (y1 + h1 > y2);
        
        return overlapX && overlapY;
    }

    // CASO 3: Círculo vs Retângulo
    if ((tipo1 == TIPO_CIRCULO && tipo2 == TIPO_RETANGULO) ||
        (tipo1 == TIPO_RETANGULO && tipo2 == TIPO_CIRCULO)) {
        
        Circulo c;
        Retangulo r;
        
        if (tipo1 == TIPO_CIRCULO) {
            c = getFormaAssoc(f1);
            r = getFormaAssoc(f2);
        } else {
            c = getFormaAssoc(f2);
            r = getFormaAssoc(f1);
        }
        
        double cx = getXCirculo(c);
        double cy = getYCirculo(c);
        double raio = getRCirculo(c);
        
        double rx = getXRetangulo(r);
        double ry = getYRetangulo(r);
        double w = getLarguraRetangulo(r);
        double h = getAlturaRetangulo(r);
        
        double closestX = cx;
        double closestY = cy;
        
        if (cx < rx) closestX = rx;
        else if (cx > rx + w) closestX = rx + w;
        
        if (cy < ry) closestY = ry;
        else if (cy > ry + h) closestY = ry + h;
        
        double dx = cx - closestX;
        double dy = cy - closestY;
        double distQuadrada = dx * dx + dy * dy;
        
        return distQuadrada <= (raio * raio);
    }

    // CASOS COM LINHA/TEXTO: Por simplicidade, retorna false
    return false;
}


/*________________________________ PROCESSAMENTO DE INTERAÇÕES ________________________________*/

void processaInteracoesArena(Arena a, Chao chao, double *pontuacao_total, Queue anotacoes_svg,
                              FILE *arquivo_txt, int *formas_clonadas, int *formas_esmagadas, void *repo) {
    if (a == NULL || chao == NULL) {
        printf("ERRO: Arena ou chão nulos!\n");
        return;
    }

    struct Arena_t *arena = (struct Arena_t*) a;
    (void)anotacoes_svg;
    (void)repo;

    double area_esmagada_round = 0.0;
    int total_formas_inicial = getTamanhoFila(arena->filaDeFormas);

    printf("\n=== INICIANDO PROCESSAMENTO DA ARENA ===\n");
    printf("Total de formas na arena: %d\n", total_formas_inicial);

    if (arquivo_txt) {
        fprintf(arquivo_txt, "\n=== PROCESSAMENTO DA ARENA ===\n");
        fprintf(arquivo_txt, "Total de formas: %d\n\n", total_formas_inicial);
    }

    // ========== LOOP PRINCIPAL: Processa pares adjacentes (I, J) ==========
    while (getTamanhoFila(arena->filaDeFormas) >= 2) {
        // Remove os dois primeiros elementos da fila (I e J)
        Forma forma_I = desenfileira(arena->filaDeFormas);
        Forma forma_J = desenfileira(arena->filaDeFormas);

        if (forma_I == NULL || forma_J == NULL) {
            break;
        }

 printf("\n--- Comparando formas ---\n");
        printf("Forma I: ID=%d, Pos=(%.2f, %.2f), Área=%.2f\n", 
               getFormaId(forma_I), getFormaX(forma_I), getFormaY(forma_I), getFormaArea(forma_I));
        printf("Forma J: ID=%d, Pos=(%.2f, %.2f), Área=%.2f\n", 
               getFormaId(forma_J), getFormaX(forma_J), getFormaY(forma_J), getFormaArea(forma_J));

        bool sobrepoe = formasSobrepoem(forma_I, forma_J);

        if (sobrepoe) {
            printf("✓ Sobreposição detectada!\n");

            double area_I = getFormaArea(forma_I);
            double area_J = getFormaArea(forma_J);

            if (arquivo_txt) {
                fprintf(arquivo_txt, "Forma %d (I) vs Forma %d (J). HOUVE SOBREPOSIÇÃO.\n",
                        getFormaId(forma_I), getFormaId(forma_J));
            }

            // ========== REGRA 1: área(I) < área(J) ==========
            if (area_I < area_J) {
                printf(">>> REGRA 1: I < J <<<\n");
                printf("* Forma ID=%d (área=%.2f) ESMAGADA por ID=%d (área=%.2f)\n",
                       getFormaId(forma_I), area_I, getFormaId(forma_J), area_J);

                if (arquivo_txt) {
                    fprintf(arquivo_txt, "<<<-- I < J -->>> *Forma %d (área %.2f) ESMAGADA por forma %d (área %.2f).\n",
                            getFormaId(forma_I), area_I, getFormaId(forma_J), area_J);
                }

                // Acumula área esmagada e incrementa contador
                area_esmagada_round += area_I;
                if (formas_esmagadas != NULL) {
                    (*formas_esmagadas)++;
                }

                // I é destruído, J volta ao chão
                destroiForma(forma_I);
                adicionaFormaChao(chao, forma_J);
            }
         
// ========== REGRA 2: área(I) >= área(J) ==========
else {
    printf(">>> REGRA 2: I >= J <<<\n");
    printf("Forma ID=%d (área=%.2f) modifica ID=%d (área=%.2f)\n",
           getFormaId(forma_I), area_I, getFormaId(forma_J), area_J);

    if (arquivo_txt) {
        fprintf(arquivo_txt, "<<<-- I >= J -->>> Forma %d (área %.2f) modifica forma %d (área %.2f).\n",
                getFormaId(forma_I), area_I, getFormaId(forma_J), area_J);
    }

    // APENAS MUDA A COR DE BORDA DE J
    char corPreenchI[64];
    strncpy(corPreenchI, getFormaCorPreenchimento(forma_I), 63);
    corPreenchI[63] = '\0';
    
    printf("DEBUG - Mudando borda de J para: '%s'\n", corPreenchI);
    printf("DEBUG - J ANTES: borda='%s', preench='%s'\n",
           getFormaCorBorda(forma_J), getFormaCorPreenchimento(forma_J));
    
    // SÓ muda a borda de J 
    setFormaCorBorda(forma_J, corPreenchI);
    
    printf("DEBUG - J DEPOIS: borda='%s', preench='%s'\n",
           getFormaCorBorda(forma_J), getFormaCorPreenchimento(forma_J));

    // Clona I com cores invertidas
    Forma clone_I = clonarFormaInvertida(forma_I);
    
    if (clone_I != NULL && formas_clonadas != NULL) {
        (*formas_clonadas)++;
        printf("✓ Clone criado: ID=%d, borda='%s', preench='%s'\n", 
               getFormaId(clone_I),
               getFormaCorBorda(clone_I),
               getFormaCorPreenchimento(clone_I));
    }

    // ========== ORDEM CRÍTICA: J → I → Clone_I ==========
    adicionaFormaChao(chao, forma_J);   // 1º: J (com borda modificada, preench original)
    adicionaFormaChao(chao, forma_I);   // 2º: I (cores originais)
    if (clone_I != NULL) {
        adicionaFormaChao(chao, clone_I); // 3º: Clone (cores invertidas)
    }
}
        }
        else {
            // ========== SEM SOBREPOSIÇÃO ==========
            printf("✗ Não há sobreposição\n");
            if (arquivo_txt) {
                fprintf(arquivo_txt, "Forma %d (I) vs Forma %d (J). NÃO HOUVE SOBREPOSIÇÃO.\n",
                        getFormaId(forma_I), getFormaId(forma_J));
            }

            // Mantém ordem relativa: I → J
            adicionaFormaChao(chao, forma_I);
            adicionaFormaChao(chao, forma_J);
        }
    }

    // ========== Processa forma ímpar (se houver) ==========
    if (!estaVaziaFila(arena->filaDeFormas)) {
        Forma ultima = desenfileira(arena->filaDeFormas);
        printf("\n>>> Forma ímpar (ID=%d) devolvida ao chão sem processamento\n", 
               getFormaId(ultima));
        adicionaFormaChao(chao, ultima);
    }

    // ========== Atualiza pontuação total ==========
    if (pontuacao_total != NULL) {
        *pontuacao_total += area_esmagada_round;
    }

    // ========== Relatório final ==========
    printf("\n=== PROCESSAMENTO CONCLUÍDO ===\n");
    printf("Formas esmagadas: %d\n", formas_esmagadas ? *formas_esmagadas : 0);
    printf("Formas clonadas: %d\n", formas_clonadas ? *formas_clonadas : 0);
    printf("Área total esmagada: %.2f\n\n", area_esmagada_round);

    if (arquivo_txt) {
        fprintf(arquivo_txt, "\nÁrea total esmagada: %.2f\n", area_esmagada_round);
        fprintf(arquivo_txt, "Formas esmagadas: %d\n", formas_esmagadas ? *formas_esmagadas : 0);
        fprintf(arquivo_txt, "Formas clonadas: %d\n\n", formas_clonadas ? *formas_clonadas : 0);
    }
}

/*________________________________ FUNÇÕES DE CONSULTA E MODIFICAÇÃO ________________________________*/

double getArenaLargura(const Arena a) {
    if (a == NULL) {
        return -1.0;
    }
    struct Arena_t *arena = (struct Arena_t*) a;
    return arena->largura;
}

double getArenaAltura(const Arena a) {
    if (a == NULL) {
        return -1.0;
    }
    struct Arena_t *arena = (struct Arena_t*) a;
    return arena->altura;
}

void setArenaLargura(Arena a, double novaLargura) {
    if (a != NULL) {
        struct Arena_t *arena = (struct Arena_t*) a;
        arena->largura = novaLargura;
    }
}

void setArenaAltura(Arena a, double novaAltura) {
    if (a != NULL) {
        struct Arena_t *arena = (struct Arena_t*) a;
        arena->altura = novaAltura;
    }
}

int getArenaNumFormas(const Arena a) {
    if (a == NULL) {
        return 0;
    }
    struct Arena_t *arena = (struct Arena_t*) a;
    return getTamanhoFila(arena->filaDeFormas);
}

bool arenaEstaVazia(const Arena a) {
    if (a == NULL) {
        return true;
    }
    struct Arena_t *arena = (struct Arena_t*) a;
    return estaVaziaFila(arena->filaDeFormas);
}