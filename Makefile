CC=gcc
CFLAGS=-O3
OUT=templ.o util.o pretty.o temp.o

all: templ

%.o: %.c
	$(CC) $(CFLAGS) -c $<

templ: $(OUT)
	$(CC) $(CFLAGS) -g -o templ $(OUT)

.PHONY: clean

clean:
	rm -f *.o templ
