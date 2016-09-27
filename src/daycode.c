/*
 * daycode: learn everyday
 *
 */
#include <getopt.h>
#include "daycode.h"

#define NOREQ_PARAM	0
#define REQUIRE_PARAM	1

/* global */
int silence = 1;

struct dayfunc funcmap[] = {
	{"AlbToChinese", AlbToChinese},
	{"BucketWater", BucketWater},
	{"TryRegex", TryRegex},
	{NULL, NULL},
};

void usage()
{
	printf("[Usage]: daycode [options]\n");
	printf("[Options]:\n"
		"\t[-n|--number]	number\n"
		"\t[-l|--list]	list\n"
		"\t[-h|-help]	help\n");
	exit(1);
}

void funcmap_dump()
{
	int count = 0;
	int i = 0;

	count = sizeof(funcmap)/sizeof(funcmap[0]) - 1;
	printf("Func Map: ----------------------\n");
	for (i = 0; i < count; i++) {
		printf("[%d]\t%s\n", i, funcmap[i].func_name);
	}
	printf("--------------------------------\n");
}

int main(int argc, char** argv)
{
	int retval = 0;
	int opt = 0;
	int i = 0;
	int count = 0;
	int number = -1;
	char* const optstring = "n:lh";

	static struct option long_options[] = {
		{"number", REQUIRE_PARAM, NULL, 'n'},
		{"list", NOREQ_PARAM, NULL, 'l'},
		{"help", NOREQ_PARAM, NULL, 'h'},
		{0, 0, 0, 0},
	};

	printf("Welcome daycode programe !\n\n");
	while((opt = getopt_long(argc, argv, optstring, long_options, NULL)) != -1) {
		switch (opt) {
			case 'n':
				number = atoi(optarg);
				silence = 0;
				break;
			case 'l':
				funcmap_dump();
				goto out;
			case 'h':
			default:
				usage();
		}
	}

	count = sizeof(funcmap)/sizeof(funcmap[0]) - 1;
	if (number >= 0 && number < count) {
		printf("[%s]\n", funcmap[number].func_name);
		funcmap[number].func();
	} else {
		for (i = 0; i < count; i++) {
			printf("[%s]\n", funcmap[i].func_name);
			funcmap[i].func();
		}
	}

out:
	printf("\nBye-bye !\n");
	return retval;
}

