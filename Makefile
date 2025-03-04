.PHONY: test clean cov all
CPPflags=-std=c++2c -Wall -pedantic -Wextra -Weverything -Wno-old-style-cast -Wno-c++98-compat

test:	tests.cpp utest.hpp image.hpp image.cpp
	g++ $(CPPflags) tests.cpp image.cpp -o test

test_debug: tests.cpp utest.hpp image.hpp image.cpp
	g++ $(CPPflags) -g tests.cpp image.cpp -o d_test

clean:
	rm *.gcov *.gcda *.gcno coverage.info
	rm -rf coverage 
	rm -rf *.dSYM
	rm test test_cov d_test

cov:
	g++ $(CPPflags) -g --coverage tests.cpp image.cpp -o test_cov
	./test_cov
	lcov --capture --directory . --output-file coverage.info --ignore-errors unsupported,format
	genhtml --ignore-errors category coverage.info --output-directory coverage

all: test
	./test