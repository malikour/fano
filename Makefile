CC      = gcc
CFLAGS  = -O2 
LDFLAGS =

fano_EXEC = fano
all:	fano

fano: 	traite_arg.o fano.o
	$(CC) $(CFLAGS) -o $(fano_EXEC) traite_arg.o fano.o

clean:
	rm -f *.o fano
