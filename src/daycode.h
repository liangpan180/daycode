#include<stdio.h>
#include<stdlib.h>

struct dayfunc {
	const char *func_name;
	void (*func)(void);
};

/* functions */
void AlbToChinese(void);
