/*
 * TryRegex
 * des: Try to use regex library
 * day: 2016-9-27
 */
#include <regex.h>
#include "daycode.h"

#define MAX_LEN		512

const char* def_pattern = "^(tcp|rdma)://([^:]*):([1-9][0-9]*)$";

const char* match_str = "tcp://192.168.1.2:9897";

void put_user_str(char *user_str)
{
	free(user_str);
	user_str = NULL;
} 

char* get_user_str(int size, char* info)
{
	char *user_str = (char *)calloc(size, sizeof(char));

	for (; ;) {
		char ch;
		int flag = 0;
		printf("%s\n", info);

		scanf("%s", user_str);
		printf("Commit: %s\n", user_str);
		printf("[Y/y/N/n]:");
		scanf(" %c", &ch);
		switch (ch) {
			case 'Y':
			case 'y':
				flag = 1;
				break;
			case 'N':
			case 'n':
			default :
				break;
		}
		if (flag)
			break;	
	} /* end for */

	return user_str;
}

void TryRegex(void)
{
	int status = -1;
	int i, j = 0;
	regmatch_t pmatch[4];
	const size_t nmatch = 4;
	regex_t reg;
	char *pattern = NULL;
	char *mt = NULL;

	if (!silence) {	
		pattern = get_user_str(MAX_LEN, "Input your pattern:");
		mt = get_user_str(MAX_LEN, "Input your match:");
	} else {
		pattern = def_pattern;
		mt = match_str;
	}

	printf("Pattern: %s\n", pattern);
	printf("Match: %s\n", mt);

	/* try regex */
	regcomp(&reg, pattern, REG_EXTENDED);
	status = regexec(&reg, mt, nmatch, pmatch, 0);
	if (status == REG_NOMATCH) {
		printf("No Match !\n");
	} else if (status == 0) {
		printf("Match !\n");
		for (j = 0; j < 4; j++) {
			for (i = pmatch[j].rm_so; i < pmatch[j].rm_eo; i++) {
				putchar(mt[i]);
			}
			printf("\n");
		}
	}
	regfree(&reg);

	if (!silence) {
		put_user_str(pattern);
		put_user_str(mt);
	}

	return;
}
