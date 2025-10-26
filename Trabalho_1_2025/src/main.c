
//linha 187 para o viewbox
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h> 

//Headers dos módulos principais
#include "arena.h"     
#include "chao.h"         

#include "formas.h"    

#include "svg.h"      
#include "processaGeo.h" 
#include "processaQry.h"  


//makefile com padrão C99.
#define PATH_LEN 512
#define FILE_NAME_LEN 256
#define MAX_FULL_PATH 2048  // Tamanho fixo 

// ======================= FUNÇÕES AUXILIARES DE CAMINHO =======================
static void trataPath(char *path, int tamMax, char* arg) {
    int argLen = strlen(arg);

    if (argLen >= tamMax) {
        fprintf(stderr, "ERRO: Caminho excede o tamanho maximo permitido.\n");
        exit(EXIT_FAILURE);
    }

    //remover a barra final 
    if (argLen > 0 && arg[argLen - 1] == '/') {
        arg[argLen - 1] = '\0';
        argLen--;
    }

    strncpy(path, arg, tamMax - 1);
    path[tamMax - 1] = '\0';
}


static char* montaCaminhoCompleto(const char *dir, const char *nomeArquivo) {
    if (!dir || !nomeArquivo || strlen(nomeArquivo) == 0) return NULL;

    size_t len = strlen(dir) + strlen(nomeArquivo) + 2; 
    char *caminhoCompleto = (char*)malloc(len);

    if (caminhoCompleto == NULL) {
        fprintf(stderr, "ERRO: Falha ao alocar memoria para o caminho completo.\n");
        exit(EXIT_FAILURE);
    }

    sprintf(caminhoCompleto, "%s/%s", dir, nomeArquivo);
    return caminhoCompleto;
}


//tira geo ou .qry para obter o nome base do arquivo.

static void getNomeBase(const char *nomeCompleto, char *destino, int tamMax) {
    strncpy(destino, nomeCompleto, tamMax);
    destino[tamMax - 1] = '\0';
    char *ponto = strrchr(destino, '.');
    if (ponto != NULL && ponto != destino) {
        *ponto = '\0';
    }
}

// ======================= FUNÇÕES DE DESENHO E ITERAÇÃO =======================
/*
 * Função Wrapper (Callback) para iteração da Arena.
 * Converte o ponteiro genérico (void *auxData) de volta para FILE * para desenhar.
 */
static void desenhaFormaWrapper(Forma f, void *auxData) {
    FILE *svg = (FILE *)auxData;
    desenhaForma(f, svg); 
}


// * Desenha todas as formas no Chao (que usa uma Fila).

static void desenhaContainerFormas(Chao chao, FILE *svg) {
    if (chao == NULL || svg == NULL) return;

    int tamanhoOriginal = getChaoTamanho(chao);

    for (int i = 0; i < tamanhoOriginal; i++) {
        Forma f = removeFormaChao(chao); // 1. Desenfileira
        if (f != NULL) {
            desenhaForma(f, svg); // 2. Desenha
            adicionaFormaChao(chao, f); // 3. Enfileira de volta
        }
    }
}

// =============================================================================================================
//                                       FUNÇÃO MAIN
//                           ___________________________________

/*
padrao c99 -> int main(int argc, char *argv[]) =
        Argument Count (argc) = armazena o total de argumentos passados para o programa na linha de comando
        Argument Vector (argv) = vetor de strings ou ponteiro para ponteiro de caracteres
*/
int main(int argc, char *argv[]) {

    //definicao e inicializacao das variáveis de caminhos
    char dirEntrada[PATH_LEN] = ".";
    char arqGeo[FILE_NAME_LEN] = "";
    char arqQry[FILE_NAME_LEN] = "";
    char dirSaida[PATH_LEN] = "";

    //flags de parâmetros obrigatórios
    bool f_encontrado = false;
    bool o_encontrado = false;

    // ======================= 1. TRATAMENTO DOS PARÂMETROS (CLI) =======================
    int i = 1;
    while (i < argc) {
        if (strcmp(argv[i], "-e") == 0) { // Diretório base de entrada (\$DIR_ENTRADA)
            i++;
            if (i >= argc) {
                fprintf(stderr, "ERRO: O parametro -e requer um caminho.\n");
                return EXIT_FAILURE;
            }
            trataPath(dirEntrada, PATH_LEN, argv[i]);
        } 
        else if (strcmp(argv[i], "-f") == 0) { // Arquivo .geo
            i++;
            if (i >= argc) {
                fprintf(stderr, "ERRO: O parametro -f requer um nome de arquivo .geo.\n");
                return EXIT_FAILURE;
            }
            strncpy(arqGeo, argv[i], FILE_NAME_LEN - 1);
            arqGeo[FILE_NAME_LEN - 1] = '\0';
            f_encontrado = true;
        } 
        else if (strcmp(argv[i], "-q") == 0) { // Arquivo .qry
            i++;
            if (i >= argc) {
                fprintf(stderr, "ERRO: O parametro -q requer um nome de arquivo .qry.\n");
                return EXIT_FAILURE;
            }
            strncpy(arqQry, argv[i], FILE_NAME_LEN - 1);
            arqQry[FILE_NAME_LEN - 1] = '\0';
        }
        else if (strcmp(argv[i], "-o") == 0) { // Diretório base de saída (\$DIR_SAIDA)
            i++;
            if (i >= argc) {
                fprintf(stderr, "ERRO: O parametro -o requer um caminho de saida.\n");
                return EXIT_FAILURE;
            }
            trataPath(dirSaida, PATH_LEN, argv[i]);
            o_encontrado = true;
        }
        else {
            fprintf(stderr, "AVISO: Parametro desconhecido ignorado: %s\n", argv[i]);
        }
        i++;
    }

    // ======================= 2. VALIDAÇÃO E PREPARAÇÃO =======================

    if (!f_encontrado || !o_encontrado) {
        fprintf(stderr, "ERRO: Os parametros -f e -o sao obrigatorios. Abortando.\n");
        return EXIT_FAILURE;
    }

    char nomeBaseGeo[FILE_NAME_LEN];
    getNomeBase(arqGeo, nomeBaseGeo, FILE_NAME_LEN);

    char *caminhoCompletoGeo = montaCaminhoCompleto(dirEntrada, arqGeo);
    if (caminhoCompletoGeo == NULL) {
         return EXIT_FAILURE;
    }

    // ======================= 3. ESTRUTURAS CENTRAIS E ARENA =======================

    Chao meuChao = NULL;
    Arena minhaArena = NULL;
    double pontuacaoTotal = 0.0;

    //aumentar view
    const double LARGURA_ARENA = 1555.0; //1555
    const double ALTURA_ARENA = 810.0; //810
 
    
    minhaArena = criaArena(LARGURA_ARENA, ALTURA_ARENA);
    if (minhaArena == NULL) {
        fprintf(stderr, "ERRO fatal: Nao foi possivel criar a Arena.\n");
        free(caminhoCompletoGeo);
        return EXIT_FAILURE;
    }

    // ======================= 4. PROCESSAMENTO DO ARQUIVO .GEO =======================

    printf("Iniciando processamento do arquivo GEO: %s\n", caminhoCompletoGeo);
    // processaGeo retorna o Chao, que é o repositório inicial
    meuChao = processaGeo(caminhoCompletoGeo);
    
    if (meuChao == NULL) {
        fprintf(stderr, "ERRO fatal: Falha ao processar o arquivo GEO ou criar o Chao.\n");
        destroiArena(minhaArena);
        free(caminhoCompletoGeo);
        return EXIT_FAILURE;
    }

    // ======================= 5. GERAÇÃO DO SVG INICIAL (ESTADO DO CHÃO) =======================

    // Nome do arquivo SVG inicial: arq.svg
    char nomeSvgInicial[MAX_FULL_PATH];
    sprintf(nomeSvgInicial, "%s.svg", nomeBaseGeo);
    char *caminhoSvgInicial = montaCaminhoCompleto(dirSaida, nomeSvgInicial);
    
    printf("Gerando SVG inicial: %s\n", caminhoSvgInicial);
    FILE *svgInicial = inicializaSvg(caminhoSvgInicial, LARGURA_ARENA, ALTURA_ARENA);
    
    if (svgInicial != NULL) {
        // Desenha todas as formas que estão no Chao
        desenhaContainerFormas(meuChao, svgInicial);
        fechaSvg(svgInicial);
    } else {
        fprintf(stderr, "AVISO: Nao foi possivel criar o SVG inicial em %s\n", caminhoSvgInicial);
    }
    free(caminhoSvgInicial);


// ======================= 6. PROCESSAMENTO DO ARQUIVO .QRY  =======================
    int formas_clonadas = 0;
    int formas_esmagadas = 0;

if (arqQry[0] != '\0') {
    // Extrair apenas o nome do arquivo .qry (sem subdiretórios)
    char *ultimaBarra = strrchr(arqQry, '/');
    char *nomeArquivoQry = (ultimaBarra != NULL) ? ultimaBarra + 1 : arqQry;
    
    char nomeBaseQry[FILE_NAME_LEN];
    getNomeBase(nomeArquivoQry, nomeBaseQry, FILE_NAME_LEN);

    char *caminhoCompletoQry = montaCaminhoCompleto(dirEntrada, arqQry);
    
    // Nomes de saída do QRY: arq-arqcons.svg e arq-arqcons.txt
    char nomeSaidaBaseQry[MAX_FULL_PATH];
    sprintf(nomeSaidaBaseQry, "%s-%s", nomeBaseGeo, nomeBaseQry);
    
    char nomeTxtQry[MAX_FULL_PATH];
    snprintf(nomeTxtQry, sizeof(nomeTxtQry), "%s.txt", nomeSaidaBaseQry);
    
    char *caminhoTxtQry = montaCaminhoCompleto(dirSaida, nomeTxtQry);
    
    // Chamada principal para processar o QRY
processaQry(caminhoCompletoQry, caminhoTxtQry, minhaArena, meuChao, 
            &pontuacaoTotal, &formas_clonadas, &formas_esmagadas);
    
printf("Processamento QRY concluido.\n");
printf("Pontuacao final: %.2f\n", pontuacaoTotal);
printf("Formas clonadas: %d\n", formas_clonadas);
printf("Formas esmagadas: %d\n", formas_esmagadas);


// --- Geração do SVG Final (após o QRY) ---
    char nomeSvgFinal[MAX_FULL_PATH];
    snprintf(nomeSvgFinal, sizeof(nomeSvgFinal), "%s.svg", nomeSaidaBaseQry);
    char *caminhoSvgFinal = montaCaminhoCompleto(dirSaida, nomeSvgFinal);

printf("Gerando SVG final: %s\n", caminhoSvgFinal);
    FILE *svgFinal = inicializaSvg(caminhoSvgFinal, LARGURA_ARENA, ALTURA_ARENA);

if (svgFinal != NULL) {

    // PRIMEIRO: Desenha o chão (formas processadas)
    desenhaContainerFormas(meuChao, svgFinal);
    // DEPOIS: Desenha a arena (se ainda houver formas - geralmente vazia após calc)
    iteraFormasArena(minhaArena, desenhaFormaWrapper, svgFinal);

    fechaSvg(svgFinal);
} else {
    fprintf(stderr, "AVISO: Nao foi possivel criar o SVG final em %s\n", caminhoSvgFinal);
}
}


    // ======================= 7. LIBERAÇÃO DE MEMÓRIA =======================

    printf("\nIniciando liberacao de memoria...\n");
    
    destroiArena(minhaArena); 
    destroiChao(meuChao); 
    free(caminhoCompletoGeo);

    printf("Programa ted encerrado com sucesso.\n");
    
    return EXIT_SUCCESS; 
}