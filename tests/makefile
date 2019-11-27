CC=gcc
CFLAGS = -g -Wall
TARGETS = LAtest

all: $(TARGETS)

LAtest: stackINT.o mystring.o scanner.o LAtest.c

stackINT.o: ../projekt/stackINT.c
	$(CC) $(CFLAGS) -c $<

mystring.o: ../projekt/mystring.c
	$(CC) $(CFLAGS) -c $<

scanner.o: ../projekt/scanner.c
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) *.o $(TARGETS)
