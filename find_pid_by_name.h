#ifndef __FIND_PID_BY_NAME__
#define __FIND_PID_BY_NAME__

#include <sys/types.h>

int find_pid_by_name(const char* pidName, pid_t *pid, int size);

#endif /* __FIND_PID_BY_NAME__ */
