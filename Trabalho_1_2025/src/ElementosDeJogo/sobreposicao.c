
#include "sobreposicao.h"

#include "formas.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

#include <math.h>
#include <string.h>

//função auxiliar para calcular distância ao quadrado
static double distanciaQuadrada(double x1, double y1, double x2, double y2) {
    double dx = x1 - x2;
    double dy = y1 - y2;
    return dx * dx + dy * dy;
}

//função auxiliar para verificar se ponto está dentro de retângulo
static bool pontoDentroRetangulo(Retangulo r, double px, double py) {
    double x = getXRetangulo(r);
    double y = getYRetangulo(r);
    double w = getLarguraRetangulo(r);
    double h = getAlturaRetangulo(r);
    
    return (px >= x && px <= x + w && py >= y && py <= y + h);
}

bool sobreposicaoCirculoCirculo(Circulo c1, Circulo c2) {
    double x1 = getXCirculo(c1);
    double y1 = getYCirculo(c1);
    double r1 = getRCirculo(c1);
    
    double x2 = getXCirculo(c2);
    double y2 = getYCirculo(c2);
    double r2 = getRCirculo(c2);
    
    double distCentros = distanciaQuadrada(x1, y1, x2, y2);
    double somaRaios = (r1 + r2) * (r1 + r2);
    
    return distCentros <= somaRaios;
}

bool sobreposicaoCirculoRetangulo(Circulo c, Retangulo r) {
    double cx = getXCirculo(c);
    double cy = getYCirculo(c);
    double raio = getRCirculo(c);
    
    double rx = getXRetangulo(r);
    double ry = getYRetangulo(r);
    double w = getLarguraRetangulo(r);
    double h = getAlturaRetangulo(r);
    
    //econtra o ponto mais próximo do círculo no retângulo
    double px = cx;
    double py = cy;
    
    if (cx < rx) px = rx;
    else if (cx > rx + w) px = rx + w;
    
    if (cy < ry) py = ry;
    else if (cy > ry + h) py = ry + h;
    
    double dist = distanciaQuadrada(cx, cy, px, py);
    return dist <= raio * raio;
}

bool sobreposicaoCirculoLinha(Circulo c, Linha l) {
    double cx = getXCirculo(c);
    double cy = getYCirculo(c);
    double r = getRCirculo(c);
    
    double x1 = getX1Linha(l);
    double y1 = getY1Linha(l);
    double x2 = getX2Linha(l);
    double y2 = getY2Linha(l);
    
    //verifica extremidades
    double dist1 = distanciaQuadrada(cx, cy, x1, y1);
    double dist2 = distanciaQuadrada(cx, cy, x2, y2);
    double rQuad = r * r;
    
    if (dist1 <= rQuad || dist2 <= rQuad) return true;
    
    //projeção do centro no segmento
    double compQuad = distanciaQuadrada(x1, y1, x2, y2);
    if (compQuad == 0) return false;
    
    double t = ((cx - x1) * (x2 - x1) + (cy - y1) * (y2 - y1)) / compQuad;
    
    if (t < 0 || t > 1) return false;
    
    double px = x1 + t * (x2 - x1);
    double py = y1 + t * (y2 - y1);
    
    return distanciaQuadrada(cx, cy, px, py) <= rQuad;
}

bool sobreposicaoCirculoTexto(Circulo c, Texto t) {
    double x1, y1, x2, y2;
    converterTextoParaLinha(t, &x1, &y1, &x2, &y2);
    
    //cria linha temporária
    Linha temp = criarLinha(-1, x1, y1, x2, y2, "temp", false, 0);
    bool resultado = sobreposicaoCirculoLinha(c, temp);
    destroiLinha(temp);
    
    return resultado;
}

bool sobreposicaoRetanguloRetangulo(Retangulo r1, Retangulo r2) {
    double x1 = getXRetangulo(r1);
    double y1 = getYRetangulo(r1);
    double w1 = getLarguraRetangulo(r1);
    double h1 = getAlturaRetangulo(r1);
    
    double x2 = getXRetangulo(r2);
    double y2 = getYRetangulo(r2);
    double w2 = getLarguraRetangulo(r2);
    double h2 = getAlturaRetangulo(r2);
    
    bool sobreX = (x1 < x2 + w2) && (x1 + w1 > x2);
    bool sobreY = (y1 < y2 + h2) && (y1 + h1 > y2);
    
    return sobreX && sobreY;
}

bool sobreposicaoRetanguloLinha(Retangulo r, Linha l) {
    double x1 = getX1Linha(l);
    double y1 = getY1Linha(l);
    double x2 = getX2Linha(l);
    double y2 = getY2Linha(l);
    
    //verifica se extremidades estão dentro
    if (pontoDentroRetangulo(r, x1, y1) || pontoDentroRetangulo(r, x2, y2)) {
        return true;
    }
    
    double rx = getXRetangulo(r);
    double ry = getYRetangulo(r);
    double w = getLarguraRetangulo(r);
    double h = getAlturaRetangulo(r);
    
    //verifica interseção com cada borda
    Linha bordas[4];
    bordas[0] = criarLinha(-1, rx, ry, rx + w, ry, "temp", false, 0);         // topo
    bordas[1] = criarLinha(-1, rx + w, ry, rx + w, ry + h, "temp", false, 0); // direita
    bordas[2] = criarLinha(-1, rx + w, ry + h, rx, ry + h, "temp", false, 0); // baixo
    bordas[3] = criarLinha(-1, rx, ry + h, rx, ry, "temp", false, 0);         // esquerda
    
    int i;
    for (i = 0; i < 4; i++) {
        if (sobreposicaoLinhaLinha(l, bordas[i])) {
            int j;
            for (j = 0; j < 4; j++) destroiLinha(bordas[j]);
            return true;
        }
    }
    
    for (i = 0; i < 4; i++) destroiLinha(bordas[i]);
    return false;
}

bool sobreposicaoRetanguloTexto(Retangulo r, Texto t) {
    double x1, y1, x2, y2;
    converterTextoParaLinha(t, &x1, &y1, &x2, &y2);
    
    Linha temp = criarLinha(-1, x1, y1, x2, y2, "temp", false, 0);
    bool resultado = sobreposicaoRetanguloLinha(r, temp);
    destroiLinha(temp);
    
    return resultado;
}

bool sobreposicaoLinhaLinha(Linha l1, Linha l2) {
    double x1 = getX1Linha(l1);
    double y1 = getY1Linha(l1);
    double x2 = getX2Linha(l1);
    double y2 = getY2Linha(l1);
    
    double x3 = getX1Linha(l2);
    double y3 = getY1Linha(l2);
    double x4 = getX2Linha(l2);
    double y4 = getY2Linha(l2);
    
    int o1 = orientacao(x1, y1, x2, y2, x3, y3);
    int o2 = orientacao(x1, y1, x2, y2, x4, y4);
    int o3 = orientacao(x3, y3, x4, y4, x1, y1);
    int o4 = orientacao(x3, y3, x4, y4, x2, y2);
    
    //caso geral
    if (o1 != o2 && o3 != o4) return true;
    
    //casos especiais (colineares)
    if (o1 == 0 && pontoNoSegmento(x1, y1, x3, y3, x2, y2)) return true;
    if (o2 == 0 && pontoNoSegmento(x1, y1, x4, y4, x2, y2)) return true;
    if (o3 == 0 && pontoNoSegmento(x3, y3, x1, y1, x4, y4)) return true;
    if (o4 == 0 && pontoNoSegmento(x3, y3, x2, y2, x4, y4)) return true;
    
    return false;
}

bool sobreposicaoLinhaTexto(Linha l, Texto t) {
    double x1, y1, x2, y2;
    converterTextoParaLinha(t, &x1, &y1, &x2, &y2);
    
    Linha temp = criarLinha(-1, x1, y1, x2, y2, "temp", false, 0);
    bool resultado = sobreposicaoLinhaLinha(l, temp);
    destroiLinha(temp);
    
    return resultado;
}

bool sobreposicaoTextoTexto(Texto t1, Texto t2) {
    double x1, y1, x2, y2;
    double x3, y3, x4, y4;
    
    converterTextoParaLinha(t1, &x1, &y1, &x2, &y2);
    converterTextoParaLinha(t2, &x3, &y3, &x4, &y4);
    
    Linha temp1 = criarLinha(-1, x1, y1, x2, y2, "temp", false, 0);
    Linha temp2 = criarLinha(-1, x3, y3, x4, y4, "temp", false, 0);
    
    bool resultado = sobreposicaoLinhaLinha(temp1, temp2);
    
    destroiLinha(temp1);
    destroiLinha(temp2);
    
    return resultado;
}

void converterTextoParaLinha(Texto t, double *x1, double *y1, double *x2, double *y2) {
    if (t == NULL || x1 == NULL || y1 == NULL || x2 == NULL || y2 == NULL) return;
    
    double xt = getXTexto(t);
    double yt = getYTexto(t);
    char ancora = getAncora(t);
    char *str = getTexto(t);
    int numCaracteres = strlen(str);
    
    double comprimento = 10.0 * numCaracteres;
    
    *y1 = yt;
    *y2 = yt;
    
    switch (ancora) {
        case 'i':
            *x1 = xt;
            *x2 = xt + comprimento;
            break;
        case 'm':
            *x1 = xt - comprimento / 2.0;
            *x2 = xt + comprimento / 2.0;
            break;
        case 'f':
            *x1 = xt - comprimento;
            *x2 = xt;
            break;
        default:
            *x1 = xt;
            *x2 = xt;
            break;
    }
}

int orientacao(double px, double py, double qx, double qy, double rx, double ry) {
    double val = (qy - py) * (rx - qx) - (qx - px) * (ry - qy);
    if (fabs(val) < 1e-10) return 0;  //colinear
    return (val > 0) ? 1 : 2;  //1: horário, 2: anti-horário
}

bool pontoNoSegmento(double px, double py, double qx, double qy, double rx, double ry) {
    return (qx <= fmax(px, rx) && qx >= fmin(px, rx) &&
            qy <= fmax(py, ry) && qy >= fmin(py, ry));
}

double calculaAreaForma(Forma f) {
    if (f == NULL) return 0.0;
    
    TipoForma tipo = getFormaTipo(f);
    
    switch (tipo) {
        case TIPO_CIRCULO:
            return calculaAreaCirculo((Circulo)f);
            
        case TIPO_RETANGULO:
            return calculaAreaRetangulo((Retangulo)f);
            
        case TIPO_LINHA: {
            Linha l = (Linha)f;
            double comp = calculaComprimentoLinha(l);
            return 2.0 * comp;
        }
            
        case TIPO_TEXTO: {
            Texto t = (Texto)f;
            char *str = getTexto(t);
            int numCaracteres = strlen(str);
            return 20.0 * numCaracteres;
        }
            
        default:
            return 0.0;
    }
}