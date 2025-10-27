#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "arena.h"
#include "chao.h"
#include "fila.h"
#include "formas.h"
#include "sobreposicao.h"

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
    
    char corBorda_original[64];
    char corPreench_original[64];
    
    strncpy(corBorda_original, getFormaCorBorda(f1), 63);
    corBorda_original[63] = '\0';
    
    strncpy(corPreench_original, getFormaCorPreenchimento(f1), 63);
    corPreench_original[63] = '\0';

    char novaCorBorda[64], novaCorPreench[64];
    strcpy(novaCorBorda, corPreench_original);
    strcpy(novaCorPreench, corBorda_original);

    int novoId = getFormaId(f1) + 100000;
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



/*________________________________ PROCESSAMENTO DE INTERAÇÕES ________________________________*/

void processaInteracoesArena(Arena a, Chao chao, double *pontuacao_total, Queue anotacoes_svg,
                              FILE *arquivo_txt, int *formas_clonadas, int *formas_esmagadas, void *repo) {
    if (a == NULL || chao == NULL) {
        printf("ERRO: Arena ou chão nulos!\n");
        return;
    }

    struct Arena_t *arena = (struct Arena_t*) a;
    (void)repo;

    double area_esmagada_round = 0.0;
    int total_formas_inicial = getTamanhoFila(arena->filaDeFormas);

    if (arquivo_txt) {
        fprintf(arquivo_txt, "\n=== PROCESSAMENTO DA ARENA ===\n");
        fprintf(arquivo_txt, "Total de formas: %d\n\n", total_formas_inicial);
    }

    //loop principal: processa pares adjacentes (I, J)
    while (getTamanhoFila(arena->filaDeFormas) >= 2) {
        Forma forma_I = desenfileira(arena->filaDeFormas);
        Forma forma_J = desenfileira(arena->filaDeFormas);

        if (forma_I == NULL || forma_J == NULL) {
            break;
        }

//verificacao de sobreposicao
        bool sobrepoe = false;
        TipoForma tipo_I = getFormaTipo(forma_I);
        TipoForma tipo_J = getFormaTipo(forma_J);

        // Usar as funções do módulo sobreposicao.h
        if (tipo_I == TIPO_CIRCULO && tipo_J == TIPO_CIRCULO) {
            sobrepoe = sobreposicaoCirculoCirculo(getFormaAssoc(forma_I), getFormaAssoc(forma_J));

        } else if (tipo_I == TIPO_CIRCULO && tipo_J == TIPO_RETANGULO) {
            sobrepoe = sobreposicaoCirculoRetangulo(getFormaAssoc(forma_I), getFormaAssoc(forma_J));

        } else if (tipo_I == TIPO_RETANGULO && tipo_J == TIPO_CIRCULO) {
            sobrepoe = sobreposicaoCirculoRetangulo(getFormaAssoc(forma_J), getFormaAssoc(forma_I));

        } else if (tipo_I == TIPO_RETANGULO && tipo_J == TIPO_RETANGULO) {
            sobrepoe = sobreposicaoRetanguloRetangulo(getFormaAssoc(forma_I), getFormaAssoc(forma_J));

        } else if (tipo_I == TIPO_CIRCULO && tipo_J == TIPO_LINHA) {
            sobrepoe = sobreposicaoCirculoLinha(getFormaAssoc(forma_I), getFormaAssoc(forma_J));

        } else if (tipo_I == TIPO_LINHA && tipo_J == TIPO_CIRCULO) {
            sobrepoe = sobreposicaoCirculoLinha(getFormaAssoc(forma_J), getFormaAssoc(forma_I));

        } else if (tipo_I == TIPO_CIRCULO && tipo_J == TIPO_TEXTO) {
            sobrepoe = sobreposicaoCirculoTexto(getFormaAssoc(forma_I), getFormaAssoc(forma_J));

        } else if (tipo_I == TIPO_TEXTO && tipo_J == TIPO_CIRCULO) {
            sobrepoe = sobreposicaoCirculoTexto(getFormaAssoc(forma_J), getFormaAssoc(forma_I));

        } else if (tipo_I == TIPO_RETANGULO && tipo_J == TIPO_LINHA) {
            sobrepoe = sobreposicaoRetanguloLinha(getFormaAssoc(forma_I), getFormaAssoc(forma_J));

        } else if (tipo_I == TIPO_LINHA && tipo_J == TIPO_RETANGULO) {
            sobrepoe = sobreposicaoRetanguloLinha(getFormaAssoc(forma_J), getFormaAssoc(forma_I));

        } else if (tipo_I == TIPO_RETANGULO && tipo_J == TIPO_TEXTO) {
            sobrepoe = sobreposicaoRetanguloTexto(getFormaAssoc(forma_I), getFormaAssoc(forma_J));

        } else if (tipo_I == TIPO_TEXTO && tipo_J == TIPO_RETANGULO) {
            sobrepoe = sobreposicaoRetanguloTexto(getFormaAssoc(forma_J), getFormaAssoc(forma_I));

        } else if (tipo_I == TIPO_LINHA && tipo_J == TIPO_LINHA) {
            sobrepoe = sobreposicaoLinhaLinha(getFormaAssoc(forma_I), getFormaAssoc(forma_J));

        } else if (tipo_I == TIPO_LINHA && tipo_J == TIPO_TEXTO) {
            sobrepoe = sobreposicaoLinhaTexto(getFormaAssoc(forma_I), getFormaAssoc(forma_J));

        } else if (tipo_I == TIPO_TEXTO && tipo_J == TIPO_LINHA) {
            sobrepoe = sobreposicaoLinhaTexto(getFormaAssoc(forma_J), getFormaAssoc(forma_I));

        } else if (tipo_I == TIPO_TEXTO && tipo_J == TIPO_TEXTO) {
            sobrepoe = sobreposicaoTextoTexto(getFormaAssoc(forma_I), getFormaAssoc(forma_J));
        }

        if (sobrepoe) {

            double area_I = getFormaArea(forma_I);
            double area_J = getFormaArea(forma_J);

            if (arquivo_txt) {
                fprintf(arquivo_txt, "Forma %d (I) vs Forma %d (J). HOUVE SOBREPOSIÇÃO.\n",
                        getFormaId(forma_I), getFormaId(forma_J));
            }

            //========== REGRA 1: área(I) < área(J) ==========
            if (area_I < area_J) {
                if (arquivo_txt) {
                    fprintf(arquivo_txt, "<<<-- I < J -->>> *Forma %d (área %.2f) ESMAGADA por forma %d (área %.2f).\n",
                            getFormaId(forma_I), area_I, getFormaId(forma_J), area_J);
                }

                //CRIAR ASTERISCO VERMELHO na posição da forma esmagada
                if (anotacoes_svg != NULL) {
                    double x_esmagada = getFormaX(forma_I);
                    double y_esmagada = getFormaY(forma_I);
                    
                    Estilo estilo_asterisco = criarEstilo("sans-serif", "bold", "30px");
                    Texto asterisco = criarTexto(-5000 - getFormaId(forma_I), 
                                                 x_esmagada, y_esmagada, 
                                                 "red", "red", 'm', "*", estilo_asterisco);
                    destroiEstilo(estilo_asterisco);
                    
                    Forma forma_asterisco = criaForma(-5000 - getFormaId(forma_I), TIPO_TEXTO, asterisco);
                    enfileira(anotacoes_svg, forma_asterisco);
                    
                }

                area_esmagada_round += area_I;
                if (formas_esmagadas != NULL) {
                    (*formas_esmagadas)++;
                }

                destroiForma(forma_I);
                adicionaFormaChao(chao, forma_J);
            }
            
            //========== REGRA 2: área(I) >= área(J) ==========
            else {
                if (arquivo_txt) {
                    fprintf(arquivo_txt, "<<<-- I >= J -->>> Forma %d (área %.2f) modifica forma %d (área %.2f).\n",
                            getFormaId(forma_I), area_I, getFormaId(forma_J), area_J);
                }

                //muda a cor de borda de J
                char corPreenchI[64];
                strncpy(corPreenchI, getFormaCorPreenchimento(forma_I), 63);
                corPreenchI[63] = '\0';
                
                setFormaCorBorda(forma_J, corPreenchI);

                //clona I com cores invertidas
                Forma clone_I = clonarFormaInvertida(forma_I);
                
                if (clone_I != NULL && formas_clonadas != NULL) {
                    (*formas_clonadas)++;
                }

                //ordem crítica: J → I → Clone_I
                adicionaFormaChao(chao, forma_J);
                adicionaFormaChao(chao, forma_I);
                if (clone_I != NULL) {
                    adicionaFormaChao(chao, clone_I);
                }
            }
        }
        else {
            //========== SEM SOBREPOSIÇÃO ==========
            if (arquivo_txt) {
                fprintf(arquivo_txt, "Forma %d (I) vs Forma %d (J). NÃO HOUVE SOBREPOSIÇÃO.\n",
                        getFormaId(forma_I), getFormaId(forma_J));
            }

            adicionaFormaChao(chao, forma_I);
            adicionaFormaChao(chao, forma_J);
        }
    }

    //processa forma ímpar (se houver)
    if (!estaVaziaFila(arena->filaDeFormas)) {
        Forma ultima = desenfileira(arena->filaDeFormas);
        adicionaFormaChao(chao, ultima);
    }

    if (pontuacao_total != NULL) {
        *pontuacao_total += area_esmagada_round;
    }

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