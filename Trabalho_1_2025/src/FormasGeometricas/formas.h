#ifndef FORMAS_H
#define FORMAS_H

#include <stdio.h>
#include <math.h> 
#include "circulo.h"
#include "linha.h"
#include "retangulo.h"
#include "texto.h"


/*_______________________ TIPO ABSTRATO DE DADOS: FORMAS GEOMÉTRICAS GENÉRICAS _______________________*/
/*
*        Este módulo define a interface para manipulação de formas geométricas
*        de maneira genérica e unificada. Ele atua como uma camada de abstração
*        sobre os TADs específicos (Círculo, Linha, Retângulo, Texto).
*                
*        A estrutura principal (FORMAGERAL) encapsula uma forma geométrica genérica, 
*        representada por um ponteiro opaco que pode referenciar qualquer tipo de forma.
*/

// Tipos genéricos opacos
typedef void * FORMAGERAL;  // Forma encapsulada
typedef void * FORMA;       // Forma específica
typedef void * Fila;        // Estrutura de fila
typedef void * Pilha;       // Estrutura de pilha
typedef void * LANC;        // Lançador


/*________________________________ FUNÇÕES BÁSICAS ________________________________*/
/*
Cria e configura uma estrutura de forma genérica que encapsula uma forma
geométrica específica junto com informações sobre seu tipo.

*        f: ponteiro para a forma geométrica específica já criada 
*           (pode ser Círculo, Retângulo, Linha ou Texto)
*        tipo: identificador numérico do tipo da forma:
*              1 = Círculo
*              2 = Retângulo
*              3 = Linha
*              4 = Texto
*
*        Pré-condição: f deve ser um ponteiro válido para uma forma já criada,
*                      tipo deve estar entre 1 e 4
*        Pós-condição: retorna um ponteiro opaco para a estrutura FORMAGERAL
*                      que encapsula a forma e seu tipo, ou NULL em caso de falha
*/
FORMAGERAL setforma(FORMA f, int tipo);

/*
Obtém o identificador numérico do tipo da forma geométrica encapsulada (através
de estruturas condicionais switch/case).

*        f: ponteiro opaco para a forma geométrica genérica
*
*        Pré-condição: f deve ser um ponteiro válido para FORMAGERAL
*        Pós-condição: retorna o tipo da forma (1-4) conforme definido:
*                      1 = Círculo, 2 = Retângulo, 3 = Linha, 4 = Texto
*/
int gettipoforma(FORMA f);

/*
Obtém a forma geométrica específica encapsulada que está no topo de uma
estrutura de dados tipo fila. Esta função é utilizada para acessar o
conteúdo de coleções sem remover o elemento, permitindo inspeção da
forma no topo da pilha (seguindo o princípio FIFO- First-In, First-Out).

*
*        f: ponteiro opaco para a estrutura de fila contendo formas
*
*        Pré-condição: f deve ser um ponteiro válido para uma Fila não vazia
*        Pós-condição: retorna ponteiro opaco para a FORMAGERAL no topo da fila,
*                      sem removê-la da estrutura
*/
FORMAGERAL gettipofila(Fila f);

/*
Obtém a forma geométrica específica encapsulada que está no topo de uma
estrutura de dados tipo pilha. Esta função é utilizada para acessar o
conteúdo de coleções sem remover o elemento, permitindo inspeção da
forma no topo da pilha (seguindo o princípio LIFO - Last In, First Out).

*        p: ponteiro opaco para a estrutura de pilha contendo formas
*
*        Pré-condição: p deve ser um ponteiro válido para uma Pilha não vazia
*        Pós-condição: retorna ponteiro opaco para a FORMAGERAL no topo da pilha,
*                      sem removê-la da estrutura
*/
FORMAGERAL gettipopilha(Pilha p);

/*
Obtém o identificador único (ID) da forma geométrica, utilizado
para distinguir formas individuais em coleções, permitindo operações de
busca, comparação e referência específica.

*        f: ponteiro opaco para a forma geométrica
*
*        Pré-condição: f deve ser um ponteiro válido para FORMA
*        Pós-condição: retorna ponteiro opaco para o ID da forma
*/
FORMAGERAL getID(FORMA f);

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

#endif