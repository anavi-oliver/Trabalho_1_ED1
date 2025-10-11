#include "formas.h"
//fazer texto!!!!!!
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include <stdbool.h>

#include "circulo.h"
#include "linha.h"
#include "retangulo.h"
#include "texto.h"



typedef struct formagenerica{
    void * forma; //ponteiro generico pra forma
    int id; //id do lancador
    int tipoforma; //tipo da forma (1,2,3 ou 4)
    bool vivo; //flag indicadora
}FORMAG;


/*________________________________ FUNÇÕES BÁSICAS ________________________________*/
/*
Cria e configura uma estrutura de forma genérica que encapsula uma forma
geométrica específica junto com informações sobre seu tipo.
*/
FORMAGERAL setforma(FORMA f, int tipo){
    //pre condicao:
    if(tipo<1 || tipo >4 || f == NULL){
        return NULL;
    }

//alocar memoria e confere
FORMAG * fg = (FORMAG*) malloc(sizeof(FORMAG));
    if(fg == NULL){
        printf("\nErro ao alocar memoria!!\n");
        return NULL;
    }

    //atribuicoes
fg->forma = f;
fg->tipoforma= tipo;
//por padrao: forma existe e nao tem id
fg->vivo= true;
fg->id = -1;

return(FORMAGERAL)fg;
}

/*________________________________ FUNÇÕES GET ________________________________*/

int gettipoforma(FORMA f){
//pre cond: f n pode ser null

    if(f=NULL){
        return NULL;
    }

    FORMAG* fg = (FORMAG *) malloc(sizeof(FORMAG));
    if(fg==NULL){
        printf("\nERRO na alocacao!!\n");
        return NULL;
    }
return fg->tipoforma;
}
//______________________________________________________________
                                    //acabar
FORMAGERAL gettipofila(Fila f){
//Pré-condição: f deve ser valido
    if(f=NULL){
        return NULL;
    }

    FORMAG* fg = (FORMAG *) malloc(sizeof(FORMAG));
    if(fg==NULL){
        printf("\nERRO na alocacao!!\n");
        return NULL;
    }

}

FORMAGERAL gettipopilha(Pilha p);
//______________________________________________________________

FORMAGERAL getID(FORMA f){
//f deve ser valido
    if(f=NULL){
        return NULL;
    }
    FORMAG* fg = (FORMAG *) malloc(sizeof(FORMAG));
int id= -1;

switch (fg->tipoforma) //pega o id de acordo com o tipo
{
case 1: //circulo
    id = (int)getXCirculo(fg->forma); //um ajuste conforme sua funcao de ID
    break;

case 2: //retangulo
    id = (int)getXRetangulo(fg->forma); 
    break;

case 3: //linha
    id = (int)getX1Linha(fg->forma); 
    break;

case 4: //linha
    id = (int)getxtexto(fg->forma); 
    break;
default:
    break;
}

}

/*
Compara os identificadores únicos de duas formas geométricas do mesmo tipo.
*
*        f1: ponteiro opaco para a primeira forma a ser comparada
*        f2: ponteiro opaco para a segunda forma a ser comparada
*
*        Pré-condição: f1 e f2 devem ser ponteiros válidos para FORMAGERAL
*                      do mesmo tipo geométrico
*        Pós-condição: retorna valor inteiro indicando a relação entre os IDs:
*                      < 0 se ID(f1) < ID(f2)
*                      = 0 se ID(f1) == ID(f2)
*                      > 0 se ID(f1) > ID(f2)
*/
int comparaIDformas(FORMAGERAL f1, FORMAGERAL f2);


/*________________________________ FUNÇÕES GEOMÉTRICAS ________________________________*/
/*
Obtém a coordenada X da âncora (o centro para círculos ou outro ponto característico
para retângulos, linhas, etc.) da forma geométrica.

*        f: ponteiro opaco para a forma geométrica
*
*        Pré-condição: f deve ser um ponteiro válido para FORMAGERAL
*        Pós-condição: retorna a coordenada X como número de ponto flutuante
*/
float getX(FORMAGERAL f);

/*
Obtém a coordenada Y da âncora ou centro da forma geométrica. Complementa
a função getX para localizar completamente a posição da forma no plano
cartesiano.

*        f: ponteiro opaco para a forma geométrica
*
*        Pré-condição: f deve ser um ponteiro válido para FORMAGERAL
*        Pós-condição: retorna a coordenada Y como número de ponto flutuante
*/
float getY(FORMAGERAL f);

/*
Calcula e retorna a área ocupada pela forma geométrica de maneira genérica.
Esta função implementa polimorfismo, calculando a área apropriada baseada
no tipo específico da forma (área do círculo, retângulo, etc.). Para formas
sem área definida (como linhas), pode retornar 0 ou valor especial.

*        f: ponteiro opaco para a forma geométrica
*
*        Pré-condição: f deve ser um ponteiro válido para FORMAGERAL
*        Pós-condição: retorna a área calculada como número de ponto flutuante,
*                      em unidades quadradas do sistema de coordenadas utilizado
*/
float getArea(FORMAGERAL f);


/*________________________________ FUNÇÕES DE ESTADO ________________________________*/

/*
Imprime as informações detalhadas da forma em um arquivo de saída de texto (TXT).
Esta função gera relatórios textuais contendo dados da forma como ID,
coordenadas, dimensões, cores e outras propriedades relevantes.

*        f: ponteiro opaco para a forma geométrica a ser impressa
*        c: ponteiro opaco para contexto contendo o arquivo de saída
*           e possíveis configurações de formatação
*
*        Pré-condição: f deve ser uma FORMAGERAL válida,
*                      c deve conter um FILE* válido e aberto para escrita
*        Pós-condição: retorna a forma após impressão,
*                      dados da forma são escritos no arquivo especificado
*/
FORMAGERAL printLista(FORMAGERAL f, void *c);

/*
Imprime a representação gráfica da forma em um arquivo SVG (Scalable Vector
Graphics). Esta função gera o código SVG necessário para visualizar a forma,
incluindo posicionamento, cores, dimensões e outras propriedades visuais.

*        x: coordenada X adicional para ajuste de posição (deslocamento)
*        y: coordenada Y adicional para ajuste de posição (deslocamento)
*        f: ponteiro opaco para a forma geométrica a ser renderizada
*        d: fator de escala ou distância para cálculos de visualização
*        extra: ponteiro opaco para dados extras como FILE* do SVG,
*               configurações de estilo, ou contexto de renderização
*
*        Pré-condição: f deve ser uma FORMAGERAL válida,
*                      extra deve conter um FILE* válido aberto para escrita SVG
*        Pós-condição: código SVG da forma é escrito no arquivo,
*                      a forma é renderizada na posição especificada
*/
void printasvg(float x, float y, FORMAGERAL f, float d, void* extra);

/*
Marca a forma como não viva (destruição lógica). Esta operação não libera
memória imediatamente, mas sinaliza que a forma deve ser considerada inativa
ou removida em futuras operações de limpeza, permitindo remoção segura
durante iterações em coleções.

*        f: ponteiro opaco para a forma geométrica a ser marcada
*
*        Pré-condição: f deve ser uma FORMAGERAL válida
*        Pós-condição: a forma é marcada como "não viva" internamente,
*                      será ignorada ou removida em operações subsequentes
*/
void destruir_form(FORMAGERAL f);
