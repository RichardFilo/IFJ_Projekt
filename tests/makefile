CC=gcc
CFLAGS = -g -Wall
TARGETS = LAtest SAtestExp SAtest

all: $(TARGETS)

LAtest: stackTOKEN.o stackINT.o mystring.o scanner.o LAtest.c

SAtestExp: stackTOKEN.o stackINT.o mystring.o scanner.o symtable.o parser.o SAtestExp.c

SAtest: stackTOKEN.o stackINT.o mystring.o scanner.o symtable.o parser.o SAtest.o

SAtest.o: SAtest.c
	$(CC) $(CFLAGS) -c $<

symtable.o: ../projekt/symtable.c
	$(CC) $(CFLAGS) -c $<

parser.o: ../projekt/parser.c
	$(CC) $(CFLAGS) -c $<

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
