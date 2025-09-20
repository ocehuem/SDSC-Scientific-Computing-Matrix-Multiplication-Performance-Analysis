CC=g++
CFLAGS=-Wall -O3
mycontainer: main.cpp mycontainer.h
	$(CC) $(CFLAGS) $^ -o $@

run:
	./mycontainer

.phony: clean

clean:
	rm -f mycontainer
