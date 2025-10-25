#include "linha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct linha {
    int id;
    double x1;
    double y1;
    double x2;
    double y2;
    char *cor;
    double sw;
    bool disp;
    int n;
    bool pontilhada;
} linhaC;

/*                                FUNÇÕES DE CRIAÇÃO E DESTRUIÇÃO                                */ 

Linha criarLinha(int i, double x1, double y1, double x2, double y2, char *cor, bool disp, int n) {
    linhaC *l = (linhaC*) malloc(sizeof(linhaC));
    if (l == NULL) {
        printf("Erro: falha na alocação de memória.\n");
        exit(1);
    }
    
    l->id = i;
    l->x1 = x1;
    l->y1 = y1;
    l->x2 = x2;
    l->y2 = y2;
    
    l->cor = (char*) malloc((strlen(cor) + 1) * sizeof(char));
    if (l->cor == NULL) {
        free(l);
        printf("Erro: falha na alocação de memória.\n");
        exit(1);
    }
    strcpy(l->cor, cor);
    
    l->sw = 1.0;     
    l->disp = disp;
    l->n = n;
    l->pontilhada = false;
    
    return (Linha) l;
}

void destroiLinha(Linha l) {
    if (l == NULL) {
        return;
    }
    linhaC *linha = (linhaC*) l;
    free(linha->cor);
    free(linha);
}

/*                                MÉTODOS GET                                */

double getX1Linha(Linha l) {
    linhaC *linha = (linhaC*) l;
    return linha->x1;
}

double getY1Linha(Linha l) {
    linhaC *linha = (linhaC*) l;
    return linha->y1;
}

double getX2Linha(Linha l) {
    linhaC *linha = (linhaC*) l;
    return linha->x2;
}

double getY2Linha(Linha l) {
    linhaC *linha = (linhaC*) l;
    return linha->y2;
}

char* getCorLinha(Linha l) {
    linhaC *linha = (linhaC*) l;
    return linha->cor;
}

double getSWLinha(Linha l) {
    linhaC *linha = (linhaC*) l;
    return linha->sw;
}

bool getDispLinha(Linha l) {
    linhaC *linha = (linhaC*) l;
    return linha->disp;
}

int getNLinha(Linha l) {
    linhaC *linha = (linhaC*) l;
    return linha->n;
}

/*                                MÉTODOS SET                                */ 
void setX1Linha(Linha l, double x) {
    linhaC *linha = (linhaC*) l;
    linha->x1 = x;
}

void setY1Linha(Linha l, double y) {
    linhaC *linha = (linhaC*) l;
    linha->y1 = y;
}

void setX2Linha(Linha l, double x) {
    linhaC *linha = (linhaC*) l;
    linha->x2 = x;
}

void setY2Linha(Linha l, double y) {
    linhaC *linha = (linhaC*) l;
    linha->y2 = y;
}

void setCorLinha(Linha l, const char* cor) {
    linhaC *linha = (linhaC*) l;
    free(linha->cor);
    linha->cor = (char*) malloc((strlen(cor) + 1) * sizeof(char));
    if (linha->cor == NULL) {
        printf("Erro: falha na alocação de memória.\n");
        exit(1);
    }
    strcpy(linha->cor, cor);
}

void setSWLinha(Linha l, double sw) {
    if (sw < 0) {
        printf("Erro: largura do traço deve ser >= 0.\n");
        return;
    }
    linhaC *linha = (linhaC*) l;
    linha->sw = sw;
}

void setDispLinha(Linha l, bool disp) {
    linhaC *linha = (linhaC*) l;
    linha->disp = disp;
}

void setNLinha(Linha l, int n) {
    linhaC *linha = (linhaC*) l;
    linha->n = n;
}

void setPontilhadaLinha(Linha l, bool pontilhada) {
    if (l == NULL) return;
    linhaC *linha = (linhaC*) l;
    linha->pontilhada = pontilhada;
}

/*                                FUNÇÕES GEOMÉTRICAS                                */

double calculaComprimentoLinha(Linha l) {
    linhaC *linha = (linhaC*) l;
    double dx = linha->x2 - linha->x1;
    double dy = linha->y2 - linha->y1;
    return sqrt(dx * dx + dy * dy);
}

double calculaAreaLinha(Linha l) {
    return 10 * calculaComprimentoLinha(l);
}

/*                          RENDERIZACAO                    */

void imprimeLinhaSVG(Linha l, FILE *arquivo) {
    if (l == NULL || arquivo == NULL) {
        return;
    }

    linhaC *linha = (linhaC*) l;

    //imprime a tag <line> no arquivo SVG
    fprintf(arquivo, "\t<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" stroke=\"%s\" stroke-width=\"%.2f\"",
            linha->x1, linha->y1, linha->x2, linha->y2, linha->cor, linha->sw);
    
    //adiciona pontilhado se precisar
    if (linha->pontilhada) {
        fprintf(arquivo, " stroke-dasharray=\"1,1\"");
    }
    
    fprintf(arquivo, " />\n");
}