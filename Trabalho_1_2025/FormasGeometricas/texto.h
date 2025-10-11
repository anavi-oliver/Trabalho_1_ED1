#ifndef TEXTO_H
#define TEXTO_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef void * Texto;
typedef void * Estilo;

/*                              FUNÇÕES DE ESTILO                              */

Estilo criarEstilo(char *family, char *weight, char *size);
void destroiEstilo(Estilo e);

char* getFamily(Estilo e);
char* getWeight(Estilo e);
char* getSize(Estilo e);

void setFamily(Estilo e, char *family);
void setWeight(Estilo e, char *weight);
void setSize(Estilo e, char *size);


/*                        FUNÇÕES DE CRIAÇÃO E DESTRUIÇÃO DE TEXTO                        */

Texto criarTexto(int i, double x, double y, char *corb, char *corp, char a, char *texto, Estilo estilo);
void destroiTexto(Texto t);


/*                                 MÉTODOS GET (CONSULTA)                                */

/*
Retorna o identificador único do texto, permitindo distingui-lo de outros
elementos e possibilitando operações de busca e referência específica.

*        t: ponteiro opaco para o texto a ser consultado
*
*        Pré-condição: t deve ser um ponteiro válido para Texto
*        Pós-condição: retorna o ID do texto como número inteiro,
*                      ou -1 se t for NULL, sem modificar o texto
*/
int getIdTexto(Texto t);

/*
Retorna a coordenada X da posição do texto na arena, indicando sua
localização horizontal no plano cartesiano.

*        t: ponteiro opaco para o texto a ser consultado
*
*        Pré-condição: t deve ser um ponteiro válido para Texto
*        Pós-condição: retorna a coordenada X como double,
*                      ou 0.0 se t for NULL, sem alterar o texto
*/
double getXTexto(Texto t);

/*
Retorna a coordenada Y da posição do texto na arena, indicando sua
localização vertical no plano cartesiano. Complementa getXTexto para
determinar completamente a localização do texto.

*        t: ponteiro opaco para o texto a ser consultado
*
*        Pré-condição: t deve ser um ponteiro válido para Texto
*        Pós-condição: retorna a coordenada Y como double,
*                      ou 0.0 se t for NULL, sem modificar o texto
*/
double getYTexto(Texto t);

char* getCorbTexto(Texto t);
char* getCorpTexto(Texto t);
char getAncora(Texto t);
char* getTexto(Texto t);
Estilo getEstiloTexto(Texto t);


/*                                 MÉTODOS SET (MODIFICAÇÃO)                                */

/*
Define uma nova coordenada X para o texto, reposicionando-o
horizontalmente na arena. Esta operação move o texto sem alterar
seu conteúdo, cor ou outras propriedades.

*        t: ponteiro opaco para o texto a ser modificado
*        x: nova coordenada X para a posição do texto
*
*        Pré-condição: t deve ser um ponteiro válido para Texto
*        Pós-condição: a coordenada X é atualizada para o novo valor,
*                      se t for NULL a função não faz nada
*/
void setXTexto(Texto t, double x);

/*
Define uma nova coordenada Y para o texto, reposicionando-o
verticalmente na arena. Complementa setXTexto para reposicionamento
completo no plano cartesiano.

*        t: ponteiro opaco para o texto a ser modificado
*        y: nova coordenada Y para a posição do texto
*
*        Pré-condição: t deve ser um ponteiro válido para Texto
*        Pós-condição: a coordenada Y é atualizada para o novo valor,
*                      se t for NULL a função não faz nada
*/
void setYTexto(Texto t, double y);

void setCorbTexto(Texto t, char *corb);
void setCorpTexto(Texto t, char *corp);
void setAncora(Texto t, char a);
void setTexto(Texto t, char *texto);
void setEstiloTexto(Texto t, Estilo estilo);


/*                                  FUNÇÕES DE RENDERIZAÇÃO                                  */

/*
Imprime a representação SVG do texto em um arquivo. Esta função gera
o código SVG necessário para visualizar o texto na posição especificada,
com as cores, âncora e estilo tipográfico definidos. A âncora é convertida
automaticamente para o formato SVG ('i'→"start", 'm'→"middle", 'f'→"end").

*        t: ponteiro opaco para o texto a ser renderizado
*        arquivo: ponteiro para FILE aberto para escrita em modo SVG
*
*        Pré-condição: t deve ser um ponteiro válido para Texto,
*                      arquivo deve ser um FILE* válido aberto para escrita
*        Pós-condição: código SVG do texto é escrito no arquivo no formato:
*                      <text x="..." y="..." fill="..." stroke="..." 
*                            text-anchor="..." font-family="..." 
*                            font-weight="..." font-size="...">conteudo</text>
*                      se t ou arquivo forem NULL a função não faz nada
*/
void imprimeTextoSVG(Texto t, FILE *arquivo);

/*
Imprime informações detalhadas do texto em formato texto simples.
Esta função gera um relatório legível contendo ID, posição, cores,
âncora, conteúdo e propriedades do estilo tipográfico, útil para
debug e logs do jogo.

*        t: ponteiro opaco para o texto a ser impresso
*        arquivo: ponteiro para FILE aberto para escrita em modo texto
*
*        Pré-condição: t deve ser um ponteiro válido para Texto,
*                      arquivo deve ser um FILE* válido aberto para escrita
*        Pós-condição: informações do texto são escritas no arquivo em formato legível,
*                      incluindo ID, posição, cores, âncora, conteúdo e estilo,
*                      se t ou arquivo forem NULL a função não faz nada
*/
void imprimeTextoTXT(Texto t, FILE *arquivo);

#endif