/*
 * AlbToChinese
 * des: Alabo number transport to Chinese
 * day:	2016-08-19
 */
#include "stdint.h"
#include "daycode.h"
#include "common/Vlist.h"

const char* ChiCall[] = {"零", "壹", "贰", "叁", "肆", "伍", "陆", "柒", "捌", "玖"};

const char* Section[] = {"", "万", "亿", "万亿"};

const char* Unit[] = {"", "拾", "百", "仟"};

uint32_t Alb_number = 390000033;

void TransSection(uint32_t section, int set_number, LIST_HEAD *head)
{
	uint32_t tmp;
	uint32_t i = 1000;
	int j = 3;
	int zero = 0;
	list_node_t *node = NULL;

	while (section) {
		tmp = section / i;

		if (!tmp) {
			zero = 1;
		} else {
			if (zero) {
				node = (list_node_t *)calloc(1, sizeof(list_node_t));
				node->data = (node_t)ChiCall[0];
				list_insert_tail(head, node);
				zero = 0;
			}

			node = (list_node_t *)calloc(1, sizeof(list_node_t));
			node->data = (node_t)ChiCall[tmp];
			list_insert_tail(head, node);

			if (node->data != Unit[0]) {
				node = (list_node_t *)calloc(1, sizeof(list_node_t));
				node->data = (node_t)Unit[j];
				list_insert_tail(head, node);
			}
		}
		section = section % i;
		i = i / 10;
		j--;
	}

	if (j != 3) {
		node = (list_node_t *)calloc(1, sizeof(list_node_t));
		node->data = (node_t)Section[set_number];
		list_insert_tail(head, node);
	}
}

void AlbToChinese(void)
{
	int sec_number = 0;
	uint32_t tmp = 0;
	uint32_t section = 0;
	LIST_HEAD result = NULL;
	list_node_t *ndata = NULL;
	list_node_t *p = NULL;
	int first = 1;

	tmp = Alb_number;
	while (tmp) {
		LIST_HEAD Chinese = NULL;
		section = tmp % 10000;
		TransSection(section, sec_number, &Chinese);
		list_append_head(&result, Chinese);
		Chinese = NULL;
		sec_number++;
		tmp /= 10000;
	}

	ndata = result;
	printf("[%d] --- ", Alb_number);
	while (ndata) {
		if (first && ndata->data == ChiCall[0])
			first = 0;
		else
			printf("%s", (char*)ndata->data);
		p = ndata;
		ndata = ndata->next;
		free(p);
		p = NULL;
	}
	printf("\n"); }
