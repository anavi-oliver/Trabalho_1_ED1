#ifndef PILHA_H
#define PILHA_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 TIPO ABSTRATO DE DADOS: PILHA (STACK)

 Este módulo define a interface para manipulação de uma Pilha,
 uma estrutura de dados baseada no princípio LIFO (Last-In, First-Out).
 A Pilha é essencial para o funcionamento dos carregadores (Launchers).

 O TAD é implementado utilizando ponteiros opacos (void *), ocultando
 a representação interna da estrutura.
*/


/*
 Declarações de tipos para se criar e manipular uma pilha

 Stack: definição do tipo vazio para pilha.
 Item: dado genérico armazenado na pilha.
*/

typedef void *Stack;     
typedef void *Item;      


/*
Cria uma nova pilha vazia.
Pilha Retorna um ponteiro opaco para a estrutura da Pilha criada.
*/
Stack createStk();


    /** ============= Modelo para comentários das funções: =============
                    * Explicação do que a função representa
                    *
                    * Significado dos parametros
                    *
                    * Pré condição
                    * Pós condição 
    */



/*
 Insere um elemento no topo da pilha.

 p: ponteiro para a pilha
 i: o item que sera empilhado

 A pilha não deve estar cheia 
 A pilha conterá o novo elemento em seu topo após este procedimento
 */
void empilha(Stack p, Item i);

/*
Retira o elemento no topo da pilha.

 p: ponteiro para a pilha
 i: o item que sera empilhado

 A pilha não deve estar vazia
 Como a pilha é da política LIFO, o primeiro objeto a ser inserido na pilha será o último a ser removido.
*/
Item desempilha(Stack p);   

/*
Retornar o elemento do topo da pilha

p: ponteiro para a pilha

A pilha não deve estar vazia
Retornará elemento que está no topo da pilha, ou seja, o último a ser inserido.
*/
Item topoPilha (Stack p);

/**
 Verifica se a Pilha está vazia.

 p Ponteiro para a Pilha

 A pilha deve estar vazia
 bool Retorna true se a Pilha estiver vazia, false caso contrário.
 */
bool estaVaziaPilha(Stack p);

/*
Libera toda a memória alocada para a Pilha.

 p Ponteiro para a Pilha a ser destruída.

 O ponteiro para a Pilha não deve ser nulo
 A memória da estrutura da Pilha é liberada.
 */
void destroiPilha(Stack p);


#endif

