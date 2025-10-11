#ifndef CHAO_H
#define CHAO_H

#include <stdio.h>
#include <stdbool.h>
#include "formas.h"

/*_______________________ TIPO ABSTRATO DE DADOS: CHÃO (REPOSITÓRIO DE FORMAS) _______________________*/
/*
* O módulo Chão funciona como um repositório ou "inventário" para as
* formas que foram criadas mas ainda não estão ativas no jogo (ou seja,
* não foram inseridas em um carregador ou disparadas na arena).
*
* - Armazenamento Inicial: Serve como o local de armazenamento para
* todas as formas lidas do arquivo .geo.
*
* - Fila de Munição: Atua como uma fonte FIFO (o primeiro que entra
* é o primeiro que sai), de onde as formas são retiradas para
* municiar os carregadores.
*
* - A definição completa da struct está encapsulada no arquivo chao.c.
*/

typedef struct Chao_t *Chao;


/*________________________________ FUNÇÕES DE CRIAÇÃO E DESTRUIÇÃO ________________________________*/
/*
Cria e inicializa a estrutura de dados que representa o Chão.

*
* Pré-condição: Nenhuma.
* Pós-condição: Retorna um ponteiro para a estrutura Chao criada,
* ou NULL em caso de falha de alocação.
*/
Chao criaChao();

/*
Destrói a estrutura do Chão, liberando sua memória. Crucialmente, esta
função também é responsável por destruir TODAS as formas que ainda
estiverem contidas no Chão no momento da chamada.

* c: Ponteiro para o Chão a ser destruído.
*
* Pré-condição: 'c' deve ser um ponteiro válido.
* Pós-condição: A memória de 'c' e de todas as formas restantes dentro
* dele é liberada.
*/
void destroiChao(Chao c);


/*________________________________ FUNÇÕES DE MANIPULAÇÃO ________________________________*/
/*
Insere uma forma no final da fila do Chão.

* c: Ponteiro para o Chão onde a forma será inserida.
* f: A forma a ser adicionada.
*
* Pré-condição: 'c' e 'f' devem ser ponteiros válidos.
* Pós-condição: A forma 'f' é adicionada ao final da estrutura.
*/
void adicionaFormaChao(Chao c, Forma f);

/*
Remove e retorna a primeira forma da fila do Chão (comportamento FIFO).

* c: Ponteiro para o Chão de onde a forma será removida.
*
* Pré-condição: 'c' deve ser um ponteiro válido e não pode estar vazio.
* Pós-condição: Retorna a primeira forma da fila, ou NULL se o Chão
* estiver vazio.
*/
Forma removeFormaChao(Chao c);


/*________________________________ FUNÇÕES DE CONSULTA ________________________________*/
/*
Verifica se o Chão não contém nenhuma forma.

* c: Ponteiro para o Chão a ser verificado.
*
* Pré-condição: 'c' deve ser um ponteiro válido.
* Pós-condição: Retorna 'true' se o Chão estiver vazio, 'false' caso contrário.
*/
bool chaoEstaVazio(const Chao c);

/*
Retorna a quantidade de formas atualmente armazenadas no Chão.

* c: Ponteiro para o Chão.
*
* Pré-condição: 'c' deve ser um ponteiro válido.
* Pós-condição: Retorna o número de formas contidas no Chão.
*/
int getChaoTamanho(const Chao c);

#endif