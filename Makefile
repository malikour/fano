CC      = gcc
CFLAGS  =
LDFLAGS =

all: fano

fano: fano.o
        $(CC) $(CFLAGS) $< -o $@

clean:
        rm -f *.o fano
