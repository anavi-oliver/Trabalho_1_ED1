#ifndef CIRCULO_H
#define CIRCULO_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
O módulo CIRCULO.H é responsável por gerenciar a forma geométrica de um
círculo como um Tipo Abstrato de Dados (TAD).
O tipo opaco Circulo (typedef void*) esconde a representação interna da estrutura,
que inclui ID, coordenadas do centro, raio, cores de borda e preenchimento,
além de flags opcionais (disparo e seleção N).
*/

typedef void *Circulo;

//                  FUNÇÕES DE CRIAÇÃO E DESTRUIÇÃO 

/*
Cria um novo círculo com os parâmetros especificados.

i: identificador do círculo
x, y: coordenadas do centro
r: raio do círculo
corb: cor da borda
corp: cor de preenchimento
disp: flag de disparo
n: identificador de seleção

Pré-condição: raio deve ser maior que 0
Pós-condição: retorna um ponteiro para o círculo criado
*/
Circulo criarCirculo(int i, double x, double y, double r, char *corb, char *corp, bool disp, int n);

/*
Libera a memória alocada para o círculo.

c: ponteiro para o círculo

Pré-condição: o círculo deve ser válido
Pós-condição: memória liberada
*/
void destroiCirculo(Circulo c);

// =============== MÉTODOS GET (CONSULTA) ===============

int getICirculo(Circulo c);           // Retorna o identificador do círculo
double getXCirculo(Circulo c);        // Retorna a coordenada X do centro
double getYCirculo(Circulo c);        // Retorna a coordenada Y do centro
double getRCirculo(Circulo c);        // Retorna o raio
char* getCorbCirculo(Circulo c);      // Retorna a cor da borda
char* getCorpCirculo(Circulo c);      // Retorna a cor de preenchimento
double getSWCirculo(Circulo c);       // Retorna a largura do traço (stroke-width)
bool getDispCirculo(Circulo c);       // Retorna a flag de disparo
int getNCirculo(Circulo c);           // Retorna o identificador de seleção n

// =============== MÉTODOS SET (MODIFICAÇÃO) ===============

void setICirculo(Circulo c, int i);
void setXCirculo(Circulo c, double x);
void setYCirculo(Circulo c, double y);
void setRCirculo(Circulo c, double r);      // Pré-condição: r > 0
void setCorbCirculo(Circulo c, char* corb);
void setCorpCirculo(Circulo c, char* corp);
void setSWCirculo(Circulo c, double sw);    // Pré-condição: sw >= 0
void setDispCirculo(Circulo c, bool disp);
void setNCirculo(Circulo c, int n);

// =============== FUNÇÕES GEOMÉTRICAS ===============

/*
Calcula a área do círculo.

c: ponteiro para o círculo

Pré-condição: círculo deve ser válido
Pós-condição: retorna a área (π * r²)
*/
double calculaAreaCirculo(Circulo c);

/*
Calcula o perímetro do círculo.

c: ponteiro para o círculo

Pré-condição: círculo deve ser válido
Pós-condição: retorna o perímetro (2 * π * r)
*/
double calculaPerimetroCirculo(Circulo c);

/*
Verifica se um ponto está dentro do círculo.

c: ponteiro para o círculo
px, py: coordenadas do ponto

Pré-condição: círculo deve ser válido
Pós-condição: retorna true se o ponto estiver dentro
*/
bool pontoNoCirculo(Circulo c, double px, double py);

/*
Verifica se dois círculos se intersectam.

c1, c2: ponteiros para os círculos

Pré-condição: círculos devem ser válidos
Pós-condição: retorna true se houver interseção
*/
bool circulosIntersectam(Circulo c1, Circulo c2);

#endif