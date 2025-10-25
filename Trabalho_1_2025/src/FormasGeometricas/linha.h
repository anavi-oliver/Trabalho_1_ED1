#ifndef LINHA_H
#define LINHA_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
*        TIPO ABSTRATO DE DADOS: LINHA
*
*        Este módulo define a interface para manipulação de uma linha como
*        Tipo Abstrato de Dados (TAD).  
*        A representação interna (ID, coordenadas, cor etc.) é escondida
*        por um ponteiro opaco (typedef void*).
*/

typedef void *Linha;   // Ponteiro genérico para a linha

/*              FUNÇÕES DE CRIAÇÃO E DESTRUIÇÃO */

/*
Esta função é responsável por criar e inicializar uma nova linha na memória.

A linha criada terá um identificador único para diferenciá-la de outros
elementos, será posicionada pelas coordenadas especificadas do plano cartesiano
definindo seus pontos inicial e final. As características visuais incluem
a cor do traço, permitindo customização completa da aparência.

A linha possui funcionalidades especiais:
uma flag de disparo que pode ser utilizada para controlar eventos ou
animações, e um identificador de seleção que facilita operações de
agrupamento ou filtragem de linhas.

*        i : identificador único da linha para referência posterior
*        x1,y1 : coordenadas do ponto inicial da linha no sistema cartesiano  
*        x2,y2 : coordenadas do ponto final da linha no sistema cartesiano  
*        cor: string representando a cor do traço da linha
*        disp: flag booleana indicando se a linha foi disparada/ativada
*        n : identificador numérico adicional para seleção ou agrupamento
*
*       Pré-condição: coordenadas válidas para formar uma linha
*       Pós-condição: retorna um ponteiro opaco para a estrutura da linha criada ou NULL em caso de falha na alocação de memória

*/
Linha criarLinha(int i, double x1, double y1, double x2, double y2, char *cor, bool disp, int n);

/*
 Libera a memória alocada para a linha.

 l : ponteiro para a linha

 Pré-condição : l deve ser válido
 Pós-condição : memória liberada.
*/
void destroiLinha(Linha l);


/*              MÉTODOS GET (CONSULTA) */
/*
*   funções de CONSULTA que permitem ACESSAR (ler) o valor de um campo
*   específico da estrutura sem modificá-lo.
*   Características: não modificam o objeto, apenas retornam valores. */

//l: ponteiro opaco para a linha a ser consultada, que precisa ser válido e nao NULL

/*
Retorna a coordenada X do ponto inicial da linha, sem modificar a linha.
X1 representa a posição horizontal do ponto de início no sistema
cartesiano.
*/
double getX1Linha(Linha l);

/*
Retorna a coordenada Y do ponto inicial da linha, sem alterar a linha.
Y1 representa a posição vertical do ponto de início no sistema
cartesiano. 
*/
double getY1Linha(Linha l);

/*
Retorna a coordenada X do ponto final da linha, sem modificar a linha.
X2 representa a posição horizontal do ponto de fim no sistema
cartesiano.
*/
double getX2Linha(Linha l);

/*
Retorna a coordenada Y do ponto final da linha, sem alterar a linha.
Y2 representa a posição vertical do ponto de fim no sistema
cartesiano. 
*/
double getY2Linha(Linha l);

/*
Retorna a cor da linha, definindo a aparência do traço da linha
quando renderizada graficamente. O valor retornado é um ponteiro para
a string que representa a cor, permitindo uso direto em funções gráficas.
*/
char* getCorLinha(Linha l);

/*
Retorna a largura do traço da borda (stroke-width), ou seja a espessura da linha.
Quanto maior o valor, mais grossa a linha, e sempre >=0.
*/
double getSWLinha(Linha l);

/*
Retorna o estado da flag de disparo, que é um indicador booleano usado para controlar
eventos especiais, animações ou estados da linha. Pode indicar
se a linha foi "ativada", "clicada" ou sofreu alguma ação específica.

Retorna true se disparado, false caso contrário
*/
bool getDispLinha(Linha l);

/*
Retorna o valor do identificador de seleção, o qual permite agrupar, filtrar ou selecionar
linhas baseado em critérios específicos da aplicação. É útil para
operações em lote ou classificação de elementos.
*/
int getNLinha(Linha l);


/*               MÉTODOS SET (MODIFICAÇÃO)  */
/*
* São funções de MODIFICAÇÃO que permitem ALTERAR (escrever) o valor de um
* campo específico da estrutura.
* Características: modificam o objeto, podem incluir validações. */

/*
Define a coordenada X do ponto inicial da linha, reposicionando-o horizontalmente.
Esta operação move o ponto inicial da linha no eixo X do plano cartesiano,
mantendo todas as outras propriedades inalteradas.
*/
void setX1Linha(Linha l, double x);

/*
Define a coordenada Y do ponto inicial da linha, reposicionando-o verticalmente.
Esta operação move o ponto inicial da linha no eixo Y do plano cartesiano,
preservando todas as demais características geométricas e visuais.
*/
void setY1Linha(Linha l, double y);

/*
Define a coordenada X do ponto final da linha, reposicionando-o horizontalmente.
Esta operação move o ponto final da linha no eixo X do plano cartesiano,
mantendo todas as outras propriedades inalteradas.
*/
void setX2Linha(Linha l, double x);

/*
Define a coordenada Y do ponto final da linha, reposicionando-o verticalmente.
Esta operação move o ponto final da linha no eixo Y do plano cartesiano,
preservando todas as demais características geométricas e visuais.
*/
void setY2Linha(Linha l, double y);

/*
Define a cor da linha, alterando a aparência do traço.
Esta operação permite mudanças dinâmicas na cor da linha,
possibilitando efeitos visuais como destaque, seleção ou indicação
de estado.
*/
void setCorLinha(Linha l,const char* cor);

/*
Define a largura do traço (pré-requisito: sw >= 0).
Esta operação controla a espessura da linha,
permitindo desde traços muito finos até linhas bem marcadas.
*/
void setSWLinha(Linha l, double sw);

/*
Define o estado da flag de disparo, alterando o comportamento da linha.
Esta operação permite ativar ou desativar funcionalidades especiais
da linha, controlando comportamentos como animações, eventos ou
indicadores visuais.

disp: novo estado (true para ativado, false para desativado)
*/
void setDispLinha(Linha l, bool disp);

/*
Define um novo identificador de seleção, permitindo reorganizar linhas.
Esta operação permite reclassificar linhas em diferentes grupos
ou categorias, facilitando operações de filtragem e manipulação
em lote de elementos relacionados.
*/
void setNLinha(Linha l, int n);


/*
Define se a linha deve ser pontilhada.

* pontilhada: true para linha pontilhada, false para linha sólida
*
* Pós-condição: o estilo da linha é atualizado
*/
void setPontilhadaLinha(Linha l, bool pontilhada);

/*               FUNÇÕES GEOMÉTRICAS */

/*
 Calcula a área da linha.

 l : ponteiro para a linha

 Pré-condição : l deve ser válido
 Pós-condição : retorna a área (10 * comprimento da linha).
*/
double calculaAreaLinha(Linha l);

/*
 Calcula o comprimento da linha.

 l : ponteiro para a linha

 Pré-condição : l deve ser válido
 Pós-condição : retorna o comprimento (distância euclidiana entre os pontos).
*/
double calculaComprimentoLinha(Linha l);

//                            RENDERIZAÇÃO                               //

/*
Imprime a representação SVG da linha em um arquivo. Esta função gera
o código SVG necessário para visualizar o texto na posição especificada,
com as cores, âncora e estilo tipográfico definidos. A âncora é convertida
automaticamente para o formato SVG ('i'→"start", 'm'→"middle", 'f'→"end").

*        l: ponteiro opaco para a linha a ser renderizada
*        arquivo: ponteiro para FILE aberto para escrita em modo SVG
*
*        Pré-condição: l deve ser um ponteiro válido para Linha,
*                      arquivo deve ser um FILE* válido aberto para escrita
*/
void imprimeLinhaSVG(Linha l, FILE *arquivo);

#endif