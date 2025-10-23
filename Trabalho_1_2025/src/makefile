# ======================= CONFIGURAÇÕES GERAIS =======================

PROJ_NAME = ted
CC = gcc

# Flags de compilação
CFLAGS = -g -Wall -Wextra -O0 -std=c99 -fstack-protector-all -Werror=implicit-function-declaration

# Flags de linkagem
LDFLAGS = -lm

# Busca automaticamente todos os diretórios e fontes
SRC_DIRS := $(shell find . -type d)
SOURCES := $(shell find . -name '*.c')
OBJECTS := $(SOURCES:.c=.o)

# Gera automaticamente os includes (-I)
INCLUDES := $(patsubst %,-I%,$(SRC_DIRS))

# ======================= REGRAS PADRÃO =======================

.PHONY: all clean ted run test1 test2

# Compila tudo e gera o executável
all: ted

ted: $(OBJECTS)
	$(CC) -o $(PROJ_NAME) $(OBJECTS) $(LDFLAGS)
	@echo "Executável '$(PROJ_NAME)' criado com sucesso!"

# Regra genérica de compilação (.c → .o)
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Limpa todos os objetos e o executável
clean:
	find . -name '*.o' -delete
	rm -f $(PROJ_NAME)
	@echo "Limpeza concluída."