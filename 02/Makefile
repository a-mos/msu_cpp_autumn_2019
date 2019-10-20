CC = g++
CFLAGS = -std=c++14 -O2
default: run

run: alloc
	./alloc 100 maxsize
alloc: alloc.cpp
	$(CC) alloc.cpp $(CFLAGS) -o $@
test: alloc
	python3 check.py
clean:
	rm -f alloc