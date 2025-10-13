#include "svg.h"
#include "fila.h"
#include "formas.h"

#include <stdio.h>

FILE* inicializaSvg(char *caminho, double largura, double altura) {
    FILE *svg = fopen(caminho, "w");
    if (svg == NULL) {
        perror("Erro ao abrir arquivo SVG");
        return NULL;
    }

    // Cabeçalho SVG com viewBox
    fprintf(svg, "<svg width=\"100%%\" height=\"100%%\" viewBox=\"0 0 %.0f %.0f\" xmlns=\"http://www.w3.org/2000/svg\">\n", 
            largura, altura);
    
    // Fundo cinza claro
    fprintf(svg, "\t<rect width=\"100%%\" height=\"100%%\" fill=\"#f0f0f0\" />\n");
    
    return svg;
}

void fechaSvg(FILE *svg) {
    if (svg == NULL) return;
    
    fprintf(svg, "\n</svg>");
    fclose(svg);
}