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
typedef struct {
    int id;
    TipoForma tipo;
    void *dados_especificos;
} FormaInterno;


/*________________________________ FUNÇÕES DE CRIAÇÃO E DESTRUIÇÃO ________________________________*/

Forma criaForma(int id, TipoForma tipo, void *dados_especificos) {
    // Pré-condição: dados não podem ser nulos
    if (!dados_especificos) {
        return NULL;
    }

    // Aloca memória para a nossa estrutura genérica (o "invólucro")
    FormaInterno *f = (FormaInterno*) malloc(sizeof(FormaInterno));
    if (!f) {
        printf("\nERRO: Falha ao alocar memória para a forma genérica!\n");
        return NULL;
    }

    // Atribui os dados comuns ao invólucro
    f->id = id;
    f->tipo = tipo;
    f->dados_especificos = dados_especificos;

    return (Forma)f;
}

void destroiForma(Forma f) {
    if (!f) {
        return;
    }

    FormaInterno *forma = (FormaInterno*)f;

    // Antes de liberar o invólucro, precisamos liberar a forma específica que está dentro dele.
    // Usamos o 'tipo' para saber qual função de destruição chamar.
    switch (forma->tipo) {
        case TIPO_CIRCULO:
            destroiCirculo(forma->dados_especificos);
            break;
        case TIPO_RETANGULO:
            destroiRetangulo(forma->dados_especificos);
            break;
        case TIPO_LINHA:
            destroiLinha(forma->dados_especificos);
            break;
        case TIPO_TEXTO:
            destroiTexto(forma->dados_especificos);
            break;
    }

    free(forma);
}


/*________________________________ FUNÇÕES DE CONSULTA (GETTERS) ________________________________*/

int getFormaId(const Forma f) {
    if (!f) {
        return -1; // Retorna um ID inválido em caso de erro
    }
    FormaInterno *forma = (FormaInterno*)f;
    return forma->id;
}

TipoForma getFormaTipo(const Forma f) {
    // valor de erro caso o enum seja usado incorretamente
    if (!f) {
        return -1; 
    }
    FormaInterno *forma = (FormaInterno*)f;
    return forma->tipo;
}

double getFormaX(const Forma f) {
    if (!f) {
        return 0.0;
    }

    FormaInterno *forma = (FormaInterno*)f;

    // chama função getX específica de cada tipo de forma
    switch (forma->tipo) {
        case TIPO_CIRCULO:   
            return getXCirculo(forma->dados_especificos);
        case TIPO_RETANGULO: 
            return getXRetangulo(forma->dados_especificos);
        case TIPO_LINHA:     
            return getX1Linha(forma->dados_especificos); // Âncora da linha é o ponto 1
        case TIPO_TEXTO:     
            return getXTexto(forma->dados_especificos);
    }
    return 0.0;
}

double getFormaY(const Forma f) {
    if (!f) {
        return 0.0;
    }

    FormaInterno *forma = (FormaInterno*)f;

    // chama a função getY específica de cada tipo de forma
    switch (forma->tipo) {
        case TIPO_CIRCULO:   
            return getYCirculo(forma->dados_especificos);
        case TIPO_RETANGULO: 
            return getYRetangulo(forma->dados_especificos);
        case TIPO_LINHA:     
            return getY1Linha(forma->dados_especificos);
        case TIPO_TEXTO:     
            return getYTexto(forma->dados_especificos);
    }
    return 0.0;
}

char *getFormaCorBorda(const Forma f) {
    if (!f) {
        return NULL;
    }

    FormaInterno *forma = (FormaInterno*)f;

    switch (forma->tipo) {
        case TIPO_CIRCULO:   
            return getCorbCirculo(forma->dados_especificos);
        case TIPO_RETANGULO: 
            return getCorbRetangulo(forma->dados_especificos);
        case TIPO_LINHA:     
            return getCorLinha(forma->dados_especificos); // Linha só tem uma cor
        case TIPO_TEXTO:     
            return getCorbTexto(forma->dados_especificos);
    }
    return NULL;
}

char *getFormaCorPreenchimento(const Forma f) {
    if (!f) {
        return NULL;
    }

    FormaInterno *forma = (FormaInterno*)f;

    switch (forma->tipo) {
        case TIPO_CIRCULO:   
            return getCorpCirculo(forma->dados_especificos);
        case TIPO_RETANGULO: 
            return getCorpRetangulo(forma->dados_especificos);
        case TIPO_LINHA:     
            return getCorLinha(forma->dados_especificos); // Linha não tem preenchimento, retornar a cor principal
        case TIPO_TEXTO:     
            return getCorpTexto(forma->dados_especificos);
    }
    return NULL;
}

void* getFormaAssoc(const Forma f) {
    if (!f) {
        return NULL;
    }
    
    FormaInterno *forma = (FormaInterno*)f;
    return forma->dados_especificos;
}

double getFormaArea(const Forma f) {
    if (!f) {
        return 0.0;  //erro
    }

    FormaInterno *forma = (FormaInterno*)f;

    switch (forma->tipo) {
        case TIPO_CIRCULO:
            return calculaAreaCirculo(forma->dados_especificos);
            
        case TIPO_RETANGULO:
            return calculaAreaRetangulo(forma->dados_especificos);
            
        case TIPO_LINHA: {
            Linha l = forma->dados_especificos;
            double comprimento = calculaComprimentoLinha(l);
            return 2.0 * comprimento;  //conforme o especificad
        }
            
        case TIPO_TEXTO: {
            Texto t = forma->dados_especificos;
            char *str = getTexto(t);

            if (str == NULL) return 0.0;
            int numCaracteres = strlen(str);

            return 20.0 * numCaracteres;  //conforme o especificado
        }
    }
    return 0.0;  //caso padrão para tipos inválidos
}

/*________________________________ FUNÇÕES DE MODIFICAÇÃO (SETTERS) ________________________________*/

void setFormaPosicao(Forma f, double x, double y) {
    if (!f) {
        return;
    }

    FormaInterno *forma = (FormaInterno*)f;

    switch (forma->tipo) {
        case TIPO_CIRCULO:
            setXCirculo(forma->dados_especificos, x);
            setYCirculo(forma->dados_especificos, y);
            break;
        case TIPO_RETANGULO:
            setXRetangulo(forma->dados_especificos, x);
            setYRetangulo(forma->dados_especificos, y);
            break;
        case TIPO_TEXTO:
            setXTexto(forma->dados_especificos, x);
            setYTexto(forma->dados_especificos, y);
            break;
        case TIPO_LINHA: {
            // Mover uma linha significa transladar ambos os pontos
            double x1_antigo = getX1Linha(forma->dados_especificos);
            double y1_antigo = getY1Linha(forma->dados_especificos);
            double dx = x - x1_antigo;
            double dy = y - y1_antigo;

            double x2_antigo = getX2Linha(forma->dados_especificos);
            double y2_antigo = getY2Linha(forma->dados_especificos);
            
            setX1Linha(forma->dados_especificos, x);
            setY1Linha(forma->dados_especificos, y);
            setX2Linha(forma->dados_especificos, x2_antigo + dx);
            setY2Linha(forma->dados_especificos, y2_antigo + dy);
            break;
        }
    }
}

void setFormaCorBorda(Forma f, const char *corBorda) {
    if (!f) {
        return;
    }

    FormaInterno *forma = (FormaInterno*)f;

    switch (forma->tipo) {
        case TIPO_CIRCULO:  
            setCorbCirculo(forma->dados_especificos, corBorda); 
            break;
        case TIPO_RETANGULO: 
            setCorbRetangulo(forma->dados_especificos, corBorda); 
            break;
        case TIPO_LINHA:     
            setCorLinha(forma->dados_especificos, corBorda); 
            break;
        case TIPO_TEXTO:     
            setCorbTexto(forma->dados_especificos, corBorda); 
            break;
    }
}

void setFormaCorPreenchimento(Forma f, const char *corPreenchimento) {
    if (!f) {
        return;
    }

    FormaInterno *forma = (FormaInterno*)f;

    switch (forma->tipo) {
        case TIPO_CIRCULO:   
            setCorpCirculo(forma->dados_especificos, corPreenchimento);
            break;
        case TIPO_RETANGULO: 
            setCorpRetangulo(forma->dados_especificos, corPreenchimento); 
            break;
        case TIPO_LINHA:     
            setCorLinha(forma->dados_especificos, corPreenchimento); 
            break;
        case TIPO_TEXTO:     
            setCorpTexto(forma->dados_especificos, corPreenchimento); 
            break;
    }
}


/*________________________________ FUNÇÕES DE RENDERIZAÇÃO ________________________________*/

void desenhaForma(const Forma f, FILE *arquivoSvg) {
    if (!f || !arquivoSvg) {
        return;
    }

    FormaInterno *forma = (FormaInterno*)f;

    // Delega a chamada para a função de impressão SVG específica de cada tipo
    switch (forma->tipo) {
        case TIPO_CIRCULO:   
            imprimeCirculoSVG(forma->dados_especificos, arquivoSvg); 
            break;
        case TIPO_RETANGULO: 
            imprimeRetanguloSVG(forma->dados_especificos, arquivoSvg); 
            break;
        case TIPO_LINHA:     
            imprimeLinhaSVG(forma->dados_especificos, arquivoSvg); 
            break;
        case TIPO_TEXTO:     
            imprimeTextoSVG(forma->dados_especificos, arquivoSvg); 
            break;
    }
}