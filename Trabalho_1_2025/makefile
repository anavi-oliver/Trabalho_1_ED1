PROJ_NAME=ted

ALUNO= Ana Vitoria Oliver Machado
LIBS=-lm
SOURCES := $(shell find src -name '*.c') #descoberta automática dos arquivos fonte
OBJETOS := $(SOURCES:.c=.o) #cria a lista de arquivos objeto a partir dos fontes

CC=gcc

INCLUDE_DIRS := $(shell find src -type d) .
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
	rm -f $(OBJETOS) $(PROJ_NAME)
	@echo "Arquivos compilados foram removidos."

#listar dependencias - os #include 

#elementos de jogo
src/ElementosDeJogo/arena.o: src/ElementosDeJogo/arena.c src/ElementosDeJogo/arena.h src/EstruturaDeDados/fila.h src/FormasGeometricas/formas.h src/FormasGeometricas/circulo.h src/FormasGeometricas/linha.h src/FormasGeometricas/retangulo.h src/FormasGeometricas/texto.h
src/ElementosDeJogo/carregador.o: src/ElementosDeJogo/carregador.c src/ElementosDeJogo/carregador.h src/ElementosDeJogo/chao.h src/EstruturaDeDados/fila.h src/FormasGeometricas/formas.h src/FormasGeometricas/circulo.h src/FormasGeometricas/linha.h src/FormasGeometricas/retangulo.h src/FormasGeometricas/texto.h
src/ElementosDeJogo/chao.o: src/ElementosDeJogo/chao.c src/ElementosDeJogo/chao.h src/EstruturaDeDados/fila.h src/FormasGeometricas/formas.h src/FormasGeometricas/circulo.h src/FormasGeometricas/linha.h src/FormasGeometricas/retangulo.h src/FormasGeometricas/texto.h
src/ElementosDeJogo/disparador.o: src/ElementosDeJogo/disparador.c src/ElementosDeJogo/disparador.h src/ElementosDeJogo/carregador.h src/ElementosDeJogo/chao.h src/EstruturaDeDados/fila.h src/FormasGeometricas/formas.h src/FormasGeometricas/circulo.h src/FormasGeometricas/linha.h src/FormasGeometricas/retangulo.h src/FormasGeometricas/texto.h
src/ElementosDeJogo/colisao.o: src/ElementosDeJogo/colisao.c src/ElementosDeJogo/colisao.h src/FormasGeometricas/formas.h src/FormasGeometricas/circulo.h src/FormasGeometricas/linha.h src/FormasGeometricas/retangulo.h src/FormasGeometricas/texto.h

#estrutura de dados
src/EstruturaDeDados/fila.o: src/EstruturaDeDados/fila.c src/EstruturaDeDados/fila.h 
src/EstruturaDeDados/pilha.o: src/EstruturaDeDados/pilha.c src/EstruturaDeDados/pilha.h

#formas geometricas
src/FormasGeometricas/circulo.o: src/FormasGeometricas/circulo.c src/FormasGeometricas/circulo.h
src/FormasGeometricas/formas.o: src/FormasGeometricas/formas.c src/FormasGeometricas/formas.h src/FormasGeometricas/circulo.h src/FormasGeometricas/linha.h src/FormasGeometricas/retangulo.h src/FormasGeometricas/texto.h
src/FormasGeometricas/linha.o: src/FormasGeometricas/linha.c src/FormasGeometricas/linha.h
src/FormasGeometricas/retangulo.o: src/FormasGeometricas/retangulo.c src/FormasGeometricas/retangulo.h
src/FormasGeometricas/texto.o: src/FormasGeometricas/texto.c src/FormasGeometricas/texto.h

#modulos de ambiente
src/ModulosDeAmbiente/processaGeo.o: src/ModulosDeAmbiente/processaGeo.c src/ModulosDeAmbiente/processaGeo.h src/ElementosDeJogo/chao.h src/FormasGeometricas/formas.h src/FormasGeometricas/circulo.h src/FormasGeometricas/linha.h src/FormasGeometricas/retangulo.h src/FormasGeometricas/texto.h
src/ModulosDeAmbiente/processaQry.o: src/ModulosDeAmbiente/processaQry.c src/ModulosDeAmbiente/processaQry.h src/ElementosDeJogo/disparador.h src/ElementosDeJogo/carregador.h src/ElementosDeJogo/chao.h src/EstruturaDeDados/fila.h src/FormasGeometricas/formas.h src/ElementosDeJogo/arena.h src/FormasGeometricas/circulo.h src/FormasGeometricas/linha.h src/FormasGeometricas/retangulo.h src/FormasGeometricas/texto.h
src/ModulosDeAmbiente/svg.o: src/ModulosDeAmbiente/svg.c src/ModulosDeAmbiente/svg.h src/EstruturaDeDados/fila.h src/FormasGeometricas/formas.h src/FormasGeometricas/circulo.h src/FormasGeometricas/linha.h src/FormasGeometricas/retangulo.h src/FormasGeometricas/texto.h
