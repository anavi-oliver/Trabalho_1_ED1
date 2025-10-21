#ifndef RETANGULO_H
#define RETANGULO_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
*        TIPO ABSTRATO DE DADOS: RETANGULO
*
*        Este módulo define a interface para manipulação de um retângulo como
*        Tipo Abstrato de Dados (TAD).  
*        A representação interna (ID, coordenadas, dimensões, cores etc.) é escondida
*        por um ponteiro opaco (typedef void*).
*/

typedef void *Retangulo;   // Ponteiro genérico para o retângulo

/*                   FUNÇÕES DE CRIAÇÃO E DESTRUIÇÃO  */
/*
Esta função é responsável por criar e inicializar um novo retângulo na memória.

O retângulo criado terá um identificador único para diferenciá-lo de outros
elementos, será posicionado nas coordenadas especificadas do plano cartesiano
e terá as dimensões definidas pelo usuário. As características visuais incluem
a cor da borda (contorno) e a cor de preenchimento (interior), permitindo
customização completa da aparência.

O retângulo possui funcionalidades especiais:
uma flag de disparo que pode ser utilizada para controlar eventos ou
animações, e um identificador de seleção que facilita operações de
agrupamento ou filtragem de retângulos.

*        i : identificador único do retângulo para referência posterior
*        x,y : coordenadas do canto superior esquerdo do retângulo no sistema cartesiano  
*        w : largura do retângulo em unidades de medida (deve ser > 0)
*        h : altura do retângulo em unidades de medida (deve ser > 0)
*        corb: string representando a cor da borda/contorno do retângulo
*        corp: string representando a cor de preenchimento interno do retângulo
*        disp: flag booleana indicando se o retângulo foi disparado/ativado
*        n : identificador numérico adicional para seleção ou agrupamento
*
*       Pré-condição: a largura w > 0 e altura h > 0 para formar um retângulo válido
*       Pós-condição: retorna um ponteiro opaco para a estrutura do retângulo criado ou NULL em caso de falha na alocação de memória

*/
Retangulo criarRetangulo(int i, double x, double y, double w, double h, char *corb, char *corp, bool disp, int n);

/*
 Libera a memória alocada para o retângulo.

 r : ponteiro para o retângulo

 Pré-condição : r deve ser válido
 Pós-condição : memória liberada.
*/
void destroiRetangulo(Retangulo r);


/*                     MÉTODOS GET (CONSULTA)  */
/*
*   funções de CONSULTA que permitem ACESSAR (ler) o valor de um campo
*   específico da estrutura sem modificá-lo.
*   Características: não modificam o objeto, apenas retornam valores. */

//r: ponteiro opaco para o retângulo a ser consultado, que precisa ser válido e nao NULL

/*
Retorna a coordenada X do canto superior esquerdo do retângulo, sem modificar o retângulo.
X representa a posição horizontal do canto superior esquerdo no sistema
cartesiano.
*/
double getXRetangulo(Retangulo r);

/*
Retorna a coordenada Y do canto superior esquerdo do retângulo, sem alterar o retângulo.
Y representa a posição vertical do canto superior esquerdo no sistema
cartesiano. 
*/
double getYRetangulo(Retangulo r);

/*
Retorna a largura do retângulo (sempre > 0 para retângulos válidos).
A largura é a extensão horizontal do retângulo,
sendo uma das propriedades geométricas fundamentais que define o
tamanho do retângulo. 
*/
double getLarguraRetangulo(Retangulo r);

/*
Retorna a altura do retângulo (sempre > 0 para retângulos válidos).
A altura é a extensão vertical do retângulo,
sendo uma das propriedades geométricas fundamentais que define o
tamanho do retângulo. 
*/
double getAlturaRetangulo(Retangulo r);

/*
Retorna a cor da borda do retângulo, definindo a aparência do contorno/perímetro do retângulo
quando renderizado graficamente. O valor retornado é um ponteiro para
a string que representa a cor, permitindo uso direto em funções gráficas.
*/
char* getCorbRetangulo(Retangulo r);

//Retorna a cor de preenchimento do retângulo, definindo a aparência do interior do retângulo quando renderizado.
char* getCorpRetangulo(Retangulo r);

/*
Retorna a largura do traço da borda (stroke-width), ou seja a espessura da linha
que forma o contorno do retângulo. Quanto maior o valor, mais grossa a borda, e sempre >=0.
*/
double getSWRetangulo(Retangulo r);

/*
Retorna o estado da flag de disparo, que é um indicador booleano usado para controlar
eventos especiais, animações ou estados do retângulo. Pode indicar
se o retângulo foi "ativado", "clicado" ou sofreu alguma ação específica.

Retorna true se disparado, false caso contrário
*/
bool getDispRetangulo(Retangulo r);

/*
Retorna o valor do identificador de seleção, o qual permite agrupar, filtrar ou selecionar
retângulos baseado em critérios específicos da aplicação. É útil para
operações em lote ou classificação de elementos.
*/
int getNRetangulo(Retangulo r);


/*                       MÉTODOS SET (MODIFICAÇÃO)  */
/*
* São funções de MODIFICAÇÃO que permitem ALTERAR (escrever) o valor de um
* campo específico da estrutura.
* Características: modificam o objeto, podem incluir validações. */

//r: ponteiro opaco para o retângulo a ser consultado, que precisa ser válido e nao NULL


/*
Define a coordenada X do canto superior esquerdo do retângulo, reposicionando-o horizontalmente.
Esta operação move o retângulo no eixo X do plano cartesiano,
mantendo todas as outras propriedades inalteradas.
*/
void setXRetangulo(Retangulo r, double x);

/*
Define a coordenada Y do canto superior esquerdo do retângulo, reposicionando-o verticalmente.
Esta operação move o retângulo no eixo Y do plano cartesiano,
preservando todas as demais características geométricas e visuais.
*/
void setYRetangulo(Retangulo r, double y);

/*
Define uma nova largura para o retângulo (pré-requisito: w > 0).
Esta operação redimensiona o retângulo horizontalmente, afetando sua área e perímetro.
Inclui validação para garantir que apenas valores positivos sejam aceitos.
*/
void setLarguraRetangulo(Retangulo r, double w);

/*
Define uma nova altura para o retângulo (pré-requisito: h > 0).
Esta operação redimensiona o retângulo verticalmente, afetando sua área e perímetro.
Inclui validação para garantir que apenas valores positivos sejam aceitos.
*/
void setAlturaRetangulo(Retangulo r, double h);

/*
Define a cor da borda do retângulo, alterando a aparência do contorno.
Esta operação permite mudanças dinâmicas na cor da borda,
possibilitando efeitos visuais como destaque, seleção ou indicação
de estado.
*/
void setCorbRetangulo(Retangulo r,const char* corb);

//Define a cor de preenchimento interno, modificando a aparência do interior do retângulo.
void setCorpRetangulo(Retangulo r,const char* corp);

/*
Define a largura do traço da borda (pré-requisito: sw >= 0).
Esta operação controla a espessura da linha que forma o contorno,
permitindo desde bordas muito finas até contornos bem marcados.
*/
void setSWRetangulo(Retangulo r, double sw);

/*
Define o estado da flag de disparo, alterando o comportamento do retângulo.
Esta operação permite ativar ou desativar funcionalidades especiais
do retângulo, controlando comportamentos como animações, eventos ou
indicadores visuais.

disp: novo estado (true para ativado, false para desativado)
*/
void setDispRetangulo(Retangulo r, bool disp);

/*
Define um novo identificador de seleção, permitindo reorganizar retângulos.
Esta operação permite reclassificar retângulos em diferentes grupos
ou categorias, facilitando operações de filtragem e manipulação
em lote de elementos relacionados.
*/
void setNRetangulo(Retangulo r, int n);

/*                         FUNÇÕES GEOMÉTRICAS  */
//r: ponteiro opaco para o retângulo a ser consultado, que precisa ser válido e nao NULL

// Retorna a área (largura * altura).
double calculaAreaRetangulo(Retangulo r);

/*
 Calcula o perímetro do retângulo.
Retorna o perímetro (2 * (largura + altura)).
*/
double calculaPerimetroRetangulo(Retangulo r);

/*
 Verifica se um ponto está dentro do retângulo.

 r  : ponteiro para o retângulo
 px : coordenada X do ponto
 py : coordenada Y do ponto

Retorna true se o ponto estiver dentro.
*/
bool pontoNoRetangulo(Retangulo r, double px, double py);

/*
 Verifica se dois retângulos se intersectam.

 r1, r2 : ponteiros para os retângulos

Retorna true se houver interseção.
*/
bool retangulosIntersectam(Retangulo r1, Retangulo r2);


//                            RENDERIZAÇÃO                               //

/*
Imprime a representação SVG do retangulo em um arquivo. Esta função gera
o código SVG necessário para visualizar o texto na posição especificada,
com as cores, âncora e estilo tipográfico definidos. A âncora é convertida
automaticamente para o formato SVG ('i'→"start", 'm'→"middle", 'f'→"end").

*        r: ponteiro opaco para o retangulo a ser renderizado
*        arquivo: ponteiro para FILE aberto para escrita em modo SVG
*
*        Pré-condição: r deve ser um ponteiro válido para Retangulo,
*                      arquivo deve ser um FILE* válido aberto para escrita
*/
void imprimeRetanguloSVG(Retangulo r, FILE *arquivo);

#endif