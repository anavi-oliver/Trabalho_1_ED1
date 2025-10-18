PROJ_NAME=ted

ALUNO=Ana Vitoria Oliver Machado
LIBS=-lm
SOURCES := $(shell find . -name '*.c')
OBJETOS := $(SOURCES:.c=.o)

CC=gcc

INCLUDE_DIRS := $(shell find . -type d)
INCLUDES := $(patsubst %,-I%,$(INCLUDE_DIRS))

#flags de compilação
CFLAGS=-ggdb -O0 -std=c99 -fstack-protector-all -Werror=implicit-function-declaration -Wall -Wextra $(INCLUDES)

#flags de linkagem
LDFLAGS=-O0

.PHONY: all clean ted

#atalho para ted
all: ted

ted: $(OBJETOS)
	$(CC) -o $(PROJ_NAME) $(LDFLAGS) $(OBJETOS) $(LIBS)
	@echo "Executável '$(PROJ_NAME)' criado com sucesso!"

#regra genérica para transformar qualquer .c em .o
%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

#regra para limpar os arquivos gerados
clean:
	find . -name '*.o' -delete
	rm -f $(PROJ_NAME)
	@echo "Arquivos compilados foram removidos."

#listar dependencias - os #include 

#elementos de jogo
ElementosDeJogo/arena.o: ElementosDeJogo/arena.c ElementosDeJogo/arena.h EstruturaDeDados/fila.h FormasGeometricas/formas.h FormasGeometricas/circulo.h FormasGeometricas/linha.h FormasGeometricas/retangulo.h FormasGeometricas/texto.h
ElementosDeJogo/carregador.o: ElementosDeJogo/carregador.c ElementosDeJogo/carregador.h ElementosDeJogo/chao.h EstruturaDeDados/fila.h FormasGeometricas/formas.h FormasGeometricas/circulo.h FormasGeometricas/linha.h FormasGeometricas/retangulo.h FormasGeometricas/texto.h
ElementosDeJogo/chao.o: ElementosDeJogo/chao.c ElementosDeJogo/chao.h EstruturaDeDados/fila.h FormasGeometricas/formas.h FormasGeometricas/circulo.h FormasGeometricas/linha.h FormasGeometricas/retangulo.h FormasGeometricas/texto.h
ElementosDeJogo/disparador.o: ElementosDeJogo/disparador.c ElementosDeJogo/disparador.h ElementosDeJogo/carregador.h ElementosDeJogo/chao.h EstruturaDeDados/fila.h FormasGeometricas/formas.h FormasGeometricas/circulo.h FormasGeometricas/linha.h FormasGeometricas/retangulo.h FormasGeometricas/texto.h ElementosDeJogo/arena.h
ElementosDeJogo/sobreposicao.o: ElementosDeJogo/sobreposicao.c ElementosDeJogo/sobreposicao.h FormasGeometricas/formas.h FormasGeometricas/circulo.h FormasGeometricas/linha.h FormasGeometricas/retangulo.h FormasGeometricas/texto.h

#estrutura de dados
EstruturaDeDados/fila.o: EstruturaDeDados/fila.c EstruturaDeDados/fila.h 
EstruturaDeDados/pilha.o: EstruturaDeDados/pilha.c EstruturaDeDados/pilha.h

#formas geometricas
FormasGeometricas/circulo.o: FormasGeometricas/circulo.c FormasGeometricas/circulo.h
FormasGeometricas/formas.o: FormasGeometricas/formas.c FormasGeometricas/formas.h FormasGeometricas/circulo.h FormasGeometricas/linha.h FormasGeometricas/retangulo.h FormasGeometricas/texto.h
FormasGeometricas/linha.o: FormasGeometricas/linha.c FormasGeometricas/linha.h
FormasGeometricas/retangulo.o: FormasGeometricas/retangulo.c FormasGeometricas/retangulo.h
FormasGeometricas/texto.o: FormasGeometricas/texto.c FormasGeometricas/texto.h

#modulos de ambiente
ModulosDeAmbiente/processaGeo.o: ModulosDeAmbiente/processaGeo.c ModulosDeAmbiente/processaGeo.h ElementosDeJogo/chao.h FormasGeometricas/formas.h FormasGeometricas/circulo.h FormasGeometricas/linha.h FormasGeometricas/retangulo.h FormasGeometricas/texto.h
ModulosDeAmbiente/processaQry.o: ModulosDeAmbiente/processaQry.c ModulosDeAmbiente/processaQry.h ElementosDeJogo/disparador.h ElementosDeJogo/carregador.h ElementosDeJogo/chao.h EstruturaDeDados/fila.h FormasGeometricas/formas.h ElementosDeJogo/arena.h FormasGeometricas/circulo.h FormasGeometricas/linha.h FormasGeometricas/retangulo.h FormasGeometricas/texto.h
ModulosDeAmbiente/svg.o: ModulosDeAmbiente/svg.c ModulosDeAmbiente/svg.h EstruturaDeDados/fila.h FormasGeometricas/formas.h FormasGeometricas/circulo.h FormasGeometricas/linha.h FormasGeometricas/retangulo.h FormasGeometricas/texto.h

#main
main.o: main.c ElementosDeJogo/arena.h ElementosDeJogo/chao.h FormasGeometricas/formas.h ModulosDeAmbiente/svg.h ModulosDeAmbiente/processaGeo.h ModulosDeAmbiente/processaQry.h