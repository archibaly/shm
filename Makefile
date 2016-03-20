CC = gcc
CFLAGS = -Wall -DDEBUG=1

all: shmwrite shmread

shmwrite: shmwrite.o semaphore.o find_pid_by_name.o
	$(CC) -o $@ $^

semaphore.o: semaphore.c

shmwrite.o: shmwrite.c

find_pid_by_name.o: find_pid_by_name.c

shmread: shmread.o semaphore.o
	$(CC) -o $@ $^

shmread.o: shmread.c semaphore.o

clean:
	-rm -f *.o shmwrite shmread
