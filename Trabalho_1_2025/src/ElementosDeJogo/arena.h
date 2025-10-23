#ifndef ARENA_H
#define ARENA_H

#include <stdio.h>
#include <stdbool.h>

#include "../EstruturaDeDados/fila.h"
#include "formas.h"
#include "chao.h"

/*_______________________ TIPO ABSTRATO DE DADOS: ARENA (PALCO PRINCIPAL) _______________________*/
/*
 * O módulo Arena representa o "cenário" principal do programa,
 * funcionando como um container para todas as formas ativas.
 *
 * - Limites Definidos: A arena é criada com uma largura e altura
 * específicas, que definem a área visível do cenário.
 *
 * - Armazenamento de Formas: As formas são armazenadas internamente,
 * prontas para serem processadas, desenhadas ou verificadas para colisões.
 *
 * - Gerenciamento de Memória: A Arena é responsável pelo ciclo de vida das
 * formas que armazena. Ao ser destruída com 'destroiArena', todas as formas
 * contidas nela também são liberadas da memória.
 *
 */

typedef void *Arena;


/*________________________________ FUNÇÕES DE CRIAÇÃO E DESTRUIÇÃO ________________________________*/

/*
 Cria e inicializa a estrutura de dados que representa a Arena.

 * largura: Define o limite horizontal (eixo X) da Arena.
 * altura: Define o limite vertical (eixo Y) da Arena.
 *
 * Pré-condição: Largura e altura devem ser valores positivos.
 * Pós-condição: Retorna um ponteiro para a estrutura Arena criada,
 * ou NULL em caso de falha de alocação de memória.
 */
Arena criaArena(double largura, double altura);

/*
 Libera a memória alocada para a Arena e, crucialmente, para TODAS as
 formas que ainda estiverem contidas nela no momento da chamada.

 * a: A Arena a ser destruída.
 *
 * Pré-condição: 'a' deve ser um ponteiro válido para uma Arena.
 * Pós-condição: A memória de 'a' e de todas as formas em seu interior
 * é completamente liberada.
 */
void destroiArena(Arena a);


/*________________________________ FUNÇÕES DE MANIPULAÇÃO DE FORMAS ________________________________*/

/*
 Insere uma nova forma na Arena. A Arena passa a ser "dona" da forma
 e será responsável por liberar sua memória quando for destruída.

 * a: A Arena onde a forma será inserida.
 * f: A Forma a ser adicionada.
 *
 * Pré-condição: 'a' e 'f' devem ser ponteiros válidos.
 * Pós-condição: A forma 'f' é adicionada ao conjunto de formas ativas na Arena.
 */
void insereFormaArena(Arena a, Forma f);

/*
  Remove e retorna a próxima forma da arena (fila), assim a primeira que foi inserida
   na arena será a primeira a ser retirada.

 * a: A Arena a ter a forma retirada.
 *
 * Pré-condição: 'a' deve ser um ponteiro válido para uma Arena.
 * Pós-condição: A memória da forma especifica é liberada.
 */
Forma removeFormaArena(Arena a);

/*
 Itera sobre todas as formas contidas na Arena e executa uma função para cada uma.
 Esta é uma forma segura e encapsulada de processar todos os elementos da Arena.

 * a: A Arena cujas formas serão iteradas.
 * executa: Ponteiro para uma função que será chamada para cada forma.
 * Esta função recebe a Forma e um dado auxiliar.
 * auxData: Ponteiro para dados extras que a função 'executa' possa precisar.
 *
 * Pré-condição: 'a' e 'executa' devem ser ponteiros válidos.
 * Pós-condição: A função 'executa' é aplicada a cada forma na Arena.
 */
void iteraFormasArena(const Arena a, void (*executa)(Forma f, void *auxData), void *auxData);


/*________________________________ PROCESSAMENTO DE INTERAÇÕES ________________________________*/

/**
 * Processa todas as interações entre formas na arena seguindo regras de colisão
 * 
 * Algoritmo:
 * 1. Enquanto houver pelo menos 2 formas na arena:
 *    - Remove duas formas (I e J) da arena na ordem FIFO
 *    - Verifica se há sobreposição entre elas
 * 
 * 2. Se NÃO há sobreposição:
 *    - Ambas as formas voltam ao chão na mesma ordem
 * 
 * 3. Se HÁ sobreposição e área(I) < área(J):
 *    - Forma I é ESMAGADA (destruída completamente)
 *    - Forma J volta sozinha ao chão
 *    - Incrementa contador de formas esmagadas
 *    - Adiciona área de I à pontuação total
 * 
 * 4. Se HÁ sobreposição e área(I) >= área(J):
 *    - Forma I modifica as cores de J:
 *      * Cor de borda de J = cor de preenchimento de I
 *      * Cor de preenchimento de J = cor de borda de I
 *    - Ordem de retorno ao chão: J, depois I, depois clone de I
 *    - Forma I é clonada com cores invertidas (borda↔preenchimento)
 *    - Incrementa contador de formas clonadas
 * 
 *  a:  Arena contendo as formas a serem processadas
 *  chao:  Chão onde as formas serão devolvidas após processamento
 *  arquivo_txt:  Arquivo para log das interações (pode ser NULL)
 *  formas_clonadas:  Ponteiro para contador de formas clonadas (pode ser NULL)
 *  formas_esmagadas: Ponteiro para contador de formas esmagadas (pode ser NULL)
 */
void processaInteracoesArena(Arena a, Chao chao, double *pontuacao_total, Queue anotacoes_svg, FILE *arquivo_txt, int *formas_clonadas, int *formas_esmagadas, void *repo);

/*___________________________ FUNÇÕES DE CONSULTA E MODIFICAÇÃO DE ATRIBUTOS ___________________________*/

/*
 Obtém a largura atual da Arena.

 * a: Ponteiro para a Arena.
 *
 * Pré-condição: 'a' deve ser um ponteiro válido.
 * Pós-condição: Retorna o valor da largura da Arena.
 */
double getArenaLargura(const Arena a);

/*
 Obtém a altura atual da Arena.

 * a: Ponteiro para a Arena.
 *
 * Pré-condição: 'a' deve ser um ponteiro válido.
 * Pós-condição: Retorna o valor da altura da Arena.
 */
double getArenaAltura(const Arena a);

/*
 Retorna a quantidade de formas atualmente ativas na Arena.

 * a: Ponteiro para a Arena.
 *
 * Pré-condição: 'a' deve ser um ponteiro válido.
 * Pós-condição: Retorna o número de formas contidas na Arena.
 */
int getArenaNumFormas(const Arena a);

/*
 Define uma nova largura para a Arena.

 * a: Ponteiro para a Arena a ser modificada.
 * novaLargura: O novo valor para a largura da Arena.
 *
 * Pré-condição: 'a' deve ser um ponteiro válido.
 * Pós-condição: A largura da Arena é atualizada.
 */
void setArenaLargura(Arena a, double novaLargura);

/*
 Define uma nova altura para a Arena.

 * a: Ponteiro para a Arena a ser modificada.
 * novaAltura: O novo valor para a altura da Arena.
 *
 * Pré-condição: 'a' deve ser um ponteiro válido.
 * Pós-condição: A altura da Arena é atualizada.
 */
void setArenaAltura(Arena a, double novaAltura);



#endif 