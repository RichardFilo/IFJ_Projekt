CC=gcc
CFLAGS = -g -Wall
TARGETS = test

all: $(TARGETS)

test: stackINT.o mystring.o scanner.o test.c

stackINT.o: stackINT.c

mystring.o: mystring.c

scanner.o: scanner.c

clean:
	$(RM) *.o $(TARGETS)
