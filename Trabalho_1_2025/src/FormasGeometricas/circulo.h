#ifndef CIRCULO_H
#define CIRCULO_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
*        TIPO ABSTRATO DE DADOS: CIRCULO
*
*        Este módulo define a interface para manipulação de um círculo como
*        Tipo Abstrato de Dados (TAD).  
*        A representação interna (ID, coordenadas, raio, cores etc.) é escondida
*        por um ponteiro opaco (typedef void*).
*/

typedef void *Circulo;   // Ponteiro genérico para o círculo

/*                                FUNÇÕES DE CRIAÇÃO E DESTRUIÇÃO                                */

/*
Esta função é responsável por criar e inicializar um novo círculo na memória.

O círculo criado terá um identificador único para diferenciá-lo de outros
elementos, será posicionado nas coordenadas especificadas do plano cartesiano
e terá o raio definido pelo usuário. As características visuais incluem
a cor da borda (contorno) e a cor de preenchimento (interior), permitindo
customização completa da aparência.

O círculo possui funcionalidades especiais:
uma flag de disparo que pode ser utilizada para controlar eventos ou
animações, e um identificador de seleção que facilita operações de
agrupamento ou filtragem de círculos.

*        i : identificador único do círculo para referência posterior
*        x,y : coordenadas do centro do círculo no sistema cartesiano  
*        r : raio do círculo em unidades de medida (deve ser > 0)
*        corb: string representando a cor da borda/contorno do círculo
*        corp: string representando a cor de preenchimento interno do círculo
*        disp: flag booleana indicando se o círculo foi disparado/ativado
*
*       Pré-condição: o raio r > 0 para formar um círculo válido
*       Pós-condição: retorna um ponteiro opaco para a estrutura do círculo criadoou NULL em caso de falha na alocação de memória

*/
Circulo criarCirculo(int i, double x, double y, double r, char *corb, char *corp, bool disp, int n);

/*
 Libera a memória alocada para o círculo.

 c : ponteiro para o círculo

 Pré-condição : c deve ser válido
 Pós-condição : memória liberada.
*/
void destroiCirculo(Circulo c);


/*                                 MÉTODOS GET (CONSULTA)                                */
/*
*   funções de CONSULTA que permitem ACESSAR (ler) o valor de um campo
*   específico da estrutura sem modificá-lo.
*   Características: não modificam o objeto, apenas retornam valores. */

//c: ponteiro opaco para o círculo a ser consultado, que precisa ser válido e nao NULL

/*
Retorna o ID/ identificador unico do círculo, sem modificar o círculo.
*/
int getIdCirculo(const Circulo c);
/*

Retorna a coordenada X do centro do círculo, sem modificar o círculo.
X representa a posição horizontal do centro no sistema
*/
double getXCirculo(Circulo c);

/*
Retorna a coordenada Y do centro do círculo, sem alterar o círculo.
Y representa a posição vertical do centro no sistema
cartesiano. 
*/
double getYCirculo(Circulo c);

/*
Retorna o raio do círculo (sempre > 0 para círculos válidos).
O raio é a distância do centro até qualquer ponto da circunferência,
sendo uma das propriedades geométricas fundamentais que define o
tamanho do círculo. 
*/
double getRCirculo(Circulo c);

/*
Retorna a cor da borda do círculo, definindo a aparência do contorno/perímetro do círculo
quando renderizado graficamente. O valor retornado é um ponteiro para
a string que representa a cor, permitindo uso direto em funções gráficas.
*/
char* getCorbCirculo(Circulo c);


//Retorna a cor de preenchimento do círculo, definindo a aparência do interior do círculo quando renderizado.
char* getCorpCirculo(Circulo c);

/*
Retorna a largura do traço da borda (stroke-width), ou seja a espessura da linha
que forma o contorno do círculo. Quanto maior o valor, mais grossa a borda, e sempre >=0.
*/
double getSWCirculo(Circulo c);

/*
Retorna o estado da flag de disparo, que é um indicador booleano usado para controlar
eventos especiais, animações ou estados do círculo. Pode indicar
se o círculo foi "ativado", "clicado" ou sofreu alguma ação específica.

Retorna true se disparado, false caso contrário
*/
bool getDispCirculo(Circulo c);

/*
Retorna o valor do identificador de seleção, o qual permite agrupar, filtrar ou selecionar
círculos baseado em critérios específicos da aplicação. É útil para
operações em lote ou classificação de elementos.
*/
int getNCirculo(Circulo c);


/*                                 MÉTODOS SET (MODIFICAÇÃO)                                */
/*
* São funções de MODIFICAÇÃO que permitem ALTERAR (escrever) o valor de um
* campo específico da estrutura.
* Características: modificam o objeto, podem incluir validações. */

/*
Define a coordenada X do centro do círculo, reposicionando-o horizontalmente.
Esta operação move o círculo no eixo X do plano cartesiano,
mantendo todas as outras propriedades inalteradas.
*/
void setXCirculo(Circulo c, double x);

/*
Define a coordenada Y do centro do círculo, reposicionando-o verticalmente.
Esta operação move o círculo no eixo Y do plano cartesiano,
preservando todas as demais características geométricas e visuais.
*/
void setYCirculo(Circulo c, double y);

/*
Define um novo raio para o círculo (pré-requisito: r > 0).
Esta operação redimensiona o círculo, afetando sua área e perímetro.
Inclui validação para garantir que apenas valores positivos sejam aceitos.
*/
void setRCirculo(Circulo c, double r);

/*
Define a cor da borda do círculo, alterando a aparência do contorno.
Esta operação permite mudanças dinâmicas na cor da borda,
possibilitando efeitos visuais como destaque, seleção ou indicação
de estado.
*/
void setCorbCirculo(Circulo c,const char* corb);

//Define a cor de preenchimento interno, modificando a aparência do interior do círculo.
void setCorpCirculo(Circulo c,const char* corp);

/*
Define a largura do traço da borda (pré-requisito: sw >= 0).
Esta operação controla a espessura da linha que forma o contorno,
permitindo desde bordas muito finas até contornos bem marcados.
*/
void setSWCirculo(Circulo c, double sw);

/*
Define o estado da flag de disparo, alterando o comportamento do círculo.
Esta operação permite ativar ou desativar funcionalidades especiais
do círculo, controlando comportamentos como animações, eventos ou
indicadores visuais.

disp: novo estado (true para ativado, false para desativado)
*/
void setDispCirculo(Circulo c, bool disp);

/*
Define um novo identificador de seleção, permitindo reorganizar círculos.
Esta operação permite reclassificar círculos em diferentes grupos
ou categorias, facilitando operações de filtragem e manipulação
em lote de elementos relacionados.
*/
void setNCirculo(Circulo c, int n);

/*                                  FUNÇÕES GEOMÉTRICAS                                  */

/*
 Calcula a área do círculo.

 c : ponteiro para o círculo

 Pré-condição : c deve ser válido
 Pós-condição : retorna a área (π * r²).
*/
double calculaAreaCirculo(Circulo c);

/*
 Calcula o perímetro do círculo.

 c : ponteiro para o círculo

 Pré-condição : c deve ser válido
 Pós-condição : retorna o perímetro (2 * π * r).
*/
double calculaPerimetroCirculo(Circulo c);

/*
 Verifica se um ponto está dentro do círculo.

 c  : ponteiro para o círculo
 px : coordenada X do ponto
 py : coordenada Y do ponto

 Pré-condição : c deve ser válido
 Pós-condição : retorna true se o ponto estiver dentro.
*/
bool pontoNoCirculo(Circulo c, double px, double py);

/*
 Verifica se dois círculos se intersectam.

 c1, c2 : ponteiros para os círculos

 Pré-condição : ambos os círculos devem ser válidos
 Pós-condição : retorna true se houver interseção.
*/
bool circulosIntersectam(Circulo c1, Circulo c2);


//                            RENDERIZAÇÃO                               //

/*
Imprime a representação SVG do circulo em um arquivo. Esta função gera
o código SVG necessário para visualizar o texto na posição especificada,
com as cores, âncora e estilo tipográfico definidos. A âncora é convertida
automaticamente para o formato SVG ('i'→"start", 'm'→"middle", 'f'→"end").

*        c: ponteiro opaco para o circulo a ser renderizado
*        arquivo: ponteiro para FILE aberto para escrita em modo SVG
*
*        Pré-condição: c deve ser um ponteiro válido para Circulo,
*                      arquivo deve ser um FILE* válido aberto para escrita
*/
void imprimeCirculoSVG(Circulo c, FILE *arquivo);


#endif
