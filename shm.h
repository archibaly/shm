#ifndef _SHM_H_
#define _SHM_H_

#define IPCKEY 123

typedef struct {
	char name[8];
	int age;
} people;

#endif /* _SHM_H_ */
