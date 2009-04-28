#makefile

all : othello.o main.o computer.o
	$(CC) -o othello othello.o main.o computer.o

othello.o : othello.c othello.h
	$(CC) -c othello.c -o othello.o

main.o : main.c othello.h
	$(CC) -c main.c -o main.o

computer.o : computer.c othello.h
	$(CC) -c computer.c -o computer.o

clean :
	$(RM) -rf *.o

