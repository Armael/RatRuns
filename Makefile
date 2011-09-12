CFLAGS+= -Wall
LIBS+=-lX11

CC = gcc

TARGET=ratruns

all: $(TARGET)

ratruns:	ratruns.o
	$(CC) -o ratruns ratruns.o $(LIBS)

clean:
	rm -rf *.o

mproper:	clean
	rm $(TARGET)

.c.o:
	@$(CC) $(CFLAGS) -c -o $@ $<
