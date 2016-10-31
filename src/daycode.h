#ifndef DAYCODE_H
#define DAYCODE_H

#include<stdio.h>
#include<stdlib.h>

struct dayfunc {
	const char *func_name;
	void (*func)(void);
};

/* global */
extern int silence;

/* functions */
void AlbToChinese(void);

void BucketWater(void);

void TryRegex(void);
#endif	/* DAYCODE_H */
