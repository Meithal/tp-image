.PHONY: test clean cov
CPPflags=-std=c++2c -Wall -pedantic -Wextra -Wreturn-type -Wvexing-parse

test:	tests.cpp utest.hpp image.hpp image.cpp
	g++ $(CPPflags) tests.cpp image.cpp -o test

clean:
	rm *.gcov *.gcda *.gcno coverage.info
	rm -rf coverage 
	rm -rf *.dSYM
	rm test test_cov

cov:
	g++ $(CPPflags) -g --coverage tests.cpp image.cpp -o test_cov
	./test_cov
	lcov --capture --directory . --output-file coverage.info --ignore-errors unsupported,format
	genhtml --ignore-errors category coverage.info --output-directory coverage
