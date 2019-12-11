CC=gcc
CFLAGS = -g -Wall
TARGETS = IFJ19 

all: $(TARGETS)

IFJ19: stackTOKEN.o stackINT.o mystring.o scanner.o symtable.o parser.o IFJ19.o

IFJ19.o: IFJ19.c
	$(CC) $(CFLAGS) -c $<

symtable.o: symtable.c
	$(CC) $(CFLAGS) -c $<

parser.o: parser.c
	$(CC) $(CFLAGS) -c $<

stackTOKEN.o: stackTOKEN.c
	$(CC) $(CFLAGS) -c $<

stackINT.o: stackINT.c
	$(CC) $(CFLAGS) -c $<

mystring.o: mystring.c
	$(CC) $(CFLAGS) -c $<

scanner.o: scanner.c
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) *.o $(TARGETS)
