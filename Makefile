CC = gcc
CFLAGS = -Wall

all: shmwrite shmread

shmwrite: shmwrite.o semaphore.o
	$(CC) -o $@ $^

semaphore.o: semaphore.c

shmwrite.o: shmwrite.c

shmread: shmread.o semaphore.o
	$(CC) -o $@ $^

shmread.o: shmread.c semaphore.o

clean:
	-rm -f *.o shmwrite shmread
