CC=gcc
CFLAGS = -g -Wall
TARGETS = LAtest

all: $(TARGETS)

LAtest: stackTOKEN.o stackINT.o mystring.o scanner.o LAtest.c

stackTOKEN.o: ../projekt/stackTOKEN.c
	$(CC) $(CFLAGS) -c $<

stackINT.o: ../projekt/stackINT.c
	$(CC) $(CFLAGS) -c $<

mystring.o: ../projekt/mystring.c
	$(CC) $(CFLAGS) -c $<

scanner.o: ../projekt/scanner.c
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) *.o $(TARGETS)
