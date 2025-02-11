.PHONY: test clean cov
CPPflags=-std=c++2c -Wall -pedantic -Wextra -Wreturn-type -Wvexing-parse

test:	tests.cpp utest.hpp image.hpp image.cpp
	g++ $(CPPflags) tests.cpp image.cpp -o test

clean:
	rm *.gcov *.gcda *.gcno coverage.info
	rm -rf coverage 
	rm -rf *.dSYM

cov:
	g++ -std=c++2c -Wall -pedantic -Wextra -Wreturn-type -g --coverage tests.cpp image.cpp -o test
	./test
	lcov --capture --directory . --output-file coverage.info --ignore-errors unsupported,format
	genhtml --ignore-errors category coverage.info --output-directory coverage
