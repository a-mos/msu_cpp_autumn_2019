CC = g++
CFLAGS = -std=c++14 -O2
default: run

run: tests
	./tests
test: tests
	python3 check.py
tests: tests.cpp Serializer.h
	$(CC) tests.cpp $(CFLAGS) -o $@
clean:
	rm -f tests