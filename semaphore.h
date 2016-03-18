#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#define SEM_SEED	1000

int set_semvalue(int sem_id, int value);
int del_semvalue(int sem_id);
int semaphore_p(int sem_id);
int semaphore_v(int sem_id);

#endif /* _SEMAPHORE_H_ */
