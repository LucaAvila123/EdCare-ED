
################################# 
#####==== MEU MAKEFILE =====#####
################################# 

# Nome do projeto
PROJ_NAME = prog.out

# Compilador
CC = gcc

# Todos os arquivos .c dentro de source
C_FILES = $(wildcard ./src/*.c)

# Todos os arquivos .h dentro de source
H_FILES = $(wildcard ./src/include/*.h)

OUT_FILES = $(wildcard ./Saidas/*.txt)

# Substitui .c por .o, e source por objects no endereco de cada arquivo .c
O_FILES = $(subst .c,.o,$(subst src,obj,$(C_FILES)))

#Todas as flags usadas na compilacao
CC_FLAGS = -Isrc/include -g -W -Wall -lm

#Para executar tudo basta criar a pasta dos objetos e compilar todo o projeto
all: ObjFolder ./bin/$(PROJ_NAME)

#Cria uma pasta onde ficarao os arquivos .o
ObjFolder:
	@mkdir -p obj

#Cria o executavel do programa linkando todos os arquivos .o
./bin/$(PROJ_NAME): $(O_FILES)
	@ echo "\033[1;36m"
	@ echo "Creating $(PROJ_NAME) ..."
	@ echo "\033[0m"
	
	$(CC) $^ -o $@


#Compila todos os arquivos .c em arquivos .o e atualiza os arquivos .h
./obj/%.o: ./src/%.c ./src/include/%.h
	@ echo "\033[1;36m"
	@ echo "Compiling $< ..."
	@ echo "\033[0m"

	$(CC) -c $< $(CC_FLAGS) -o $@


#Compila o arquivo main.c em um arquivo main.o
./obj/main.o: ./src/main.c $(H_FILES)
	@ echo "\033[1;36m"
	@ echo "Compiling main.c ..."
	@ echo "\033[0m"

	$(CC) $< -c $(CC_FLAGS) -o $@


#Roda o programa
run:
	@ echo "\033[1;36m"
	@ echo "Running $(PROJ_NAME) ..."
	@ echo "\033[0m"
	@ rm -rf $(OUT_FILES)
	@ ./bin/$(PROJ_NAME)

#Limpa todos os arquivos compila e roda o programa
test: clean all run

valgrind: 
	@ echo "\033[1;36m"
	@ echo "Running valgrind ..."
	@ echo "\033[0m"
	@ valgrind --leak-check=yes ./bin/$(PROJ_NAME)

clean: 
	@ echo "\033[1;36m"
	@ echo "Removing temporary files ..."
	@ rm -rf $(O_FILES) bin/$(PROJ_NAME) $(OUT_FILES)
	@ echo "\033[0m"
	