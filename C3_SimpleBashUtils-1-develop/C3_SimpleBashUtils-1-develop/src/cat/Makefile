CC = gcc
FLAGS = -Wall -Werror -Wextra
SOURCES1 = ./s21_cat.c

EXE1 = ./s21_cat

all: s21_cat 

s21_cat:
	$(CC) $(FLAGS) $(SOURCES1) -o $(EXE1)

clean:
	rm -f *.o *.out ./s21_cat
rebuild:
	@$(MAKE) clean
	@$(MAKE) all
