#ifndef TEXTO_H
#define TEXTO_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//ponteiro generico para o texto e estilo do texto, ambos serão explicados abaixo
typedef void * Texto;
typedef void * Estilo;

/* FUNÇÕES DE ESTILO                                 */

/*
Cria e aloca memória para um novo objeto de Estilo. O estilo define
a aparência tipográfica de um texto, incluindo a família da fonte,
o peso (negrito, normal) e o tamanho.

* family: string que representa a família da fonte (ex: "Arial")
* weight: string que representa o peso da fonte (ex: "bold")
* size: string que representa o tamanho da fonte (ex: "12px")
*
* Pré-condição: as strings de entrada devem ser válidas
* Pós-condição: retorna um ponteiro opaco para o Estilo criado,
* ou o programa é encerrado em caso de falha de alocação
*/
Estilo criarEstilo(const char *family, const char *weight, const char *size);

//============================================================================================

/*OBS:
* para as funcoes abaixo: 
*    e: ponteiro opaco para o estilo a ser utilizado dependendo do contexto da funcao
*   Pré-condição: e deve ser um ponteiro válido
*/

//Libera toda a memória associada a um objeto de Estilo.
void destroiEstilo(Estilo e);

/*
Retorna a família da fonte associada a um estilo.
*
* Pós-condição: retorna um ponteiro para a string da família da fonte, ou NULL se o estilo for nulo
*/
char* getFamily(const Estilo e);

/*
Retorna o peso da fonte (ex: "bold") associado a um estilo.
*
* Pós-condição: retorna um ponteiro para a string do peso da fonte,
* ou NULL se o estilo for nulo
*/
char* getWeight(const Estilo e);

/*
Retorna o tamanho da fonte (ex: "12px") associado a um estilo.
*
* Pós-condição: retorna um ponteiro para a string do tamanho da fonte,
* ou NULL se o estilo for nulo
*/
char* getSize(const Estilo e);

/*
Define uma nova família de fonte para um objeto de Estilo existente.

* family: nova string da família da fonte
*
* Pós-condição: a família da fonte do estilo é atualizada
*/
void setFamily(Estilo e, const char *family);

/*
Define um novo peso de fonte para um objeto de Estilo existente.

* weight: nova string do peso da fonte
*
* Pós-condição: o peso da fonte do estilo é atualizado
*/
void setWeight(Estilo e, const char *weight);

/*
Define um novo tamanho de fonte para um objeto de Estilo existente.

* size: nova string do tamanho da fonte
*
* Pós-condição: o tamanho da fonte do estilo é atualizado
*/
void setSize(Estilo e, const char *size);

//============================================================================================
/*                          FUNÇÕES DE CRIAÇÃO E DESTRUIÇÃO DE TEXTO                         */

/*
Cria e aloca memória para um novo objeto de Texto. O texto possui
propriedades de posicionamento, cor, conteúdo textual e um estilo associado.

* i: identificador único do texto
* x, y: coordenadas do ponto de âncora do texto
* corb: string da cor da borda do texto
* corp: string da cor de preenchimento do texto
* a: caractere da âncora ('i', 'm' ou 'f')
* conteudo: a string de texto a ser exibida
* estilo: um objeto de Estilo que define a aparência do texto
*
* Pré-condição: os parâmetros de ponteiro devem ser válidos
* Pós-condição: retorna um ponteiro opaco para o Texto criado,
* ou o programa é encerrado em caso de falha de alocação
*/
Texto criarTexto(int i, double x, double y, const char *corb, const char *corp, char a, const char *conteudo, Estilo estilo);


//============================================================================================
/*OBS:
* para as funcoes abaixo: 
*    t: ponteiro opaco para o texto a ser utilizado dependendo do contexto da funcao
* Pré-condição: t deve ser um ponteiro válido para Texto
*/

/*
Libera toda a memória associada a um objeto de Texto, incluindo a cópia
interna do seu estilo.
*
* Pós-condição: a memória alocada para o texto e suas propriedades é liberada
*/
void destroiTexto(Texto t);


/*                                              MÉTODOS GET (CONSULTA)                                                   */

/*
Retorna o identificador único do texto, permitindo distingui-lo de outros
elementos e possibilitando operações de busca e referência específica.
*
* Pós-condição: retorna o ID do texto como número inteiro,
* ou -1 se t for NULL, sem modificar o texto
*/
int getIdTexto(const Texto t);

/*
Retorna a coordenada X da posição do texto na arena, indicando sua
localização horizontal no plano cartesiano.
*
* Pós-condição: retorna a coordenada X como double,
* ou 0.0 se t for NULL, sem alterar o texto
*/
double getXTexto(const Texto t);

/*
Retorna a coordenada Y da posição do texto na arena, indicando sua
localização vertical no plano cartesiano. Complementa getXTexto para
determinar completamente a localização do texto.
* 
* Pós-condição: retorna a coordenada Y como double,
* ou 0.0 se t for NULL, sem modificar o texto
*/
double getYTexto(const Texto t);

/*
Retorna a cor da borda do texto.

*
* Pós-condição: retorna um ponteiro para a string da cor da borda,
* ou NULL se o texto for nulo
*/
char* getCorbTexto(const Texto t);

/*
Retorna a cor de preenchimento do texto.

* 
* Pós-condição: retorna um ponteiro para a string da cor de preenchimento,
* ou NULL se o texto for nulo
*/
char* getCorpTexto(const Texto t);

/*
Retorna o caractere de âncora do texto ('i', 'm' ou 'f').
*
* Pós-condição: retorna o caractere da âncora,
* ou '\0' se o texto for nulo
*/
char getAncora(const Texto t);

/*
Retorna o conteúdo textual do objeto.
* 
* Pós-condição: retorna um ponteiro para a string do conteúdo,
* ou NULL se o texto for nulo
*/
char* getTexto(const Texto t);

/*
Retorna o objeto de Estilo associado ao texto.
*
* Pós-condição: retorna um ponteiro opaco para o Estilo do texto,
* ou NULL se o texto for nulo
*/
Estilo getEstiloTexto(const Texto t);


/*                                               MÉTODOS SET (MODIFICAÇÃO)                                                     */

/*
Define uma nova coordenada X para o texto, reposicionando-o
horizontalmente na arena. Esta operação move o texto sem alterar
seu conteúdo, cor ou outras propriedades.

* x: nova coordenada X para a posição do texto
*
* Pós-condição: a coordenada X é atualizada para o novo valor,
* se t for NULL a função não faz nada
*/
void setXTexto(Texto t, double x);

/*
Define uma nova coordenada Y para o texto, reposicionando-o
verticalmente na arena. Complementa setXTexto para reposicionamento
completo no plano cartesiano.

* y: nova coordenada Y para a posição do texto
*
* Pós-condição: a coordenada Y é atualizada para o novo valor,
* se t for NULL a função não faz nada
*/
void setYTexto(Texto t, double y);

/*
Define uma nova cor de borda para o texto.

* corb: nova string da cor da borda
*
* Pós-condição: a cor da borda do texto é atualizada
*/
void setCorbTexto(Texto t, const char *corb);

/*
Define uma nova cor de preenchimento para o texto.

* corp: nova string da cor de preenchimento
*
* Pós-condição: a cor de preenchimento do texto é atualizada
*/
void setCorpTexto(Texto t, const char *corp);

/*
Define um novo caractere de âncora para o texto.

* a: novo caractere de âncora ('i', 'm' ou 'f')
*
* Pós-condição: a âncora do texto é atualizada
*/
void setAncora(Texto t, char a);

/*
Define um novo conteúdo textual para o objeto.

* conteudo: nova string de conteúdo
*
* Pós-condição: o conteúdo do texto é atualizado
*/
void setTexto(Texto t, const char *conteudo);

/*
Define um novo estilo para o texto. A função irá destruir o estilo antigo
e criar uma nova cópia do estilo fornecido para garantir o encapsulamento.

* estilo: o novo objeto de Estilo a ser aplicado
*
* Pré-condição: estilo deve ser um ponteiro válidos
* Pós-condição: o estilo do texto é substituído por uma cópia do novo estilo
*/
void setEstiloTexto(Texto t, Estilo estilo);


/*                                          FUNÇÕES DE RENDERIZAÇÃO                                  */

/*
Imprime a representação SVG do texto em um arquivo. Esta função gera
o código SVG necessário para visualizar o texto na posição especificada,
com as cores, âncora e estilo tipográfico definidos. A âncora é convertida
automaticamente para o formato SVG ('i'→"start", 'm'→"middle", 'f'→"end").

* arquivo: ponteiro para FILE aberto para escrita em modo SVG
*
* arquivo deve ser um FILE* válido aberto para escrita
* Pós-condição: código SVG do texto é escrito no arquivo no formato:
* <text x="..." y="..." fill="..." stroke="..." 
* text-anchor="..." font-family="..." 
* font-weight="..." font-size="...">conteudo</text>
* se t ou arquivo forem NULL a função não faz nada
*/
void imprimeTextoSVG(const Texto t, FILE *arquivo);

/*
Imprime informações detalhadas do texto em formato texto simples.
Esta função gera um relatório legível contendo ID, posição, cores,
âncora, conteúdo e propriedades do estilo tipográfico, útil para
debug e logs do jogo.

* arquivo: ponteiro para FILE aberto para escrita em modo texto
*
* arquivo deve ser um FILE* válido aberto para escrita
* Pós-condição: informações do texto são escritas no arquivo em formato legível,
* incluindo ID, posição, cores, âncora, conteúdo e estilo,
* se t ou arquivo forem NULL a função não faz nada
*/
void imprimeTextoTXT(const Texto t, FILE *arquivo);

#endif