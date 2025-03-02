CC = gcc 
SOURCES1 = ./s21_grep.c
FLAGS = -Wall -Werror -Wextra -std=c11

EXE1 = ./s21_grep

all: s21_grep 

s21_grep:
	$(CC) $(FLAGS) $(SOURCES1) -o $(EXE1)

clean:
	rm -f *.o *.out ./s21_grep 
	
rebuild:
	@$(MAKE) clean
	@$(MAKE) all
