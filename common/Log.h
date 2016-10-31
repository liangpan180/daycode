/*
 * Used for log info
 */

#include <stdio.h>

#define MAX_PATH_LEN		1024
#define LOG_ROOT		/tmp

FILE* global_fp = NULL;

FILE* log_open(char *name)
{
	char path[MAX_PATH_LEN] = {0};

	sprintf(path, "/tmp/%s", name);
	global_fp = fopen(path, "w");
	if (global_fp < 0)
		return NULL;

	fseek(global_fp, 0, SEEK_END);

	return global_fp;
}

#define log_close()	fclose(global_fp)

#define DLOG(fmt, args...) \
	{	\
		fprintf(global_fp, "%s:%d " fmt "\n", __FILE__, __LINE__, ##args);	\
		fflush(global_fp);	\
	}
