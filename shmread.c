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

void sig_usr1(int num)
{
	if (num == SIGUSR1) {
		int sem_id;
		int shm_id;
		people *p_map;

		sem_id = semget((key_t)SEM_SEED, 1, IPC_CREAT | 0600);
		if (sem_id < 0) {
			return;
		}

		shm_id = shmget(SHM_SEED, 4096, IPC_CREAT | 0600);
		if (shm_id == -1) {
			return;
		}

		p_map = (people *)shmat(shm_id, NULL, 0);
		semaphore_p(sem_id);
		printf("name = %s\n", p_map->name);
		printf("age = %d\n", p_map->age);
		semaphore_v(sem_id);
		shmdt(p_map);
	}
}

int main(int argc, char** argv)
{
	signal(SIGUSR1, sig_usr1);
	for(;;) {
		pause();
	}

	return 0 ;
}
