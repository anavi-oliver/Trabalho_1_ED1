#ifndef SVG_H
#define SVG_H

#include <stdio.h>
#include "retangulo.h"
#include "circulo.h"
#include "linha.h"
#include "texto.h"

/*
*        MÓDULO DE SAÍDA SVG
*
*        Este módulo é responsável por gerenciar a criação e escrita de arquivos
*        no formato SVG (Scalable Vector Graphics), permitindo a renderização
*        gráfica das formas geométricas definidas pelos TADs.
*
*        Funcionalidades principais:
*        - Criação e inicialização de arquivos SVG com cabeçalho padrão
*        - Inserção de formas geométricas (círculos, retângulos, linhas)
*        - Inserção de elementos de texto
*        - Finalização e fechamento correto do arquivo SVG
*
*/


/*                    FUNÇÕES DE GERENCIAMENTO DE ARQUIVO                    */

/*
Cria e inicializa um novo arquivo SVG pronto para receber elementos gráficos.

Esta função abre um arquivo no caminho especificado, escreve o cabeçalho
padrão SVG incluindo a declaração XML e a tag <svg> com as dimensões
da área de visualização (viewBox). O arquivo retornado está pronto
para receber comandos de desenho de formas geométricas.

viewBox: define a área de coordenadas do SVG, onde (0,0) é o canto
superior esquerdo e (largura, altura) define os limites da área
de desenho visível.

*        caminho: string com o nome/caminho do arquivo a ser criado
*        largura: largura da área de visualização do SVG (coordenada máxima X)
*        altura: altura da área de visualização do SVG (coordenada máxima Y)
*
*        Pré-condição: caminho deve ser válido, largura e altura > 0
*        Pós-condição: retorna ponteiro FILE* aberto para escrita com cabeçalho SVG,
*                      ou NULL se houver erro na abertura do arquivo
*/
FILE* inicializaSvg(char *caminho, double largura, double altura);

/*
Finaliza e fecha o arquivo SVG.

Esta função escreve a tag de fechamento </svg> e fecha o arquivo,
garantindo que todo o conteúdo seja salvo corretamente no disco.
Deve ser chamada ao final de todas as operações de desenho.

*        svg: ponteiro para o arquivo SVG aberto
*
*        Pré-condição: svg deve ser um ponteiro FILE* válido
*        Pós-condição: arquivo SVG fechado com tag de fechamento escrita,
*                      se svg for NULL a função não faz nada
*/
void fechaSvg(FILE *svg);


/*                    FUNÇÕES DE INSERÇÃO DE FORMAS                    */

/*
Insere um retângulo no arquivo SVG.

Esta função converte os dados do TAD Retângulo em uma tag <rect> SVG,
escrevendo no arquivo todas as propriedades necessárias: posição (x,y),
dimensões (largura e altura), cores de borda e preenchimento, e
espessura do traço.

*        svg: ponteiro para o arquivo SVG aberto para escrita
*        r: ponteiro para o retângulo a ser desenhado
*
*        Pré-condição: svg e r devem ser ponteiros válidos
*        Pós-condição: tag <rect> completa é escrita no arquivo SVG,
*                      se svg ou r forem NULL a função não faz nada
*/
void insereRetangulo(FILE *svg, Retangulo r);

/*
Insere um círculo no arquivo SVG.

Esta função converte os dados do TAD Circulo em uma tag <circle> SVG,
escrevendo no arquivo todas as propriedades: coordenadas do centro (cx,cy),
raio, cores de borda e preenchimento, e espessura do traço.

*        svg: ponteiro para o arquivo SVG aberto para escrita
*        c: ponteiro para o círculo a ser desenhado
*
*        Pré-condição: svg e c devem ser ponteiros válidos
*        Pós-condição: tag <circle> completa é escrita no arquivo SVG,
*                      se svg ou c forem NULL a função não faz nada
*/
void insereCirculo(FILE *svg, Circulo c);

/*
Insere uma linha no arquivo SVG.

Esta função converte os dados do TAD Linha em uma tag <line> SVG,
escrevendo no arquivo as coordenadas dos pontos inicial (x1,y1) e
final (x2,y2), a cor do traço e sua espessura.

*        svg: ponteiro para o arquivo SVG aberto para escrita
*        l: ponteiro para a linha a ser desenhada
*
*        Pré-condição: svg e l devem ser ponteiros válidos
*        Pós-condição: tag <line> completa é escrita no arquivo SVG,
*                      se svg ou l forem NULL a função não faz nada
*/
void insereLinha(FILE *svg, Linha l);

/*
Insere um texto no arquivo SVG.

Esta função converte os dados do TAD Texto em uma tag <text> SVG,
escrevendo no arquivo a posição (x,y), o conteúdo textual, cores,
âncora de alinhamento (start/middle/end) e propriedades tipográficas
(família da fonte, peso, tamanho).

*        svg: ponteiro para o arquivo SVG aberto para escrita
*        t: ponteiro para o texto a ser inserido
*
*        Pré-condição: svg e t devem ser ponteiros válidos
*        Pós-condição: tag <text> completa é escrita no arquivo SVG,
*                      se svg ou t forem NULL a função não faz nada
*/
void insereTexto(FILE *svg, Texto t);

#endif