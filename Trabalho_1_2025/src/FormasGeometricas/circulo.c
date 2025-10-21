#include "circulo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265358979323846

// estrutura interna do círculo
typedef struct circulo {
    int id;           // identificador único
    double x;         // coordenada X do centro
    double y;         // coordenada Y do centro
    double r;         // raio
    char *corb;       // cor da borda
    char *corp;       // cor de preenchimento
    double sw;        // largura do traço (stroke-width)
    bool disp;        // flag de disparo
    int n;            // identificador de seleção
} circuloC;


/*         FUNÇÕES DE CRIAÇÃO E DESTRUIÇÃO  */

Circulo criarCirculo(int i, double x, double y, double r, char *corb, char *corp, bool disp, int n) {
    if (r <= 0) {
        printf("Erro: raio deve ser maior que zero.\n");
        return NULL;
    }
    
    circuloC *c = (circuloC*) malloc(sizeof(circuloC));
    if (c == NULL) {
        printf("Erro: falha na alocação de memória.\n");
        exit(1);
    }
    
    c->id = i;
    c->x = x;
    c->y = y;
    c->r = r;
    
    c->corb = (char*) malloc((strlen(corb) + 1) * sizeof(char));
    if (c->corb == NULL) {
        free(c);
        printf("Erro: falha na alocação de memória.\n");
        exit(1);
    }
    strcpy(c->corb, corb);
    
    c->corp = (char*) malloc((strlen(corp) + 1) * sizeof(char));
    if (c->corp == NULL) {
        free(c->corb);
        free(c);
        printf("Erro: falha na alocação de memória.\n");
        exit(1);
    }
    strcpy(c->corp, corp);
    
    c->sw = 1.0;      
    c->disp = disp;
    c->n = n;
    
    return (Circulo) c;
}

void destroiCirculo(Circulo c) {
    if (c == NULL) {
        return;
    }
    circuloC *circ = (circuloC*) c;
    free(circ->corb);
    free(circ->corp);
    free(circ);
}

/*           MÉTODOS GET (CONSULTA)  */
int getIdCirculo(const Circulo c) {
    if (c == NULL) {
        return -1; // Retorna ID inválido em caso de erro
    }
    circuloC *circ = (circuloC*) c;
    return circ->id;
}
double getXCirculo(Circulo c) {
    circuloC *circ = (circuloC*) c;
    return circ->x;
}

double getYCirculo(Circulo c) {
    circuloC *circ = (circuloC*) c;
    return circ->y;
}

double getRCirculo(Circulo c) {
    circuloC *circ = (circuloC*) c;
    return circ->r;
}

char* getCorbCirculo(Circulo c) {
    circuloC *circ = (circuloC*) c;
    return circ->corb;
}

char* getCorpCirculo(Circulo c) {
    circuloC *circ = (circuloC*) c;
    return circ->corp;
}

double getSWCirculo(Circulo c) {
    circuloC *circ = (circuloC*) c;
    return circ->sw;
}

bool getDispCirculo(Circulo c) {
    circuloC *circ = (circuloC*) c;
    return circ->disp;
}

int getNCirculo(Circulo c) {
    circuloC *circ = (circuloC*) c;
    return circ->n;
}

/*               MÉTODOS SET (MODIFICAÇÃO)  */

void setXCirculo(Circulo c, double x) {
    circuloC *circ = (circuloC*) c;
    circ->x = x;
}

void setYCirculo(Circulo c, double y) {
    circuloC *circ = (circuloC*) c;
    circ->y = y;
}

void setRCirculo(Circulo c, double r) {
    if (r <= 0) {
        printf("Erro: raio deve ser maior que zero.\n");
        return;
    }
    circuloC *circ = (circuloC*) c;
    circ->r = r;
}

void setCorbCirculo(Circulo c,const char* corb) {
    circuloC *circ = (circuloC*) c;
    free(circ->corb);
    circ->corb = (char*) malloc((strlen(corb) + 1) * sizeof(char));
    if (circ->corb == NULL) {
        printf("Erro: falha na alocação de memória.\n");
        exit(1);
    }
    strcpy(circ->corb, corb);
}

void setCorpCirculo(Circulo c, const char* corp) {
    circuloC *circ = (circuloC*) c;
    free(circ->corp);
    circ->corp = (char*) malloc((strlen(corp) + 1) * sizeof(char));
    if (circ->corp == NULL) {
        printf("Erro: falha na alocação de memória.\n");
        exit(1);
    }
    strcpy(circ->corp, corp);
}

void setSWCirculo(Circulo c, double sw) {
    if (sw < 0) {
        printf("Erro: largura do traço deve ser >= 0.\n");
        return;
    }
    circuloC *circ = (circuloC*) c;
    circ->sw = sw;
}

void setDispCirculo(Circulo c, bool disp) {
    circuloC *circ = (circuloC*) c;
    circ->disp = disp;
}

void setNCirculo(Circulo c, int n) {
    circuloC *circ = (circuloC*) c;
    circ->n = n;
}

/*               FUNÇÕES GEOMÉTRICAS */

double calculaAreaCirculo(Circulo c) {
    circuloC *circ = (circuloC*) c;
    return PI * circ->r * circ->r;
}

double calculaPerimetroCirculo(Circulo c) {
    circuloC *circ = (circuloC*) c;
    return 2 * PI * circ->r;
}

bool pontoNoCirculo(Circulo c, double px, double py) {
    circuloC *circ = (circuloC*) c;
    double distancia = sqrt(pow(px - circ->x, 2) + pow(py - circ->y, 2));
    return distancia <= circ->r;
}

bool circulosIntersectam(Circulo c1, Circulo c2) {
    circuloC *circ1 = (circuloC*) c1;
    circuloC *circ2 = (circuloC*) c2;
    
    double distanciaCentros = sqrt(pow(circ2->x - circ1->x, 2) + 
                                   pow(circ2->y - circ1->y, 2));
    double somaRaios = circ1->r + circ2->r;
    
    return distanciaCentros <= somaRaios;
}

void imprimeCirculoSVG(Circulo c, FILE *arquivo) {
    if (c == NULL || arquivo == NULL) {
        return;
    }
    
    circuloC *circ = (circuloC *)c;
    
fprintf(arquivo, "  <circle cx=\"%.2f\" cy=\"%.2f\" r=\"%.2f\" ",
        circ->x, circ->y, circ->r);

fprintf(arquivo, "stroke=\"%s\" fill=\"%s\" fill-opacity=\"0.5\" ",
        circ->corb, circ->corp);

fprintf(arquivo, "stroke-width=\"%.2f\"/>\n",
        circ->sw);
}