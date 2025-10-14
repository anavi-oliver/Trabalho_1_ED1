#ifndef PROCESSAQRY_H
#define PROCESSAQRY_H

#include "chao.h"
#include "disparador.h"
#include "carregador.h"
#include "arena.h"

/*_______________________ TIPO ABSTRATO DE DADOS: REPOSITÓRIO _______________________*/
/*
 * O Repositório é uma estrutura que centraliza o gerenciamento de todos os
 * Carregadores e Disparadores do sistema, permitindo acesso e manipulação
 * eficientes durante o processamento de comandos do arquivo .qry.
 */

typedef void *Repositorio;
typedef void *ReportTxt;


/*________________________________ FUNÇÕES DE CRIAÇÃO E DESTRUIÇÃO ________________________________*/

/*
 * Cria e inicializa a estrutura de dados que representa o Repositório.
 *
 * Pré-condição: Nenhuma.
 * Pós-condição: Retorna um ponteiro para a estrutura Repositório criada,
 * ou NULL em caso de falha de alocação de memória.
 */
Repositorio criaRepositorio();

/*
 * Libera a memória alocada para o Repositório e para todos os Carregadores
 * e Disparadores que ele contém. Não libera a memória do Chão ou da Arena,
 * pois estes são gerenciados externamente.
 *
 * repo: Ponteiro para o Repositório a ser destruído.
 *
 * Pré-condição: 'repo' deve ser um ponteiro válido.
 * Pós-condição: A memória de 'repo' e de todos os Carregadores e Disparadores
 * contidos é liberada.
 */
void destroiRepositorio(Repositorio repo);

/*________________________________ FUNÇÃO PRINCIPAL DE PROCESSAMENTO ________________________________*/

/*
 * Processa o arquivo .qry, executando comandos que manipulam a Arena, o Chão,
 * os Carregadores e os Disparadores, e gerando relatórios no arquivo .txt.
 * A pontuação total é atualizada com base nas operações realizadas.
 *
 * nome_path_qry: Caminho para o arquivo .qry contendo os comandos.
 * nome_txt: Caminho para o arquivo .txt onde os relatórios serão gravados.
 * arena: Ponteiro para a Arena onde as formas são inseridas.
 * chao: Ponteiro para o Chão que armazena as formas iniciais.
 * pontuacao_total: Ponteiro para a variável que acumula a pontuação total.
 *
 * Pré-condição: 'nome_path_qry', 'nome_txt', 'arena' e 'chao' devem ser válidos;
 *               'pontuacao_total' deve ser um ponteiro para uma variável double inicializada.
 * Pós-condição: Os comandos do arquivo .qry são executados, os relatórios são
 *               gerados no arquivo .txt, e a pontuação total é atualizada.
 */
void processaQry(const char *nome_path_qry, const char *nome_txt, Arena arena, Chao chao, double *pontuacao_total);

#endif