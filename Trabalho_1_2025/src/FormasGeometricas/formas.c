#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "formas.h"

#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

/*_______________________ ESTRUTURA INTERNA DA FORMA GENÉRICA _______________________*/
/*
* Esta é a definição da nossa struct opaca. Ela é o "cérebro" do módulo.
* - 'id': Armazena o ID, que é um atributo comum a todas as formas.
* - 'tipo': Usa o enum 'TipoForma' para identificar o que a forma realmente é.
* - 'dados_especificos': O ponteiro void* que aponta para a struct da forma
* específica (um Círculo, Retângulo, etc.).
*/
struct Forma_t {
    int id;
    TipoForma tipo;
    void *dados_especificos;
};


/*________________________________ FUNÇÕES DE CRIAÇÃO E DESTRUIÇÃO ________________________________*/

Forma criaForma(int id, TipoForma tipo, void *dados_especificos) {
    // Pré-condição: dados não podem ser nulos
    if (!dados_especificos) {
        return NULL;
    }

    // Aloca memória para a nossa estrutura genérica (o "invólucro")
    Forma f = (Forma) malloc(sizeof(struct Forma_t));
    if (!f) {
        printf("\nERRO: Falha ao alocar memória para a forma genérica!\n");
        return NULL;
    }

    // Atribui os dados comuns ao invólucro
    f->id = id;
    f->tipo = tipo;
    f->dados_especificos = dados_especificos;

    return f;
}

void destroiForma(Forma f) {
    if (!f) {
        return;
    }

    // Antes de liberar o invólucro, precisamos liberar a forma específica que está dentro dele.
    // Usamos o 'tipo' para saber qual função de destruição chamar.
    switch (f->tipo) {
        case TIPO_CIRCULO:
            destroiCirculo(f->dados_especificos);
            break;
        case TIPO_RETANGULO:
            destroiRetangulo(f->dados_especificos);
            break;
        case TIPO_LINHA:
            destroiLinha(f->dados_especificos);
            break;
        case TIPO_TEXTO:
            destroiTexto(f->dados_especificos);
            break;
    }

    free(f);
}


/*________________________________ FUNÇÕES DE CONSULTA (GETTERS) ________________________________*/

int getFormaId(const Forma f) {
    if (!f) {
        return -1; // Retorna um ID inválido em caso de erro
    }
    return f->id;
}

TipoForma getFormaTipo(const Forma f) {
    // valor de erro caso o enum seja usado incorretamente
    if (!f) {
        return -1; 
    }
    return f->tipo;
}

double getFormaX(const Forma f) {
    if (!f) {
        return 0.0;
    }

    // chama função getX específica de cada tipo de forma
    switch (f->tipo) {
        case TIPO_CIRCULO:   
            return getXCirculo(f->dados_especificos);
        case TIPO_RETANGULO: 
            return getXRetangulo(f->dados_especificos);
        case TIPO_LINHA:     
            return getX1Linha(f->dados_especificos); // Âncora da linha é o ponto 1
        case TIPO_TEXTO:     
            return getXTexto(f->dados_especificos);
    }
    return 0.0;
}

double getFormaY(const Forma f) {
    if (!f) {
        return 0.0;
    }

    // chama a função getY específica de cada tipo de forma
    switch (f->tipo) {
        case TIPO_CIRCULO:   
            return getYCirculo(f->dados_especificos);
        case TIPO_RETANGULO: 
            return getYRetangulo(f->dados_especificos);
        case TIPO_LINHA:     
            return getY1Linha(f->dados_especificos);
        case TIPO_TEXTO:     
            return getYTexto(f->dados_especificos);
    }
    return 0.0;
}

char *getFormaCorBorda(const Forma f) {
    if (!f) {
        return NULL;
    }

    switch (f->tipo) {
        case TIPO_CIRCULO:   
            return getCorbCirculo(f->dados_especificos);
        case TIPO_RETANGULO: 
            return getCorbRetangulo(f->dados_especificos);
        case TIPO_LINHA:     
            return getCorLinha(f->dados_especificos); // Linha só tem uma cor
        case TIPO_TEXTO:     
            return getCorbTexto(f->dados_especificos);
    }
    return NULL;
}

char *getFormaCorPreenchimento(const Forma f) {
    if (!f) {
        return NULL;
    }

    switch (f->tipo) {
        case TIPO_CIRCULO:   
            return getCorpCirculo(f->dados_especificos);
        case TIPO_RETANGULO: 
            return getCorpRetangulo(f->dados_especificos);
        case TIPO_LINHA:     
            return getCorLinha(f->dados_especificos); // Linha não tem preenchimento, retornar a cor principal
        case TIPO_TEXTO:     
            return getCorpTexto(f->dados_especificos);
    }
    return NULL;
}


/*________________________________ FUNÇÕES DE MODIFICAÇÃO (SETTERS) ________________________________*/

void setFormaPosicao(Forma f, double x, double y) {
    if (!f) {
        return;
    }

    switch (f->tipo) {
        case TIPO_CIRCULO:
            setXCirculo(f->dados_especificos, x);
            setYCirculo(f->dados_especificos, y);
            break;
        case TIPO_RETANGULO:
            setXRetangulo(f->dados_especificos, x);
            setYRetangulo(f->dados_especificos, y);
            break;
        case TIPO_TEXTO:
            setXTexto(f->dados_especificos, x);
            setYTexto(f->dados_especificos, y);
            break;
        case TIPO_LINHA: {
            // Mover uma linha significa transladar ambos os pontos
            double x1_antigo = getX1Linha(f->dados_especificos);
            double y1_antigo = getY1Linha(f->dados_especificos);
            double dx = x - x1_antigo;
            double dy = y - y1_antigo;

            double x2_antigo = getX2Linha(f->dados_especificos);
            double y2_antigo = getY2Linha(f->dados_especificos);
            
            setX1Linha(f->dados_especificos, x);
            setY1Linha(f->dados_especificos, y);
            setX2Linha(f->dados_especificos, x2_antigo + dx);
            setY2Linha(f->dados_especificos, y2_antigo + dy);
            break;
        }
    }
}

void setFormaCorBorda(Forma f, const char *corBorda) {
    if (!f) {
        return;
    }

    switch (f->tipo) {
        case TIPO_CIRCULO:  
            setCorbCirculo(f->dados_especificos, corBorda); 
            break;
        case TIPO_RETANGULO: 
            setCorbRetangulo(f->dados_especificos, corBorda); 
            break;
        case TIPO_LINHA:     
            setCorLinha(f->dados_especificos, corBorda); 
            break;
        case TIPO_TEXTO:     
            setCorbTexto(f->dados_especificos, corBorda); 
            break;
    }
}

void setFormaCorPreenchimento(Forma f, const char *corPreenchimento) {
    if (!f) {
        return;
    }

    switch (f->tipo) {
        case TIPO_CIRCULO:   
            setCorpCirculo(f->dados_especificos, corPreenchimento);
            break;
        case TIPO_RETANGULO: 
            setCorpRetangulo(f->dados_especificos, corPreenchimento); 
            break;
        case TIPO_LINHA:     
            setCorLinha(f->dados_especificos, corPreenchimento); 
            break;
        case TIPO_TEXTO:     
            setCorpTexto(f->dados_especificos, corPreenchimento); 
            break;
    }
}


/*________________________________ FUNÇÕES DE RENDERIZAÇÃO ________________________________*/

void desenhaForma(const Forma f, FILE *arquivoSvg) {
    if (!f || !arquivoSvg) {
        return;
    }

    // Delega a chamada para a função de impressão SVG específica de cada tipo
    switch (f->tipo) {
        case TIPO_CIRCULO:   
            imprimeCirculoSVG(f->dados_especificos, arquivoSvg); 
            break;
        case TIPO_RETANGULO: 
            imprimeRetanguloSVG(f->dados_especificos, arquivoSvg); 
            break;
        case TIPO_LINHA:     
            imprimeLinhaSVG(f->dados_especificos, arquivoSvg); 
            break;
        case TIPO_TEXTO:     
            imprimeTextoSVG(f->dados_especificos, arquivoSvg); 
            break;
    }
}