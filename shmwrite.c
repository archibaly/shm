#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#include "shm.h"

int main(int argc, char** argv)
{
	int shm_id, i;
	char temp[8];
	people *p_map;
	char pathname[30] ;
/*
	key_t key;
	strcpy(pathname,"/tmp") ;
	key = ftok(pathname, 0x03);
	if (key == -1) {
		perror("ftok");
		return -1;
	}
	printf("key = %d\n", key);
*/

	shm_id = shmget(IPCKEY, 4096, 0600);
	if (shm_id != -1) {	/* already be created */
		if (shmctl(shm_id, IPC_RMID, NULL) < 0) {	/* delete it first */
			perror("shmctl()");
			return -1;
		}
	}

	shm_id = shmget(IPCKEY, 4096, IPC_CREAT | IPC_EXCL | 0600);
	if (shm_id < 0) {
		perror("shmget");
		return -1;
	}
	printf("shm_id = %d\n", shm_id);

	p_map = (people *)shmat(shm_id, NULL, 0);
	memset(temp, 0x00, sizeof(temp));
	strcpy(temp, "test");

	temp[4] = '0';
	for(i = 0; i < 3; i++) {
		temp[4] += 1;
		strncpy((p_map+i)->name, temp, 5);
		(p_map+i)->age = i + 20;
	}
	shmdt(p_map);

	return 0 ;
}
