CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11
LFLAGS=-lcheck -lpthread -lsubunit -lm
GCOV_FLAGS=-fprofile-arcs -ftest-coverage -fPIC
CFILES=s21_matrix.a
CEXE=s21_test


#CFLAGS=-Wall -Werror -Wextra -std=c11 -g#-g for valgrind, -Wpedantic also can be added, -lm for <math.h>
#VFLAGS=--track-origins=yes --tool=memcheck --vgdb=no --leak-check=full --show-leak-kinds=all --verbose
#TFLAGS = -lcheck -lpthread

#============= FLAGS FOR OS ======================================================== 
UNAME:=$(shell uname -s)
ifeq ($(UNAME),Linux)
	LDFLAGS=-lcheck -lsubunit -lm -lrt -lpthread
	OPEN_CM=xdg-open
endif
ifeq ($(UNAME),Darwin)
	LDFLAGS=-lcheck -lm
	OPEN_CM=open
endif

#============= ALL ==================================================================
all: clean ${CFILES} test

#============= LIBRIRY & TEST LIBRARY================================================

s21_matrix.a:
	${CC} ${CFLAGS} -c modules/*.c
	ar rc ${CFILES} *.o
	ranlib ${CFILES}
	rm -f *.o

gcov_s21_matrix.a: clean
	${CC} ${CFLAGS} -c modules/*.c ${GCOV_FLAGS}
	ar rc s21_matrix.a *.o
	ranlib s21_matrix.a
	rm -f *.o

vg: clean s21_matrix.a
	$(CC) ${CFLAGS} tests/*.c  ${CFILES} -o ${CEXE} ${LDFLAGS}
	chmod a+x ${CEXE}
	valgrind --tool=memcheck --leak-check=yes --leak-check=full ./${CEXE}
	rm -rf *.gcno
#============= TEST ==============================================================

test: clean s21_matrix.a
	$(CC) ${CFLAGS} tests/*.c  ${CFILES} -o ${CEXE} ${LDFLAGS}
	./${CEXE}

gcov_report: clean gcov_s21_matrix.a
	$(CC) ${CFLAGS} tests/*.c s21_matrix.a -o ${CEXE} ${LDFLAGS} ${GCOV_FLAGS}
	mkdir report
	./${CEXE} >> report/s21_report.txt
	lcov -c -d . -o coverage.info
	genhtml coverage.info --output-directory report
	rm -rf *.gcda *.gcno *.info
	open report/index.html
	

#=========== STYLE ====================================================================
format_check:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -n tests/*.c modules/*.c *.h
	rm -f .clang-format

format:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -i tests/*.c modules/*.c *.h
	rm -f .clang-format

#========== CLEAN ======================================================================
clean:
	rm -rf *.o
	rm -rf *.out
	rm -rf *.a
	rm -rf s21_test
	rm -rf *.gcno
	rm -rf *.gcda
	rm -rf *.gcov
	rm -rf *.log
	rm -rf *.html
	rm -rf *.css
	rm -rf report
	rm -rf *.dSYM
	rm -rf *.info

