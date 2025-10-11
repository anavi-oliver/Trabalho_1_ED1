#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 TIPO ABSTRATO DE DADOS: FILA (QUEUE)

 Este módulo define a interface para manipulação de uma Fila,
 uma estrutura de dados baseada no princípio FIFO (First-In, First-Out).
 A Fila é essencial para o controle de processos e gerenciamento de tarefas.

 O TAD é implementado utilizando ponteiros opacos (void *), ocultando
 a representação interna da estrutura.
*/


/*
 Declarações de tipos para se criar e manipular uma fila

 Queue: definição do tipo vazio para fila.
 Item: dado genérico armazenado na fila.
*/
typedef void *Queue;
typedef void *Item;


/*
Cria uma nova fila vazia.
Queue Retorna um ponteiro opaco para a estrutura da Fila criada.
*/
Queue createQueue();


/* ========== MODELO DOS COMENTARIOS ==========
                    * Explicação do que a função representa
                    *
                    * Significado dos parametros
                    *
                    * Pré condição
                    * Pós condição 
*/



/*
  Insere um elemento no final da fila.

 q: ponteiro para a fila
 i: o item que sera enfileirado

 A fila não deve estar cheia 
 A fila conterá o novo elemento em seu final após este procedimento
*/
void enfileira(Queue q, Item i);

/*
Retira o elemento do início da fila.

 q: ponteiro para a fila

 A fila não deve estar vazia
 Como a fila é da política FIFO, o primeiro objeto a ser inserido na fila será o primeiro a ser removido.
*/
Item desenfileira(Queue q); 

/*
Retornar o elemento do início da fila

q: ponteiro para a fila

A fila não deve estar vazia
Retornará elemento que está no início da fila, ou seja, o primeiro a ser inserido.
*/
Item inicioFila(const Queue q);

/*
Retornar o elemento do final da fila

q: ponteiro para a fila

A fila não deve estar vazia
Retornará elemento que está no final da fila, ou seja, o último a ser inserido.
*/
Item fimFila(const Queue q);

/**
 Verifica se a Fila está vazia.

 q Ponteiro para a Fila

 A fila deve estar inicializada
 bool Retorna true se a Fila estiver vazia, false caso contrário.
 */
bool estaVaziaFila(const Queue q);

/*
NOVA FUNÇÃO ADICIONADA
Retorna o número de elementos atualmente na Fila.

 q: ponteiro para a fila

 A fila deve estar inicializada
 Retorna um inteiro representando a quantidade de itens na fila.
*/
int getTamanhoFila(const Queue q);

/*
Libera toda a memória alocada para a Fila.

 q Ponteiro para a Fila a ser destruída.

 O ponteiro para a Fila não deve ser nulo
 A memória da estrutura da Fila é liberada.
 */
void destroiFila(Queue q);


#endif