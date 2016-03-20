#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/sem.h>
#include <signal.h>

#include "shm.h"
#include "semaphore.h"

people *p_map;
int sem_id;

void sig_usr1(int num)
{
	if (num == SIGUSR1) {
		semaphore_p(sem_id);
		printf("name = %s\n", p_map->name);
		printf("age = %d\n", p_map->age);
		p_map->age = -1;
		semaphore_v(sem_id);
	}
}

int main(int argc, char** argv)
{
	int shm_id;
	sem_id = semget((key_t)SEM_SEED, 1, IPC_CREAT | 0600);
	if (sem_id < 0) {
		perror("semget()");
		return -1;
	}
#if DEBUG
	printf("sem_id = %d\n", sem_id);
#endif

	shm_id = shmget(SHM_SEED, 4096, IPC_CREAT | 0600);
	if (shm_id == -1) {
		perror("shmget()");
		return -1;
	}
	printf("shm_id = %d\n", shm_id);
	p_map = (people *)shmat(shm_id, NULL, 0);

	signal(SIGUSR1, sig_usr1);
	// set_semvalue(sem_id, 0);
	for(;;) {
		sleep(1);
	}
	shmdt(p_map);

	return 0 ;
}
