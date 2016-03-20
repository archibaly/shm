#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#include "shm.h"
#include "semaphore.h"
#include "find_pid_by_name.h"

int people_set(const people *data, int sem_id)
{
	int shm_id;
	people *p_map;

	shm_id = shmget(SHM_SEED, 4096, IPC_CREAT | 0600);
	if (shm_id < 0) {
		perror("shmget");
		return -1;
	}

	p_map = (people *)shmat(shm_id, NULL, 0);

	semaphore_p(sem_id);
	strcpy(p_map->name, data->name);
	p_map->age = data->age;
	semaphore_v(sem_id);
	shmdt(p_map);

	return 0;
}

int main(int argc, char** argv)
{
	int sem_id = semget((key_t)SEM_SEED, 1, IPC_CREAT | 0600);
	if (sem_id < 0) {
		perror("semget()");
		return -1;
	}
	printf("sem_id = %d\n", sem_id);

	set_semvalue(sem_id, 1);

	people p;
	sprintf(p.name, "%s", "jackyliu");
	p.age = 25;

	int i;
	for(i = 0; ; i++) {
		people_set(&p, sem_id);
		pid_t read_pid;
		if (find_pid_by_name("shmread", &read_pid, 1) > 0) {
			kill(read_pid, SIGUSR1);
		}
		sleep(3);
	}

	return 0 ;
}
