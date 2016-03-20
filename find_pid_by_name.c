#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <dirent.h>

#define READ_BUF_SIZE	512

/*
 * @name: 进程名
 * @pid : 存放获得的pid的数组
 * @size: 数组的大小
 */
int find_pid_by_name(const char *pid_name, pid_t *pid, int size)
{
	DIR *dir;
	struct dirent *next;
	int i = 0;

	// /proc中包括当前的进程信息，读取该目录
	dir = opendir("/proc");
	if (!dir) {
		printf("Cannot open /proc");
		return -1;
	}

	while ((next = readdir(dir)) != NULL) {
		FILE *status;
		char filename[READ_BUF_SIZE];
		char buffer[READ_BUF_SIZE];
		char name[READ_BUF_SIZE];

		/* Must skip ".." since that is outside /proc */
		if (strcmp(next->d_name, "..") == 0)
			continue;

		/* If it isn't a number, we don't want it */
		if (!isdigit(*next->d_name))
			continue;

		sprintf(filename, "/proc/%s/status", next->d_name);
		if (!(status = fopen(filename, "r"))) {
			continue;
		}
		if (fgets(buffer, READ_BUF_SIZE - 1, status) == NULL) {
			fclose(status);
			continue;
		}
		fclose(status);

		/* Buffer should contain a string like "Name:   binary_name" */
		sscanf(buffer, "%*s %s", name);
		if (strcmp(pid_name, name) == 0) {
			if (i <= size - 1)
				pid[i++] = strtol(next->d_name, NULL, 0);
			else
				return size;
		}
	}

	return i;
}
