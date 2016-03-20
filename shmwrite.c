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

int main(int argc, char** argv)
{
	int shm_id, i;
	char temp[8];
	people *p_map;
	int sem_id;

	sem_id = semget((key_t)SEM_SEED, 1, IPC_CREAT | 0600);
	if (sem_id < 0) {
		perror("semget()");
		return -1;
	}
	printf("sem_id = %d\n", sem_id);

	shm_id = shmget(SHM_SEED, 4096, IPC_CREAT | 0600);
#if 0
	if (shm_id != -1) {	/* already be created */
		if (shmctl(shm_id, IPC_RMID, NULL) < 0) {	/* delete it first */
			perror("shmctl()");
			return -1;
		}
	}

	shm_id = shmget(SHM_SEED, 4096, IPC_CREAT | IPC_EXCL | 0600);
#endif
	if (shm_id < 0) {
		perror("shmget");
		return -1;
	}
	printf("shm_id = %d\n", shm_id);

	p_map = (people *)shmat(shm_id, NULL, 0);
	memset(temp, 0, sizeof(temp));
	strcpy(temp, "test");

	set_semvalue(sem_id, 1);
	for(i = 0; ; i++) {
		semaphore_p(sem_id);
		sprintf(p_map->name, temp);
		p_map->age = i + 20;
		semaphore_v(sem_id);
		pid_t read_pid;
		if (find_pid_by_name("shmread", &read_pid, 1) > 0) {
			printf("shmread = %d\n", read_pid);
			kill(read_pid, SIGUSR1);
		}
		sleep(3);
	}
	shmdt(p_map);

	return 0 ;
}
