CC=cc
CFLAGS=-O3

all: templ

%.o: %.c
	$(CC) $(CFLAGS) -c $<

templ: templ.o gettemp.o
	$(CC) -g -o templ templ.o gettemp.o

.PHONY: clean

clean:
	rm -f *.o templ
