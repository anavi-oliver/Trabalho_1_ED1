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
#include <ctype.h>

Chao processaGeo(const char *nome_path_geo) {
    FILE *arquivo_geo = fopen(nome_path_geo, "r");
    if (arquivo_geo == NULL) {
        printf("Erro ao abrir o arquivo .geo: %s\n", nome_path_geo);
        return NULL;
    }

    Chao meuChao = criaChao();
    if (meuChao == NULL) {
        printf("Erro ao criar o Chão!\n");
        fclose(arquivo_geo);
        return NULL;
    }

    char linha_buffer[512];
    char comando[16];

    //estilo padrão para texto
    char estilo_familia[64] = "sans-serif";
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

            sscanf(linha_buffer, "c %d %lf %lf %lf %s %s", &id, &x, &y, &r, corb, corp);

            Circulo c = criarCirculo(id, x, y, r, corb, corp, false, 0);
            Forma f = criaForma(id, TIPO_CIRCULO, c);
            adicionaFormaChao(meuChao, f);
        }

        else if (strcmp(comando, "r") == 0) {
            int id;
            double x, y, w, h;
            char corb[64], corp[64];

            sscanf(linha_buffer, "r %d %lf %lf %lf %lf %s %s", &id, &x, &y, &w, &h, corb, corp);

            Retangulo rt = criarRetangulo(id, x, y, w, h, corb, corp, false, 0);
            Forma f = criaForma(id, TIPO_RETANGULO, rt);
            adicionaFormaChao(meuChao, f);
        }

        else if (strcmp(comando, "l") == 0) {
            int id;
            double x1, y1, x2, y2;
            char cor[64];

            sscanf(linha_buffer, "l %d %lf %lf %lf %lf %s", &id, &x1, &y1, &x2, &y2, cor);

            Linha l = criarLinha(id, x1, y1, x2, y2, cor, false, 0);
            Forma f = criaForma(id, TIPO_LINHA, l);
            adicionaFormaChao(meuChao, f);
        }

        else if (strcmp(comando, "t") == 0) {
            int id;
            double x, y;
            char corb[64], corp[64];
            char ancora;
            char conteudo_texto[256] = ""; //inicializa como string vazia

            sscanf(linha_buffer, "t %d %lf %lf %s %s", &id, &x, &y, corb, corp);

            //extrair âncora e texto
            char *ptr = linha_buffer;
            int espacos_encontrados = 0;

            //avança o ponteiro até após o 6º espaço (após corp)
            while (*ptr && espacos_encontrados < 6) {
                if (*ptr == ' ') {
                    espacos_encontrados++;
                }
                ptr++;
            }
            
            //agora ptr na âncora.
            if (*ptr) {
                ancora = *ptr;
                ptr++;  //avança pra após a âncora.
                
                //pula espaços em branco
                while (*ptr && isspace(*ptr)) {
                    ptr++;
                }
                
                //resto = o texto
                char *inicio_texto = ptr;
                if (*inicio_texto) {
                    inicio_texto[strcspn(inicio_texto, "\r\n")] = '\0';
                    strcpy(conteudo_texto, inicio_texto);
                }
            }
            
            Estilo e = criarEstilo(estilo_familia, estilo_peso, estilo_tamanho);
            Texto t = criarTexto(id, x, y, corb, corp, ancora, conteudo_texto, e);
            Forma f = criaForma(id, TIPO_TEXTO, t);

            adicionaFormaChao(meuChao, f);

            //destroi pq foi copiado
            destroiEstilo(e);
        }

        else if (strcmp(comando, "ts") == 0) {
            sscanf(linha_buffer, "ts %s %s %s", estilo_familia, estilo_peso, estilo_tamanho);
        }
        else {
             printf("Comando desconhecido ou mal formatado na linha: %s\n", linha_buffer);
        }
    }

    fclose(arquivo_geo);
    return meuChao;
}