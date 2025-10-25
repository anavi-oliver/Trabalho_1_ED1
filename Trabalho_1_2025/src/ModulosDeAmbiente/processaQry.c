#include "processaQry.h"

#include "fila.h"

#include "carregador.h"
#include "disparador.h"
#include "arena.h"
#include "chao.h"

#include "formas.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OBJETOS 100

typedef struct stRepositorio {
    Carregador carregadores[MAX_OBJETOS];
    int num_carregadores;
    Disparador disparadores[MAX_OBJETOS];
    int num_disparadores;
} RepositorioR;


/*________________________________ FUNÇÕES AUXILIARES INTERNAS ________________________________*/

static void imprimeDetalhesForma(Forma f, FILE *arquivo) {
    if (f == NULL || arquivo == NULL) return;
    
    int id = getFormaId(f);
    TipoForma tipo = getFormaTipo(f);
    double x = getFormaX(f);
    double y = getFormaY(f);
    
    fprintf(arquivo, "    Forma ID: %d, Tipo: ", id);
    
    switch (tipo) {
        case TIPO_CIRCULO:
            fprintf(arquivo, "Círculo, Centro: (%.2f, %.2f), Raio: %.2f, ", x, y, getRCirculo(getFormaAssoc(f)));           
            fprintf(arquivo, "Borda: %s, Preench: %s\n", 
                    getFormaCorBorda(f), getFormaCorPreenchimento(f));
            break;
            
        case TIPO_RETANGULO:
            fprintf(arquivo, "Retângulo, Posição: (%.2f, %.2f), ", x, y);
            fprintf(arquivo, "Borda: %s, Preench: %s\n", 
                    getFormaCorBorda(f), getFormaCorPreenchimento(f));
            break;
            
        case TIPO_LINHA:
            fprintf(arquivo, "Linha, Início: (%.2f, %.2f), ", x, y);
            fprintf(arquivo, "Cor: %s\n", getFormaCorBorda(f));
            break;
            
        case TIPO_TEXTO:
            fprintf(arquivo, "Texto, Posição: (%.2f, %.2f), ", x, y);
            fprintf(arquivo, "Borda: %s, Preench: %s\n", 
                    getFormaCorBorda(f), getFormaCorPreenchimento(f));
            break;
    }
}

static Disparador encontraOuCriaDisparador(Repositorio *repo, int id) {
    RepositorioR *repo_interno = (RepositorioR *)repo;
    
    for (int i = 0; i < repo_interno->num_disparadores; i++) {
        if (getDisparadorId(repo_interno->disparadores[i]) == id) {
            return repo_interno->disparadores[i];
        }
    }
    
    if (repo_interno->num_disparadores < MAX_OBJETOS) {
        Disparador novo = criaDisparador(id, 0.0, 0.0, NULL, NULL);
        repo_interno->disparadores[repo_interno->num_disparadores] = novo;
        repo_interno->num_disparadores++;
        return novo;
    }
    
    return NULL;
}

static Carregador encontraOuCriaCarregador(Repositorio *repo, int id) {
    RepositorioR *repo_interno = (RepositorioR *)repo;

    for (int i = 0; i < repo_interno->num_carregadores; i++) {
        if (getCarregadorId(repo_interno->carregadores[i]) == id) {
            return repo_interno->carregadores[i];
        }
    }
    
    if (repo_interno->num_carregadores < MAX_OBJETOS) {
        Carregador novo = criaCarregador(id);
        repo_interno->carregadores[repo_interno->num_carregadores] = novo;
        repo_interno->num_carregadores++;
        return novo;
    }
    
    return NULL;
}

/*________________________________ FUNÇÕES PÚBLICAS ________________________________*/

Repositorio criaRepositorio() {
    RepositorioR *repo = (RepositorioR *)malloc(sizeof(RepositorioR));
    if (repo == NULL) {
        printf("Erro ao alocar memoria para o repositorio!\n");
        return NULL;
    }
    
    repo->num_carregadores = 0;
    repo->num_disparadores = 0;
    
    return (Repositorio) repo;
}

void destroiRepositorio(Repositorio repo) {
    RepositorioR *repo_interno = (RepositorioR *)repo;
    
    if (repo_interno == NULL) {
        return;
    }
    
    for (int i = 0; i < repo_interno->num_carregadores; i++) {
        destroiCarregador(repo_interno->carregadores[i]);
    }
    
    for (int i = 0; i < repo_interno->num_disparadores; i++) {
        destroiDisparador(repo_interno->disparadores[i]);
    }
    
    free(repo_interno);
}

void processaQry(const char *nome_path_qry, const char *nome_txt, Arena arena, Chao chao, 
                 double *pontuacao_total, int *formas_clonadas_out, int *formas_esmagadas_out) {
    
    FILE *arquivo_qry = fopen(nome_path_qry, "r");
    if (arquivo_qry == NULL) {
        printf("Erro ao abrir o arquivo .qry: %s\n", nome_path_qry);
        return;
    }
    
    FILE *arquivo_txt = fopen(nome_txt, "w");
    if (arquivo_txt == NULL) {
        printf("Erro ao abrir o arquivo .txt: %s\n", nome_txt);
        fclose(arquivo_qry);
        return;
    }
    
    Repositorio repo = criaRepositorio();
    if (repo == NULL) {
        fclose(arquivo_qry);
        fclose(arquivo_txt);
        return;
    }
    
    //fila especial para anotações visuais (asteriscos, trajetórias, marcadores)
    Queue filaSVG = createQueue();
    
    int instrucoes_realizadas = 0;
    int total_disparos = 0;
    int formas_esmagadas = 0;
    int formas_clonadas = 0;
    
    char linha_buffer[512];
    char comando[16];
    
    fprintf(arquivo_txt, "_______ RELATÓRIO DE EXECUÇÃO ________ \n\n");
    
    while (fgets(linha_buffer, sizeof(linha_buffer), arquivo_qry) != NULL) {
        if (linha_buffer[0] == '\n' || linha_buffer[0] == '#') {
            continue;
        }
        
        sscanf(linha_buffer, "%s", comando);
        fprintf(arquivo_txt, "[*] %s", linha_buffer);
        
        //pd: posiciona disparador - pd l x y
        if (strcmp(comando, "pd") == 0) {
            int id;
            double x, y;
            sscanf(linha_buffer, "pd %d %lf %lf", &id, &x, &y);
            
            Disparador d = encontraOuCriaDisparador(repo, id);
            if (d != NULL) {
                setDisparadorPosicao(d, x, y);
                fprintf(arquivo_txt, " Disparador %d posicionado em (%.2f, %.2f)\n", id, x, y); 
                instrucoes_realizadas++;
            }
        }
        
        //lc: Load Carregador - lc c n
        else if (strcmp(comando, "lc") == 0) {
            int id, n;
            sscanf(linha_buffer, "lc %d %d", &id, &n);
            
            Carregador c = encontraOuCriaCarregador(repo, id);
            if (c != NULL) {
                fprintf(arquivo_txt, "    Carregando %d forma(s) no carregador %d:\n", n, id);
                
                int formas_antes = getCarregadorTamanho(c);
                carregaFormasDoChao(c, chao, n);
                int formas_depois = getCarregadorTamanho(c);
                int formas_carregadas = formas_depois - formas_antes;
                
                fprintf(arquivo_txt, "    Total de formas carregadas: %d\n", formas_carregadas);
                instrucoes_realizadas++;
            }
        }
        
        //atch: attach carregadores - atch d cesq cdir
        else if (strcmp(comando, "atch") == 0) {
            int id_disp, id_esq, id_dir;
            sscanf(linha_buffer, "atch %d %d %d", &id_disp, &id_esq, &id_dir);
            
            Carregador esq = encontraOuCriaCarregador(repo, id_esq);
            Carregador dir = encontraOuCriaCarregador(repo, id_dir);
            
            if (esq == NULL || dir == NULL) {
                fprintf(arquivo_txt, "    ERRO: Carregadores invalidos\n");
                continue;
            }
            
            RepositorioR *repo_interno = (RepositorioR *)repo;
            Disparador d = NULL;
            
            for (int i = 0; i < repo_interno->num_disparadores; i++) {
                if (getDisparadorId(repo_interno->disparadores[i]) == id_disp) {
                    d = repo_interno->disparadores[i];
                    break;
                }
            }
            
            if (d != NULL) {
                reconectaCarregadores(d, esq, dir);
            } else {
                d = criaDisparador(id_disp, 0.0, 0.0, esq, dir);
                if (d != NULL && repo_interno->num_disparadores < MAX_OBJETOS) {
                    repo_interno->disparadores[repo_interno->num_disparadores] = d;
                    repo_interno->num_disparadores++;
                }
            }
            
            if (d != NULL) {
                fprintf(arquivo_txt, "    Disparador %d conectado: carregador %d (esq) e %d (dir)\n", 
                        id_disp, id_esq, id_dir);
                instrucoes_realizadas++;
            }
        }
        
        //shft: preparar disparo - shft d [e|d] n
        else if (strcmp(comando, "shft") == 0) {
            int id, n;
            char lado;
            sscanf(linha_buffer, "shft %d %c %d", &id, &lado, &n);
            
            Disparador d = encontraOuCriaDisparador(repo, id);
            if (d != NULL) {
                preparaDisparo(d, lado, n);
                
                Forma forma_pronta = getDisparadorFormaPronta(d);
                if (forma_pronta != NULL) {
                    fprintf(arquivo_txt, "    Forma pronta para disparo no disparador %d:\n", id);
                    imprimeDetalhesForma(forma_pronta, arquivo_txt);
                } else {
                    fprintf(arquivo_txt, "    Nenhuma forma disponível no disparador %d\n", id);
                }
                instrucoes_realizadas++;
            }
        }
        
        //dsp: Disparo - dsp d dx dy [v|i]
        else if (strcmp(comando, "dsp") == 0) {
            int id;
            double dx, dy;
            char flag[4] = "";
            
            int num_params = sscanf(linha_buffer, "dsp %d %lf %lf %3s", &id, &dx, &dy, flag);
            
            Disparador d = encontraOuCriaDisparador(repo, id);
            if (d != NULL) {
                double x_disp = getDisparadorX(d);
                double y_disp = getDisparadorY(d);
                
                Forma forma_disparada = dispara(d, dx, dy);
                
                if (forma_disparada != NULL) {
                    total_disparos++;
                    
                    double x_final = getFormaX(forma_disparada);
                    double y_final = getFormaY(forma_disparada);
                    
                    fprintf(arquivo_txt, "    Forma disparada:\n");
                    imprimeDetalhesForma(forma_disparada, arquivo_txt);
                    fprintf(arquivo_txt, "    Posição inicial disparador: (%.2f, %.2f)\n", x_disp, y_disp);
                    fprintf(arquivo_txt, "    Posição final forma: (%.2f, %.2f)\n", x_final, y_final);
                    
                    insereFormaArena(arena, forma_disparada);
                    
                    //tratamento da flag "v" - criar anotações visuais
                    if (num_params == 4 && strcmp(flag, "v") == 0) {
                        fprintf(arquivo_txt, "    [Flag visual 'v' ativada]\n");
                        
                        //marcador do disparador (número vermelho)
                        char id_str[16];
                        sprintf(id_str, "%d", id);
                        Estilo estilo_marcador = criarEstilo("sans-serif", "bold", "16px");
                        Texto texto_id = criarTexto(-1000 - id, x_disp, y_disp, 
                                                    "red", "red", 'm', id_str, estilo_marcador);
                        destroiEstilo(estilo_marcador);
                        Forma forma_marcador = criaForma(-1000 - id, TIPO_TEXTO, texto_id);
                        enfileira(filaSVG, forma_marcador);
                        
                        //linha de projeção Y (vertical)
                        Linha proj_y = criarLinha(-2000 - total_disparos, 
                                                 x_final, y_disp, 
                                                 x_final, y_final, 
                                                 "red", false, 0);
                        setPontilhadaLinha(proj_y, true);
                        setSWLinha(proj_y, 1.0);
                        Forma forma_proj_y = criaForma(-2000 - total_disparos, TIPO_LINHA, proj_y);
                        enfileira(filaSVG, forma_proj_y);
                        
                        //linha de projeção X (horizontal)
                        Linha proj_x = criarLinha(-3000 - total_disparos, 
                                                 x_disp, y_final, 
                                                 x_final, y_final, 
                                                 "red", false, 0);
                        setPontilhadaLinha(proj_x, true);
                        setSWLinha(proj_x, 1.0);
                        Forma forma_proj_x = criaForma(-3000 - total_disparos, TIPO_LINHA, proj_x);
                        enfileira(filaSVG, forma_proj_x);
                        
                        fprintf(arquivo_txt, "      Anotações visuais criadas\n");
                    }
                    
                    instrucoes_realizadas++;
                } else {
                    fprintf(arquivo_txt, "    Falha: Nenhuma forma na posição de disparo\n");
                }
            }
        }
        
        //rjd: rajada de disparos - rjd d [e|d] dx dy ix iy
        else if (strcmp(comando, "rjd") == 0) {
            int id;
            char lado;
            double dx, dy, ix, iy;
            
            sscanf(linha_buffer, "rjd %d %c %lf %lf %lf %lf", &id, &lado, &dx, &dy, &ix, &iy);
            
            Disparador d = encontraOuCriaDisparador(repo, id);
            if (d != NULL) {
                fprintf(arquivo_txt, "    Iniciando rajada de disparos no disparador %d (lado %c):\n", id, lado);
                
                int disparos_rajada = 0;
                int i = 0;
                
                while (true) {
                    preparaDisparo(d, lado, 1);
                    
                    Forma forma_pronta = getDisparadorFormaPronta(d);
                    if (forma_pronta == NULL) {
                        break;
                    }
                    
                    double dx_atual = dx + i * ix;
                    double dy_atual = dy + i * iy;
                    
                    Forma forma_disparada = dispara(d, dx_atual, dy_atual);
                    
                    if (forma_disparada != NULL) {
                        total_disparos++;
                        disparos_rajada++;
                        
                        fprintf(arquivo_txt, "      Disparo %d: deslocamento (%.2f, %.2f)\n", 
                                disparos_rajada, dx_atual, dy_atual);
                        imprimeDetalhesForma(forma_disparada, arquivo_txt);
                        
                        insereFormaArena(arena, forma_disparada);
                    }
                    
                    i++;
                }
                
                fprintf(arquivo_txt, "    Total de disparos na rajada: %d\n", disparos_rajada);
                instrucoes_realizadas++;
            }
        }
        
        //calc: Calcular colisões e processar arena
        else if (strcmp(comando, "calc") == 0) {
            instrucoes_realizadas++;
            
            processaInteracoesArena(arena, chao, pontuacao_total, filaSVG, arquivo_txt, 
                                   &formas_clonadas, &formas_esmagadas, repo);
        }
    }
    
    //ao final, adicionar todas as anotações visuais ao chão para serem desenhadas
    while (!estaVaziaFila(filaSVG)) {
        Forma anotacao = desenfileira(filaSVG);
        adicionaFormaChao(chao, anotacao);
    }
    
    //relatório final
    fprintf(arquivo_txt, "\n===== RELATÓRIO FINAL =====\n");
    fprintf(arquivo_txt, "Pontuação total: %.2f\n", *pontuacao_total);
    fprintf(arquivo_txt, "Número de instruções realizadas: %d\n", instrucoes_realizadas);
    fprintf(arquivo_txt, "Número total de disparos: %d\n", total_disparos);
    fprintf(arquivo_txt, "Número de formas esmagadas: %d\n", formas_esmagadas);
    fprintf(arquivo_txt, "Número de formas clonadas: %d\n", formas_clonadas);
    fprintf(arquivo_txt, "===============================\n");
    
    if (formas_clonadas_out != NULL) *formas_clonadas_out = formas_clonadas;
    if (formas_esmagadas_out != NULL) *formas_esmagadas_out = formas_esmagadas;
    
    destroiFila(filaSVG);
    destroiRepositorio(repo);
    fclose(arquivo_qry);
    fclose(arquivo_txt);
}