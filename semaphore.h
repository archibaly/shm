#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#define SEM_SEED	1000

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

int set_semvalue(int sem_id, int value);
void del_semvalue(int sem_id);
int semaphore_p(int sem_id);
int semaphore_v(int sem_id);

#endif /* _SEMAPHORE_H_ */
