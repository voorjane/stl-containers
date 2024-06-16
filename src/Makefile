CC= g++
CFLAGS= -Wall -Wextra -Werror -std=c++17 -g
TESTFLAGS=-lgtest
TESTFILES= tests/*.cpp

all: test

test:
	$(CC) $(CFLAGS) $(TESTFILES) $(TESTFLAGS) -o test_s21_containers
	./test_s21_containers

clean:
	rm -rf test_containers report
	rm  test_s21_containers

clang:
	cp ../.clang-format .
	clang-format -i ./*.h tests/* s21_containers/*
	rm .clang-format

gcov_report:
	$(CC) $(CFLAGS) $(TESTFILES) $(TESTFLAGS) --coverage -o test_s21_containers
	./test_s21_containers
	lcov -t "test_s21_containers" -o test_s21_containers.info -c -d ./ --no-external
	genhtml -o report test_s21_containers.info
	open report/index.html
	rm *.gcno *.gcda *.info test_s21_containers

valgrind:
	$(CC) $(CFLAGS) $(TESTFILES) $(TESTFLAGS) -o test_s21_containers
	valgrind --leak-check=full --leak-resolution=med -s ./test_s21_containers

.PHONY: all test clean clang gcov_report valgrind
