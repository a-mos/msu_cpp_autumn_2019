CC = g++
CFLAGS = -std=c++14 -O2
default: run

run: tests
	./tests
test: tests
	./tests
tests: tests.cpp vector.h
	$(CC) tests.cpp $(CFLAGS) -o $@
clean:
	rm -f tests