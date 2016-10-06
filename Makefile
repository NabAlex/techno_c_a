PROGRAMS = main.o

MAIN = main

OUT = out
CC = gcc


# default: program

$@: program

program: $(PROGRAMS)
	$(CC) $(PROGRAMS) -lm -o $(OUT)

$(MAIN).o: $(MAIN).c
	$(CC) -Wall -pedantic -c $(MAIN).c

clean:
	rm -rf *.o $(OUT)
