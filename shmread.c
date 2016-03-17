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
	key_t key;
	char temp[8];
	people *p_map;
	char pathname[30] ;

	shm_id = shmget(IPCKEY, 4096, 0600);
	if (shm_id == -1) {
		perror("shmget()");
		return -1;
	}
	printf("shm_id = %d\n", shm_id);
	p_map = (people *)shmat(shm_id, NULL, 0);

	for(i = 0; i < 3; i++) {
		printf("name = %s\n", p_map[i].name);
		printf("age = %d\n", p_map[i].age);
	}
	shmdt(p_map);

	return 0 ;
}
