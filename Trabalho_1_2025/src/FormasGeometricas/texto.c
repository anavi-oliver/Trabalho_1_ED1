#include "texto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura interna do Estilo (sintaxe de typedef mais concisa)
typedef struct stEstilo {
    char *fFamily;
    char *fWeight;
    char *fSize;
} Estilo_t;

// Estrutura interna do Texto (sintaxe de typedef mais concisa)
typedef struct stTexto {
    int i;
    double x, y;
    char *corb, *corp;
    char a;  // âncora: 'i', 'm', 'f'
    char *txto;
    Estilo_t *e;
} Texto_t;


/*________________________________ FUNÇÕES AUXILIARES INTERNAS ________________________________*/

// Cria uma cópia de um estilo existente
// O estilo original é const, pois não será modificado.
Estilo_t *criaCopiaEstilo(const Estilo_t *original) {
    if (original == NULL) {
        return NULL;
    }
    
    Estilo_t *e = (Estilo_t *)malloc(sizeof(Estilo_t));
    if (e == NULL) {
        // Erros devem ir para stderr
        fprintf(stderr, "Erro ao alocar memoria para o estilo do texto!\n");
        exit(1);
    }
    
    // Alocação e cópia dos campos da string
    e->fFamily = (char *)malloc(strlen(original->fFamily) + 1);
    strcpy(e->fFamily, original->fFamily);
    
    e->fWeight = (char *)malloc(strlen(original->fWeight) + 1);
    strcpy(e->fWeight, original->fWeight);
    
    e->fSize = (char *)malloc(strlen(original->fSize) + 1);
    strcpy(e->fSize, original->fSize);

    // Validação de alocação para robustez
    if (e->fFamily == NULL || e->fWeight == NULL || e->fSize == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para os campos do estilo!\n");
        free(e->fFamily);
        free(e->fWeight);
        free(e->fSize);
        free(e);
        exit(1);
    }
    
    return e;
}


/*________________________________ FUNÇÕES DE ESTILO ________________________________*/

Estilo criarEstilo(const char *family, const char *weight, const char *size) {
    Estilo_t *e = (Estilo_t *)malloc(sizeof(Estilo_t));
    if (e == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para o estilo do texto!\n");
        exit(1);
    }
    
    e->fFamily = (char *)malloc(strlen(family) + 1);
    strcpy(e->fFamily, family);
    
    e->fWeight = (char *)malloc(strlen(weight) + 1);
    strcpy(e->fWeight, weight);
    
    e->fSize = (char *)malloc(strlen(size) + 1);
    strcpy(e->fSize, size);

    if (e->fFamily == NULL || e->fWeight == NULL || e->fSize == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para os campos do estilo!\n");
        free(e->fFamily);
        free(e->fWeight);
        free(e->fSize);
        free(e);
        exit(1);
    }
    
    return (Estilo)e;
}

void destroiEstilo(Estilo e) {
    if (e == NULL) {
        return;
    }
    
    Estilo_t *est = (Estilo_t *)e;
    free(est->fFamily);
    free(est->fWeight);
    free(est->fSize);
    free(est);
}

// Getters agora usam "const" para indicar que não modificam o objeto
char* getFamily(const Estilo e) {
    if (e == NULL) return NULL;
    return ((Estilo_t *)e)->fFamily;
}

char* getWeight(const Estilo e) {
    if (e == NULL) return NULL;
    return ((Estilo_t *)e)->fWeight;
}

char* getSize(const Estilo e) {
    if (e == NULL) return NULL;
    return ((Estilo_t *)e)->fSize;
}

// Setters agora recebem "const char*" pois apenas leem a string de entrada
void setFamily(Estilo e, const char *family) {
    if (e == NULL || family == NULL) return;
    
    Estilo_t *est = (Estilo_t *)e;
    
    char *novaFamilia = (char *)realloc(est->fFamily, strlen(family) + 1);
    if (novaFamilia == NULL) {
        fprintf(stderr, "Erro ao realocar a familia do estilo do texto!\n");
        return;
    }
    strcpy(novaFamilia, family);
    est->fFamily = novaFamilia;
}

void setWeight(Estilo e, const char *weight) {
    if (e == NULL || weight == NULL) return;
    
    Estilo_t *est = (Estilo_t *)e;
    
    char *novoPeso = (char *)realloc(est->fWeight, strlen(weight) + 1);
    if (novoPeso == NULL) {
        fprintf(stderr, "Erro ao realocar a espessura do estilo do texto!\n");
        return;
    }
    strcpy(novoPeso, weight);
    est->fWeight = novoPeso;
}

void setSize(Estilo e, const char *size) {
    if (e == NULL || size == NULL) return;
    
    Estilo_t *est = (Estilo_t *)e;
    
    char *novoSize = (char *)realloc(est->fSize, strlen(size) + 1);
    if (novoSize == NULL) {
        fprintf(stderr, "Erro ao realocar o tamanho do estilo do texto!\n");
        return;
    }
    strcpy(novoSize, size);
    est->fSize = novoSize;
}


/*________________________________ FUNÇÕES DE TEXTO ________________________________*/

// Corrigido o nome do parâmetro "texto" para "conteudo" para evitar conflito
Texto criarTexto(int i, double x, double y, const char *corb, const char *corp, char a, const char *conteudo, Estilo estilo) {
    Texto_t *t = (Texto_t *)malloc(sizeof(Texto_t));
    if (t == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para a stTexto!\n");
        exit(1);
    }
    
    t->i = i;
    t->x = x;
    t->y = y;
    t->a = a;
    
    t->corb = (char *)malloc(strlen(corb) + 1);
    strcpy(t->corb, corb);
    
    t->corp = (char *)malloc(strlen(corp) + 1);
    strcpy(t->corp, corp);
    
    t->txto = (char *)malloc(strlen(conteudo) + 1);
    strcpy(t->txto, conteudo);
    
    if (t->corb == NULL || t->corp == NULL || t->txto == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para os campos do texto!\n");
        free(t->corb);
        free(t->corp);
        free(t->txto);
        free(t);
        exit(1);
    }
    
    t->e = criaCopiaEstilo((Estilo_t *)estilo);
    
    return (Texto)t;
}

void destroiTexto(Texto t) {
    if (t == NULL) return;
    
    Texto_t *txt = (Texto_t *)t;
    
    free(txt->corb);
    free(txt->corp);
    free(txt->txto);
    destroiEstilo(txt->e);
    free(txt);
}

int getIdTexto(const Texto t) {
    if (t == NULL) return -1;
    return ((Texto_t *)t)->i;
}

double getXTexto(const Texto t) {
    if (t == NULL) return 0.0;
    return ((Texto_t *)t)->x;
}

double getYTexto(const Texto t) {
    if (t == NULL) return 0.0;
    return ((Texto_t *)t)->y;
}

char* getCorbTexto(const Texto t) {
    if (t == NULL) return NULL;
    return ((Texto_t *)t)->corb;
}

char* getCorpTexto(const Texto t) {
    if (t == NULL) return NULL;
    return ((Texto_t *)t)->corp;
}

char getAncora(const Texto t) {
    if (t == NULL) return '\0';
    return ((Texto_t *)t)->a;
}

char* getTexto(const Texto t) {
    if (t == NULL) return NULL;
    return ((Texto_t *)t)->txto;
}

Estilo getEstiloTexto(const Texto t) {
    if (t == NULL) return NULL;
    return (Estilo)((Texto_t *)t)->e;
}

void setXTexto(Texto t, double x) {
    if (t == NULL) return;
    ((Texto_t *)t)->x = x;
}

void setYTexto(Texto t, double y) {
    if (t == NULL) return;
    ((Texto_t *)t)->y = y;
}

void setCorbTexto(Texto t, const char *corb) {
    if (t == NULL || corb == NULL) return;
    
    Texto_t *txt = (Texto_t *)t;
    char *novaCorb = (char *)realloc(txt->corb, strlen(corb) + 1);
    if (novaCorb == NULL) {
        fprintf(stderr, "Erro ao realocar memoria para a nova cor de borda!\n");
        return;
    }
    strcpy(novaCorb, corb);
    txt->corb = novaCorb;
}

void setCorpTexto(Texto t, const char *corp) {
    if (t == NULL || corp == NULL) return;

    Texto_t *txt = (Texto_t *)t;
    char *novaCorp = (char *)realloc(txt->corp, strlen(corp) + 1);
     if (novaCorp == NULL) {
        fprintf(stderr, "Erro ao realocar memoria para a nova cor de preenchimento!\n");
        return;
    }
    strcpy(novaCorp, corp);
    txt->corp = novaCorp;
}

void setAncora(Texto t, char a) {
    if (t == NULL) return;
    ((Texto_t *)t)->a = a;
}

void setTexto(Texto t, const char *conteudo) {
    if (t == NULL || conteudo == NULL) return;
    
    Texto_t *txt = (Texto_t *)t;
    char *novoTexto = (char *)realloc(txt->txto, strlen(conteudo) + 1);
    if (novoTexto == NULL) {
        fprintf(stderr, "Erro ao realocar memoria para o novo texto!\n");
        return;
    }
    strcpy(novoTexto, conteudo);
    txt->txto = novoTexto;
}

void setEstiloTexto(Texto t, Estilo estilo) {
    if (t == NULL || estilo == NULL) return;
    
    Texto_t *txt = (Texto_t *)t;
    
    destroiEstilo(txt->e);
    txt->e = criaCopiaEstilo((Estilo_t *)estilo);
}


/*________________________________ FUNÇÕES DE RENDERIZAÇÃO ________________________________*/

void imprimeTextoSVG(const Texto t, FILE *arquivo) {
    if (t == NULL || arquivo == NULL) return;
    
    Texto_t *txt = (Texto_t *)t;
    Estilo_t *est = txt->e;
    
    const char *text_anchor = "middle"; // Valor padrão
    if (txt->a == 'i') {
        text_anchor = "start";
    } else if (txt->a == 'f') {
        text_anchor = "end";
    }
    
    fprintf(arquivo, "\t<text x=\"%.2f\" y=\"%.2f\" fill=\"%s\" stroke=\"%s\" text-anchor=\"%s\"",
            txt->x, txt->y, txt->corp, txt->corb, text_anchor);
    
    if (est != NULL) {
        fprintf(arquivo, " font-family=\"%s\" font-weight=\"%s\" font-size=\"%s\"",
                est->fFamily, est->fWeight, est->fSize);
    }
    
    fprintf(arquivo, ">%s</text>\n", txt->txto);
}

//para debug
void imprimeTextoTXT(const Texto t, FILE *arquivo) {
    if (t == NULL || arquivo == NULL) return;
    
    Texto_t *txt = (Texto_t *)t;
    Estilo_t *est = txt->e;
    
    fprintf(arquivo, "Texto ID: %d\n", txt->i);
    fprintf(arquivo, "  Posição: (%.2f, %.2f)\n", txt->x, txt->y);
    fprintf(arquivo, "  Cor borda: %s\n", txt->corb);
    fprintf(arquivo, "  Cor preenchimento: %s\n", txt->corp);
    fprintf(arquivo, "  Âncora: %c\n", txt->a);
    fprintf(arquivo, "  Conteúdo: \"%s\"\n", txt->txto);
    
    if (est != NULL) {
        fprintf(arquivo, "  Estilo:\n");
        fprintf(arquivo, "    Família: %s\n", est->fFamily);
        fprintf(arquivo, "    Peso: %s\n", est->fWeight);
        fprintf(arquivo, "    Tamanho: %s\n", est->fSize);
    }
    
    fprintf(arquivo, "\n");
}