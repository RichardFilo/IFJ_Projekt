CC=gcc
CFLAGS = -g -Wall
TARGETS = test

all: $(TARGETS)

test: stackINT.o mystring.o test.c

stackINT.o: stackINT.c

mystring.o: mystring.c

clean:
	$(RM) *.o $(TARGETS)
