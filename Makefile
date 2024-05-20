FLAGS=-Wall -Wextra -Werror -std=c11
LFLAGS=-lcheck -lm

ifeq ($(shell uname), Linux)
	LFLAGS=-lcheck -lm -lsubunit
endif

all: s21_string.a

s21_string.a:
	gcc -c $(FLAGS) s21_string.c
	ar rc s21_string.a s21_string.o
	ranlib s21_string.a

test: s21_string.a
	gcc $(FLAGS) -c unittests.c 
	gcc $(FLAGS) unittests.o -L. s21_string.a $(LFLAGS) -o test

rebuild: clean all

clean:
	rm -rf report
	rm -f s21_string.a *.o test* *.gcno *.gcda

gcov_report: clean add_coverage test
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

add_coverage:
	$(eval FLAGS += --coverage)

.PHONY: s21_string.a test rebuild clean gcov_report add_coverage
