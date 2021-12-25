CC=cc
CFLAGS=-O3
OUT=templ.o gettemp.o util.o

all: templ

%.o: %.c
	$(CC) $(CFLAGS) -c $<

templ: $(OUT)
	$(CC) -g -o templ $(OUT)

.PHONY: clean

clean:
	rm -f *.o templ
