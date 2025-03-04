.PHONY: all clean rebuild s21_decimal.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
SOURCES = $(wildcard *.c)
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))
TEST = ./tests/test_s21_decimal.c
GCOV_FL = -fprofile-arcs -ftest-coverage -lcheck -lm -pthread
OS = $(shell uname)
ifeq ($(OS), Linux)
	TFLAGS = -lcheck -pthread -lrt -lm -lsubunit
else
	TFLAGS = -lcheck -coverage
endif

all: s21_decimal.a

s21_decimal.a: $(OBJECTS)
	ar rcs s21_decimal.a $(OBJECTS)
	ranlib s21_decimal.a

test_s21_decimal.o: $(TEST) s21_decimal.h
	$(CC) $(CFLAGS) -g -c $(TEST)

test: s21_decimal.a test_s21_decimal.o
	$(CC) $(CFLAGS) ./tests/*.c $(TFLAGS) s21_decimal.a -lm -o test
	./test

gcov_report: s21_decimal.a
	$(CC) $(CFLAGS) s21_decimal.a ./tests/*.c $(SOURCES) $(GCOV_FL) -o report
	./report
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage-report
	open coverage-report/index.html

style_check:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -n tests/*.c tests/*.h *.c *.h
	rm -f .clang-format

style_get:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -i tests/*.c tests/*.h *.c *.h
	rm -f .clang-format

clean:
	rm -rf *.o *.a temp *.gcda *.gcno test test.dSYM report coverage-report coverage.info

rebuild:
	make clean
	make all
