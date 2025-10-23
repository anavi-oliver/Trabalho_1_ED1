#ifndef FORMAS_H
#define FORMAS_H

#include <stdio.h>
#include <stdbool.h> 

#include "circulo.h"
#include "linha.h"
#include "retangulo.h"
#include "texto.h"

/*_______________________ TIPO ABSTRATO DE DADOS: FORMAS GEOMÉTRICAS _______________________*/
/*
* Este módulo define uma interface genérica para manipular diferentes
* tipos de objetos geométricos (círculos, retângulos, etc.) de forma
* uniforme. A 'Forma' genérica funciona como um container que armazena
* atributos comuns a todas as formas e aponta para os dados específicos.
*
* - A definição completa da struct está encapsulada no arquivo .c
*/

typedef enum {
    TIPO_CIRCULO,
    TIPO_RETANGULO,
    TIPO_LINHA,
    TIPO_TEXTO
} TipoForma;

// Este ponteiro apontará para uma struct que contém o ID, o Tipo e os dados específicos (void*).
typedef void *Forma;


/*________________________________ FUNÇÕES DE CRIAÇÃO E DESTRUIÇÃO ________________________________*/
/*
Cria e encapsula uma forma geométrica. A camada genérica armazena o ID e o tipo,
e aponta para a forma específica que contém os demais dados.

* id: Identificador numérico único para esta forma.
* tipo: O tipo da forma (ex: TIPO_CIRCULO, TIPO_RETANGULO).
* dados_especificos: Ponteiro para a forma específica já alocada (ex: um Circulo, um Texto).
*
* Pré-condição: 'dados_especificos' deve ser um ponteiro válido para uma forma criada.
* Pós-condição: Retorna um ponteiro para a estrutura Forma que encapsula os dados.
*/
Forma criaForma(int id, TipoForma tipo, void *dados_especificos);

/*
Libera a memória alocada para a forma genérica e também para a forma
específica contida nela.

* f: A forma a ser destruída.
*
* Pré-condição: 'f' deve ser um ponteiro válido.
* Pós-condição: A memória de 'f' e de seus dados internos é liberada.
*/
void destroiForma(Forma f);


/*________________________________ FUNÇÕES DE CONSULTA (GETTERS) ________________________________*/
/*
Obtém o identificador único (ID) da forma.

* f: Ponteiro para a forma.
*
* Pré-condição: 'f' deve ser um ponteiro válido.
* Pós-condição: Retorna o valor do ID.
*/
int getFormaId(const Forma f);

/*
Obtém o tipo da forma (enum).

* f: Ponteiro para a forma.
*
* Pré-condição: 'f' deve ser um ponteiro válido.
* Pós-condição: Retorna o enum correspondente ao tipo da forma.
*/
TipoForma getFormaTipo(const Forma f);

/*
Obtém a coordenada X da âncora da forma.

* f: Ponteiro para a forma.
*
* Pré-condição: 'f' deve ser um ponteiro válido.
* Pós-condição: Retorna a coordenada X como double.
*/
double getFormaX(const Forma f);

/*
Obtém a coordenada Y da âncora da forma.

* f: Ponteiro para a forma.
*
* Pré-condição: 'f' deve ser um ponteiro válido.
* Pós-condição: Retorna a coordenada Y como double.
*/
double getFormaY(const Forma f);

/*
Obtém a cor da borda da forma.

* f: Ponteiro para a forma.
*
* Pré-condição: 'f' deve ser um ponteiro válido.
* Pós-condição: Retorna um ponteiro para a string da cor de borda.
*/
char *getFormaCorBorda(const Forma f);

/*
Obtém a cor de preenchimento da forma.

* f: Ponteiro para a forma.
*
* Pré-condição: 'f' deve ser um ponteiro válido.
* Pós-condição: Retorna um ponteiro para a string da cor de preenchimento.
*/
char *getFormaCorPreenchimento(const Forma f);


/*
Obtém o ponteiro para os dados específicos da forma (o objeto Circulo, Retangulo, etc.).

* f: Ponteiro para a forma.
*
* Pré-condição: 'f' deve ser um ponteiro válido.
* Pós-condição: Retorna o ponteiro void* para os dados específicos.
*/
void* getFormaAssoc(const Forma f);

/*
Obtem a área da forma

* f: Ponteiro para a forma.
*
* Pré-condição: 'f' deve ser um ponteiro válido.
* Pós-condição: Retorna o valor da área da forma como double.
*/
double getFormaArea(const Forma f);


/*________________________________ FUNÇÕES DE MODIFICAÇÃO (SETTERS) ________________________________*/
/*
Define a posição (coordenadas X e Y) da forma.

* f: Ponteiro para a forma a ser modificada.
* x: Nova coordenada X.
* y: Nova coordenada Y.
*
* Pré-condição: 'f' deve ser um ponteiro válido.
* Pós-condição: A posição da forma é atualizada.
*/
void setFormaPosicao(Forma f, double x, double y);

/*
Define a cor de borda da forma.

* f: Ponteiro para a forma a ser modificada.
* corBorda: Nova cor de borda.
*
* Pré-condição: 'f' deve ser um ponteiro válido.
* Pós-condição: A cor de borda da forma é atualizada.
*/
void setFormaCorBorda(Forma f, const char *corBorda);

/*
Define a cor de preenchimento da forma.

* f: Ponteiro para a forma a ser modificada.
* corPreenchimento: Nova cor de preenchimento.
*
* Pré-condição: 'f' deve ser um ponteiro válido.
* Pós-condição: A cor de preenchimento da forma é atualizada.
*/
void setFormaCorPreenchimento(Forma f, const char *corPreenchimento);


/*________________________________ FUNÇÕES DE RENDERIZAÇÃO ________________________________*/
/*
Desenha a representação SVG da forma em um arquivo.

* f: Ponteiro para a forma a ser desenhada.
* arquivoSvg: Ponteiro para o arquivo SVG aberto para escrita.
*
* Pré-condição: 'f' e 'arquivoSvg' devem ser ponteiros válidos.
* Pós-condição: O código SVG correspondente à forma é escrito no arquivo.
*/
void desenhaForma(const Forma f, FILE *arquivoSvg);

#endif