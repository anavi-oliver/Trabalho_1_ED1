#include "retangulo.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct retangulo{
    int id; //identificador
    double x;
    double y;
    double w; //deve ser >0
    double h; //deve ser >0
    char *corb;
    char *corp;
    double sw; //largura do traco
    bool disp;
    int n; 

}retanguloR; //retanguloR != Retangulo

Retangulo criarRetangulo(int i, double x, double y, double w, double h, char *corb, char *corp, bool disp, int n){
    if(w<=0 || h<=0 ){//condigcoes
        printf("Erro: largura e altura devem ser maiores que zero.\n");
        return NULL;
    }
//alocar
    retanguloR *r= (retanguloR*) malloc (sizeof(retanguloR));
    if(r==NULL){
        printf("\n Erro na alocacao de memoria!!\n");
        exit(1);
    }

//atribuir
    r->id= i;
    r->x = x;
    r->y = y;
    r->w = w;
    r->h = h;

    //cor borda 
    r->corb = (char*)malloc((strlen(corb) + 1) * sizeof(char));
    if(r->corb ==NULL){ 
        free(r);
        printf("\n Erro na alocacao de memoria!!\n");
        exit(1);
    }
    strcpy(r->corb, corb); //copiar como apenas corb
    
    //cor preenchemento
    r->corp = (char*) malloc((strlen(corp) + 1) * sizeof(char));
    if (r->corp == NULL) {
        free(r->corb);
        free(r);
        printf("\n Erro na alocacao de memoria!!\n");
        exit(1);
    }
    strcpy(r->corp, corp);

    r->sw = 1.0;  //largura da borda, altera no setsw   
    r->disp = disp; 
    r->n = n;
    
    return (Retangulo) r;
    
    
} //criar retangulo



void destroiRetangulo(Retangulo r) {
    if (r == NULL) {
        return;
    }
    retanguloR *ret = (retanguloR*) r;
    free(ret->corb);
    free(ret->corp);
    free(ret);
}

//get =   retanguloR *ret = (retanguloR*) r, pega o tipo opaco e faz o cast pra struct, convertendo o Retangulo pra retanguloR* e dps retorna campo desejado(ex: x,y, w...)

double getXRetangulo(Retangulo r) {
    retanguloR *ret = (retanguloR*) r;
    return ret->x;
}

double getYRetangulo(Retangulo r) {
    retanguloR *ret = (retanguloR*) r;
    return ret->y;
}

double getLarguraRetangulo(Retangulo r) {
    retanguloR *ret = (retanguloR*) r;
    return ret->w;
}

double getAlturaRetangulo(Retangulo r) {
    retanguloR *ret = (retanguloR*) r;
    return ret->h;
}

char* getCorbRetangulo(Retangulo r) {
    retanguloR *ret = (retanguloR*) r;
    return ret->corb;
}

char* getCorpRetangulo(Retangulo r) {
    retanguloR *ret = (retanguloR*) r;
    return ret->corp;
}

double getSWRetangulo(Retangulo r) {
    retanguloR *ret = (retanguloR*) r;
    return ret->sw;
}

bool getDispRetangulo(Retangulo r) {
    retanguloR *ret = (retanguloR*) r;
    return ret->disp;
}

int getNRetangulo(Retangulo r) {
    retanguloR *ret = (retanguloR*) r;
    return ret->n;
}

//set: permite modificar, tmb faz o cast  de Retangulo (void*) para retanguloR* igual o get, mas agr atribui o novo valor ao desejado(ex: x,y,w)
    //mas esses com validacao pra mais certeza
void setXRetangulo(Retangulo r, double x) {
    retanguloR *ret = (retanguloR*) r;
    ret->x = x;
}

void setYRetangulo(Retangulo r, double y) {
    retanguloR *ret = (retanguloR*) r;
    ret->y = y;
}

void setLarguraRetangulo(Retangulo r, double w) {
    if (w <= 0) {
        printf("Erro! A largura deve ser maior que zero.\n");
        return;
    }
    retanguloR *ret = (retanguloR*) r;
    ret->w = w;
}

void setAlturaRetangulo(Retangulo r, double h) {
    if (h <= 0) {
        printf("Erro!A altura deve ser maior que zero.\n");
        return;
    }
    retanguloR *ret = (retanguloR*) r;
    ret->h = h;
}

//mais complexos - alocar dinamicamente
void setCorbRetangulo(Retangulo r, const char* corb) {
    retanguloR *ret = (retanguloR*) r;
    free(ret->corb);
    ret->corb = (char*) malloc((strlen(corb) + 1) * sizeof(char));
    if (ret->corb == NULL) {
        printf("\n Erro na alocacao de memoria!!\n");
        exit(1);
    }
    strcpy(ret->corb, corb);
}

void setCorpRetangulo(Retangulo r,const char* corp) {
    retanguloR *ret = (retanguloR*) r;
    free(ret->corp);
    ret->corp = (char*) malloc((strlen(corp) + 1) * sizeof(char));
    if (ret->corp == NULL) {
        printf("\n Erro na alocacao de memoria!!\n");
        exit(1);
    }

    strcpy(ret->corp, corp);
}

void setSWRetangulo(Retangulo r, double sw) {
    if (sw < 0) {
        printf("Erro!A largura do traço deve ser >= 0\n");
        return;
    }
    retanguloR *ret = (retanguloR*) r;
    ret->sw = sw;
}


void setDispRetangulo(Retangulo r, bool disp) {
    retanguloR *ret = (retanguloR*) r;
    ret->disp = disp;
}

void setNRetangulo(Retangulo r, int n) {
    retanguloR *ret = (retanguloR*) r;
    ret->n = n;
}

//gemometria
double calculaAreaRetangulo(Retangulo r) {
    retanguloR *ret = (retanguloR*) r;
    return ret->w * ret->h;
}

double calculaPerimetroRetangulo(Retangulo r) {
    retanguloR *ret = (retanguloR*) r;
    return 2 * (ret->w + ret->h);
}

bool pontoNoRetangulo(Retangulo r, double px, double py) {
    retanguloR *ret = (retanguloR*) r;
    return (px >= ret->x && px <= ret->x + ret->w &&
            py >= ret->y && py <= ret->y + ret->h);
}

bool retangulosIntersectam(Retangulo r1, Retangulo r2) {
    retanguloR *ret1 = (retanguloR*) r1;
    retanguloR *ret2 = (retanguloR*) r2;
    
    // verifica se NAO ha interseção (é mais fácil), depois inverte
    if (ret1->x + ret1->w < ret2->x ||  // r1 está à esquerda de r2
        ret2->x + ret2->w < ret1->x ||  // r2 está à esquerda de r1
        ret1->y + ret1->h < ret2->y ||  // r1 está acima de r2
        ret2->y + ret2->h < ret1->y) {  // r2 está acima de r1
        return false;
    }
    
    return true; // há interseção
}

//renderizacao

void imprimeRetanguloSVG(Retangulo r, FILE *arquivo) {
    if (r == NULL || arquivo == NULL) {
        return;
    }

    retanguloR *ret = (retanguloR*) r;
fprintf(arquivo, "\t<rect x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" fill=\"%s\" fill-opacity=\"0.5\" stroke=\"%s\" stroke-width=\"%.2f\" />\n",
        ret->x,
        ret->y,
        ret->w,
        ret->h,
        ret->corp,  
        ret->corb,  
        ret->sw);
}