#ifndef DISPARADOR_H
#define DISPARADOR_H

#include <stdbool.h>
#include "formas.h"
#include "carregador.h"
#include "arena.h"



/*_______________________ TIPO ABSTRATO DE DADOS: DISPARADOR _______________________*/
/*
 * O Disparador é a entidade responsável por pegar as formas dos carregadores
 * e projetá-las na Arena. Ele funciona como uma "arma" no cenário.
 *
 * - Posição: Possui uma âncora (x,y) que define a origem dos disparos.
 *
 * - Munição: Conecta-se a dois Carregadores (esquerdo e direito), que
 * servem como sua fonte de munição (Formas).
 *
 * - Posição de Disparo: Armazena uma única Forma que está pronta para ser
 * disparada. Esta posição é preenchida pela função 'preparaDisparo' e
 * esvaziada pela função 'dispara'.
 *
 * - Gerenciamento de Memória: O Disparador NÃO é dono dos Carregadores
 * que utiliza, mas é responsável pela memória da Forma que estiver em sua
 * posição de disparo.
 */

typedef struct Disparador_t *Disparador;


/*________________________________ FUNÇÕES DE CRIAÇÃO E DESTRUIÇÃO ________________________________*/

/*
 Cria e inicializa a estrutura de dados que representa um Disparador.

 * id: Identificador numérico único para este Disparador.
 * x: Coordenada X inicial da âncora do Disparador.
 * y: Coordenada Y inicial da âncora do Disparador.
 * esq: Ponteiro para o Carregador que será usado no lado esquerdo.
 * dir: Ponteiro para o Carregador que será usado no lado direito.
 *
 * Pré-condição: Os Carregadores 'esq' and 'dir' devem ser válidos.
 * Pós-condição: Retorna um ponteiro para a estrutura Disparador criada,
 * ou NULL em caso de falha de alocação de memória.
 */
Disparador criaDisparador(int id, double x, double y, Carregador esq, Carregador dir);

/*
 Libera a memória alocada para o Disparador. Esta função NÃO libera a
 memória dos Carregadores associados a ele, mas libera a memória de
 qualquer Forma que tenha ficado na posição de disparo sem ser disparada.

 * d: O Disparador a ser destruído.
 *
 * Pré-condição: 'd' deve ser um ponteiro válido.
 * Pós-condição: A memória de 'd' e da forma em sua posse é liberada.
 */
void destroiDisparador(Disparador d);


/*________________________________ FUNÇÕES DE CONSULTA (GETTERS) ________________________________*/

/*
 Obtém o identificador único (ID) do Disparador.

 * d: Ponteiro para o Disparador.
 *
 * Pré-condição: 'd' deve ser um ponteiro válido.
 * Pós-condição: Retorna o valor do ID do Disparador.
 */
int getDisparadorId(const Disparador d);

/*
 Obtém a coordenada X da âncora do Disparador.

 * d: Ponteiro para o Disparador.
 *
 * Pré-condição: 'd' deve ser um ponteiro válido.
 * Pós-condição: Retorna a coordenada X do Disparador.
 */
double getDisparadorX(const Disparador d);

/*
 Obtém a coordenada Y da âncora do Disparador.

 * d: Ponteiro para o Disparador.
 *
 * Pré-condição: 'd' deve ser um ponteiro válido.
 * Pós-condição: Retorna a coordenada Y do Disparador.
 */
double getDisparadorY(const Disparador d);

/*
 Obtém um ponteiro para a Forma que está atualmente na posição de disparo.

 * d: Ponteiro para o Disparador.
 *
 * Pré-condição: 'd' deve ser um ponteiro válido.
 * Pós-condição: Retorna a Forma pronta para disparo, ou NULL se não houver nenhuma.
 */
Forma getDisparadorFormaPronta(const Disparador d);


/*________________________________ FUNÇÕES DE MODIFICAÇÃO (SETTERS) ________________________________*/

/*
 Define a posição (coordenadas X e Y) da âncora do Disparador.

 * d: Ponteiro para o Disparador a ser modificado.
 * x: Nova coordenada X.
 * y: Nova coordenada Y.
 *
 * Pré-condição: 'd' deve ser um ponteiro válido.
 * Pós-condição: A posição do Disparador é atualizada.
 */
void setDisparadorPosicao(Disparador d, double x, double y);


/*_______________________________________ AÇÕES PRINCIPAIS _______________________________________*/

/*
 Move uma Forma do Carregador selecionado para a posição de disparo.
 Se já houver uma Forma na posição, ela é movida para o topo do Carregador oposto.

 * d: O Disparador que executará a ação.
 * lado: O Carregador de origem ('E' para esquerdo, 'D' para direito).
 * n: O número de vezes que a operação é repetida (para "ciclar" as formas).
 *
 * Pré-condição: 'd' deve ser um ponteiro válido; 'lado' deve ser 'E' ou 'D'.
 * Pós-condição: A Forma na posição de disparo é atualizada.
 */
void preparaDisparo(Disparador d, char lado, int n);

/*
 Dispara a Forma que está na posição de disparo. A função remove a Forma do
 Disparador, ajusta sua posição final com base na âncora do Disparador e
 nos deslocamentos (dx, dy), e a retorna.

 * d: O Disparador que efetuará o disparo.
 * dx: O deslocamento no eixo X a partir da âncora do Disparador.
 * dy: O deslocamento no eixo Y a partir da âncora do Disparador.
 *
 * Pré-condição: Deve haver uma Forma na posição de disparo.
 * Pós-condição: Retorna a Forma disparada, com suas coordenadas atualizadas.
 * O Disparador não terá mais uma forma pronta. A responsabilidade pela
 * memória da Forma retornada é transferida para quem chamou a função.
 */
Forma dispara(Disparador d, double dx, double dy);


#endif 