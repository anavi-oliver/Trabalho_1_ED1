#include "processaGeo.h"

#include "chao.h"
#include "circulo.h"
#include "linha.h"
#include "retangulo.h"
#include "texto.h"
#include "formas.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Chao processaGeo(const char *nome_path_geo) {
    FILE *arquivo_geo = fopen(nome_path_geo, "r");
    if (arquivo_geo == NULL) {
        printf("Erro ao abrir o arquivo .geo: %s\n", nome_path_geo);
        return NULL;
    }
    
    //cria o Chao que armazenará todas as formas
    Chao meuChao = criaChao();
    if (meuChao == NULL) {
        printf("Erro ao criar o Chão!\n");
        fclose(arquivo_geo);
        return NULL;
    }
    
    //buffer para leitura de linhas e variáveis auxiliares
    char linha_buffer[512];
    char comando[16];
    
    //estilo padrão (pode ser modificado pelo comando 'ts')
    char estilo_familia[64] = "sans";
    char estilo_peso[16] = "normal";
    char estilo_tamanho[16] = "12";
    
    while (fgets(linha_buffer, sizeof(linha_buffer), arquivo_geo) != NULL) {
        if (linha_buffer[0] == '\n' || linha_buffer[0] == '#') {
            continue;
        }
        
        sscanf(linha_buffer, "%s", comando);
        
        if (strcmp(comando, "c") == 0) {
            int id;
            double x, y, r;
            char corb[64], corp[64];
            
            sscanf(linha_buffer, "c %d %lf %lf %lf %s %s", &id, &x, &y, &r, corb, corp); //extrair facilmente os valores dos comandos e criar as formas correspondentes
            
            Circulo c = criarCirculo(id, x, y, r, corb, corp, false, 0);
            Forma f = criaForma(id, TIPO_CIRCULO, c);
            
            adicionaFormaChao(meuChao, f);
        }

        else if (strcmp(comando, "r") == 0) {
            int id;
            double x, y, w, h;
            char corb[64], corp[64];
            
            sscanf(linha_buffer, "r %d %lf %lf %lf %lf %s %s", &id, &x, &y, &w, &h, corb, corp);
            
            Retangulo r = criarRetangulo(id, x, y, w, h, corb, corp, false, 0);
            Forma f = criaForma(id, TIPO_RETANGULO, r);
            
            adicionaFormaChao(meuChao, f);
        }

        else if (strcmp(comando, "l") == 0) {
            int id;
            double x1, y1, x2, y2;
            char cor[64];
            
            sscanf(linha_buffer, "l %d %lf %lf %lf %lf %s",  &id, &x1, &y1, &x2, &y2, cor);
            
            Linha l = criarLinha(id, x1, y1, x2, y2, cor, false, 0);
            Forma f = criaForma(id, TIPO_LINHA, l);
            
            adicionaFormaChao(meuChao, f);
        }

        else if (strcmp(comando, "t") == 0) {
            int id;
            double x, y;
            char corp[64], corb[64], ancora;
            char conteudo_texto[256];
            
            char *inicio_texto = strstr(linha_buffer, "txto");
            if (inicio_texto != NULL) {
                inicio_texto += 5; 

                inicio_texto[strcspn(inicio_texto, "\r\n")] = '\0';
                strcpy(conteudo_texto, inicio_texto);
            } else {
                strcpy(conteudo_texto, "");
            }
            
            sscanf(linha_buffer, "t %d %lf %lf %s %s %c", &id, &x, &y, corp, corb, &ancora);
            
            // Cria o estilo com as configurações atuais e o texto com o estilo
            Estilo e = criarEstilo(estilo_familia, estilo_peso, estilo_tamanho);
            Texto t = criarTexto(id, x, y, corb, corp, ancora, conteudo_texto, e);
            Forma f = criaForma(id, TIPO_TEXTO, t);
            
            adicionaFormaChao(meuChao, f);
            
            destroiEstilo(e); //destroi ja que foi copiado pra criarTexto
        }

        else if (strcmp(comando, "ts") == 0) {
            sscanf(linha_buffer, "ts %s %s %s", estilo_familia, estilo_peso, estilo_tamanho);
        }
        else {
             printf("Comando desconhecido: %s\n", comando);
        }
    }
    
    fclose(arquivo_geo);
    return meuChao;
}