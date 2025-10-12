#include "disparador.h"
#include "formas.h"
#include "carregador.h"
#include "arena.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
    Para o Disparador é necessário: 
    um tipo com implementacao oculta, criar disparador, destruir disparador, 
    mover do carregador para o disparador/ atirar forma do carregador, pegar posicao x e y dele, 
    pegar a ultima forma a ser disparada. SET vai ser so a posicao da ancora. 

*/

/*_______________________ TIPO ABSTRATO DE DADOS: DISPARADOR _______________________*/
typedef struct Disparador_t *Disparador;


/*________________________________ FUNÇÕES DE CRIAÇÃO E DESTRUIÇÃO ________________________________*/
Disparador criaDisparador(int id, double x, double y, Carregador esq, Carregador dir);

void destroiDisparador(Disparador d);


/*________________________________ FUNÇÕES DE CONSULTA (GETTERS) ________________________________*/
int getDisparadorId(const Disparador d);

double getDisparadorX(const Disparador d);


double getDisparadorY(const Disparador d);


Forma getDisparadorFormaPronta(const Disparador d);


/*________________________________ FUNÇÕES DE MODIFICAÇÃO (SETTERS) ________________________________*/
void setDisparadorPosicao(Disparador d, double x, double y);


/*_______________________________________ AÇÕES PRINCIPAIS _______________________________________*/
void preparaDisparo(Disparador d, char lado, int n);

Forma dispara(Disparador d, double dx, double dy);

