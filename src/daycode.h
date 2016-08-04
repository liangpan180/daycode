#include<stdio.h>
#include<stdlib.h>

void AlbToChinese(void) { printf("Abs\n"); };

struct dayfunc {
	const char *func_name;
	void (*func)(void);
};
