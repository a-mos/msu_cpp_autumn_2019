CC = g++
CFLAGS = -std=c++14 -O2
default: run

run: gen sort tests
	./tests output

gen: generate_test.cpp
	g++ generate_test.cpp $(CFLAGS) -o gen
	./gen test 5

sort: sort.cpp
	g++ sort.cpp $(CFLAGS) -o sort
	./sort test output

test: gen sort tests
	./tests output

tests:
	g++ tests.cpp $(CFLAGS) -o tests

clean:
	rm -f gen
	rm -f sort
	rm -f tests