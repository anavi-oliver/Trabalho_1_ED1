#ifndef CARREGADOR_H
#define CARREGADOR_H

#include <stdbool.h>
#include <stdio.h>
#include "chao.h"
#include "formas.h"
#include "fila.h"

/*_______________________ TIPO ABSTRATO DE DADOS: CARREGADOR DE FORMAS _______________________*/
/*
 * O módulo Carregador funciona como um depósito ou "pente de munição" para
 * as formas geométricas. Sua principal função é retirar formas do 'Chão',
 * que atua como um repositório geral, e armazená-las para uso posterior.
 *
 * - Como funciona: As formas são retiradas do Chão e enfileiradas
 * dentro do Carregador, seguindo uma política FIFO (o primeiro
 * que entra é o primeiro que sai).
 */

typedef struct Carregador_t *Carregador;


/*________________________________ FUNÇÕES DE CRIAÇÃO E DESTRUIÇÃO ________________________________*/

/*
 Cria e inicializa a estrutura de dados que representa um Carregador.

 * id: Identificador numérico único para este Carregador.
 *
 * Pré-condição: Nenhuma.
 * Pós-condição: Retorna um ponteiro para a estrutura Carregador criada,
 * ou NULL em caso de falha de alocação de memória.
 */
Carregador criaCarregador(int id);

/*
 Libera a memória alocada para a estrutura do Carregador. Esta função
 também libera a memória da fila interna do Carregador, mas é crucial
 notar que ela **NÃO** libera a memória das formas contidas nele.

 * c: O Carregador a ser destruído.
 *
 * Pré-condição: 'c' deve ser um ponteiro válido.
 * Pós-condição: A memória de 'c' e de sua estrutura interna é liberada.
 */
void destroiCarregador(Carregador c);


/*________________________________ FUNÇÕES DE MANIPULAÇÃO ________________________________*/

/*
 Transfere uma quantidade 'n' de formas do Chão para o Carregador. As formas
 são removidas do Chão e adicionadas ao final da fila do Carregador.

 * carregadorAlvo: O Carregador que receberá as formas.
 * chaoOrigem: O Chão de onde as formas serão retiradas.
 * n: A quantidade de formas a serem carregadas.
 *
 * Pré-condição: 'carregadorAlvo' e 'chaoOrigem' devem ser ponteiros válidos.
 * Pós-condição: 'n' formas (ou menos, se o Chão não tiver 'n' formas)
 * são movidas do Chão para o Carregador.
 */
void carregaFormasDoChao(Carregador carregadorAlvo, Chao chaoOrigem, int n);

/*
 Remove e retorna a próxima forma na fila do Carregador (comportamento FIFO).

 * c: O Carregador de onde a forma será removida.
 *
 * Pré-condição: 'c' deve ser um ponteiro válido e não pode estar vazio.
 * Pós-condição: Retorna a primeira Forma da fila. Se o Carregador
 * estiver vazio, retorna NULL.
 */
Forma descarregaForma(Carregador c);


/*________________________________ FUNÇÕES GET ________________________________*/

/*
OBS: uso de const
        const usado por se tratar de uma ferramenta simples e eficaz em C para evitar bugs, 
        deixar suas intenções claras e escrever código mais robusto e de fácil manutenção.
        Agindo assim, como um guarda contra bugs acidentais ou perigosos, que as vezes pudessem passar despercebido.
*/
/*
 Obtém o identificador único (ID) do Carregador.

 * c: Ponteiro para o Carregador.
 *
 * Pré-condição: 'c' deve ser um ponteiro válido.
 * Pós-condição: Retorna o valor do ID do Carregador.
 */
int getCarregadorId(const Carregador c);

/*
 Retorna a quantidade de formas atualmente armazenadas no Carregador.

 * c: Ponteiro para o Carregador.
 *
 * Pré-condição: 'c' deve ser um ponteiro válido.
 * Pós-condição: Retorna o número de formas contidas no Carregador.
 */
int getCarregadorTamanho(const Carregador c);

/*
 Verifica se o Carregador não contém nenhuma forma.

 * c: Ponteiro para o Carregador a ser verificado.
 *
 * Pré-condição: 'c' deve ser um ponteiro válido.
 * Pós-condição: Retorna 'true' se o Carregador estiver vazio, 'false' caso contrário.
 */
bool carregadorEstaVazio(const Carregador c);

/*
 Insere uma forma diretamente no Carregador (no final da fila).
 
 * c: O Carregador que receberá a forma.
 * f: A Forma a ser inserida.
 
 * Pré-condição: 'c' e 'f' devem ser válidos.
 * Pós-condição: A forma é adicionada ao final do Carregador.
 */
void insereFormaCarregador(Carregador c, Forma f);

#endif 