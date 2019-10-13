CC = g++
CFLAGS = -std=c++14 -O2
default: run

run: calc
	./calc "2 + 2"
calc: calc.cpp
	$(CC) calc.cpp $(CFLAGS) -o $@
test: calc
	python3 check.py
clean:
	rm -f calc