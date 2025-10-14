#ifndef PROCESSAGEO_H
#define PROCESSAGEO_H

#include <stdio.h>
#include "chao.h"

//       TIPO ABSTRATO DE DADOS: PROCESSADOR DE ARQUIVO GEO

/*      O módulo ProcessaGeo é responsável por ler e interpretar o arquivo .geo,
*       que contém os comandos de criação das formas geométricas iniciais do jogo.
*       processa linha por linha os comandos de criação de formas (círculos,
*       retângulos, linhas e textos) com seus respectivos atributos (posição, dimensões, cores).
*
*        -Formas no Chão: Adiciona cada forma criada ao Chão, que atua como
*        repositório inicial de todas as formas disponíveis para o jogo.
*
*/

/*________________________________ FUNÇÃO DE PROCESSAMENTO ________________________________*/
/*
Processa o arquivo .geo, criando todas as formas nele especificadas e
as adicionando ao Chao.

* nome_path_geo: string contendo o caminho/nome do arquivo .geo a ser processado
*
*       Pré-condição: 'nome_path_geo' deve ser um caminho válido para um arquivo
*       geo existente e legível
*       Pós-condição: retorna um ponteiro para o Chão contendo todas as formas
*       criadas e adicionadas, ou NULL em caso de erro na abertura
*       do arquivo.
*/
Chao processaGeo(const char *nome_path_geo);

#endif 
