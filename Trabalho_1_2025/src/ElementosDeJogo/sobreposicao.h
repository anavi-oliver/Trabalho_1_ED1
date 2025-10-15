#ifndef SOBREPOSICAO_H
#define SOBREPOSICAO_H

#include <stdbool.h>

#include "formas.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

/*
*        MÓDULO DE SOBREPOSIÇÃO DE FORMAS
*
*        Este módulo verifica se existe sobreposição (interseção) entre
*        diferentes tipos de formas geométricas no plano cartesiano.
*
*        Contém uma função mestre que identifica os tipos das formas
*        e delega para funções especialistas a verificação específica.
*/


/*                    FUNÇÃO MESTRE                    */
/*
Verifica se duas formas genéricas se sobrepõem no plano.
Esta função identifica os tipos das formas e chama a função
especialista apropriada para realizar a verificação.

f1, f2: ponteiros para as formas a serem verificadas

Pré-condição: f1 e f2 devem ser ponteiros válidos
Pós-condição: retorna true se há sobreposição, false caso contrário
*/
bool formasSobrepoem(Forma f1, Forma f2);


/*                    FUNÇÕES ESPECIALISTAS DE SOBREPOSIÇÃO                    */

// Verifica sobreposição entre dois círculos
bool sobreposicaoCirculoCirculo(Circulo c1, Circulo c2);

// Verifica sobreposição entre círculo e retângulo
bool sobreposicaoCirculoRetangulo(Circulo c, Retangulo r);

// Verifica sobreposição entre círculo e linha
bool sobreposicaoCirculoLinha(Circulo c, Linha l);

// Verifica sobreposição entre círculo e texto
bool sobreposicaoCirculoTexto(Circulo c, Texto t);

// Verifica sobreposição entre dois retângulos
bool sobreposicaoRetanguloRetangulo(Retangulo r1, Retangulo r2);

// Verifica sobreposição entre retângulo e linha
bool sobreposicaoRetanguloLinha(Retangulo r, Linha l);

// Verifica sobreposição entre retângulo e texto
bool sobreposicaoRetanguloTexto(Retangulo r, Texto t);

// Verifica sobreposição entre duas linhas
bool sobreposicaoLinhaLinha(Linha l1, Linha l2);

// Verifica sobreposição entre linha e texto
bool sobreposicaoLinhaTexto(Linha l, Texto t);

// Verifica sobreposição entre dois textos
bool sobreposicaoTextoTexto(Texto t1, Texto t2);


/*                    FUNÇÕES AUXILIARES                    */
/*
Converte um texto em uma linha para facilitar cálculos de sobreposição.

O texto é considerado como um segmento com base na sua âncora:
    - 'i' (início): x1=xt, x2 = xt+comprimento
    - 'f' (fim): x1 = xt-comprimento, x2=xt
    - 'm' (meio): x1 =xt-comprimento/2, x2 = xt+comprimento / 2comprimento = 10.0 * número_caracteres

t: ponteiro para o texto
x1, y1, x2, y2: ponteiros para armazenar as coordenadas do segmento

Pré-condição: t deve ser válido, ponteiros de coordenadas não nulos
Pós-condição: coordenadas do segmento são preenchidas
*/
void converterTextoParaLinha(Texto t, double *x1, double *y1, double *x2, double *y2);

/*
Calcula a orientação de três pontos ordenados (p, q, r).
Usa o produto vetorial para determinar se os pontos formam
uma curva no sentido horário, anti-horário ou são colineares.

px, py: coordenadas do ponto p
qx, qy: coordenadas do ponto q
rx, ry: coordenadas do ponto r

Retorna: 0 se colineares, 1 se horário, 2 se anti-horário
*/
int orientacao(double px, double py, double qx, double qy, double rx, double ry);

/*
Verifica se um ponto q está no segmento de reta pr.
Assume que os três pontos são colineares.

px, py: coordenadas do ponto p (extremidade do segmento)
qx, qy: coordenadas do ponto q (ponto a verificar)
rx, ry: coordenadas do ponto r (outra extremidade)

Retorna: true se q está no segmento pr, false caso contrário
*/
bool pontoNoSegmento(double px, double py, double qx, double qy, double rx, double ry);

/*
Calcula a área de uma forma genérica.
Para textos: 20.0 * número_caracteres
Para linhas: 2.0 * comprimento_da_linha
Para círculos e retângulos: usa funções específicas dos TADs

f: ponteiro para a forma

Pré-condição: f deve ser válido
Pós-condição: retorna a área calculada
*/
double calculaAreaForma(Forma f);

#endif