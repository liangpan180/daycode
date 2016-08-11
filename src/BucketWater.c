/*
 * BucketWater
 * des: Bucket and water question
 * day:	2016-08-23
 */
#include "stdint.h"
#include "daycode.h"

#define BUCKET_COUNTS	3
uint32_t buckets[BUCKET_COUNTS] = {8, 5, 3};

int find = 0;

typedef uint32_t bkt_stat[BUCKET_COUNTS];

typedef struct state {
	bkt_stat start;
	bkt_stat end;
	bkt_stat cur;
	struct state* next;
} mystat_t;

typedef struct action {
	int from;
	int to;
	int water;
	bkt_stat cur;
	struct action* next;
} do_action_t;

void SearchAction(mystat_t *st, do_action_t** act_list, mystat_t **st_list);

void show_action(do_action_t act)
{
	printf("Move %d(L) water, from %d to %d; Cur [%d, %d, %d]\n",
					act.water, act.from, act.to,
					act.cur[0], act.cur[1], act.cur[2]);
}

void dump_action(do_action_t* act_list)
{
	do_action_t* tmp = act_list;

	if (!act_list)
		printf("Is really to the end now!\n");
	else {
		while (tmp) {
			show_action(*tmp);
			tmp = tmp->next;
		}
	}
}

/* Get the result */
int IsEnd(mystat_t *st)
{
	int i = 0;

	for (i = 0; i < BUCKET_COUNTS; i++) {
		if (st->cur[i] != st->end[i])
			return 0;
	}

	find = 1;

	return 1;
}

int IsEmpty(mystat_t *st, int pos)
{
	if (st->cur[pos] <= 0)
		return 1;
	else
		return 0;
}

int IsFull(mystat_t *st, int pos)
{
	if (st->cur[pos] >= buckets[pos])
		return 1;
	else
		return 0;
}

void insert_stat(mystat_t** st_list, mystat_t* stat)
{
	mystat_t* tmp = NULL;

	if (!*st_list) {
		*st_list = stat;
		return;
	}

	tmp = *st_list;
	while(tmp) {
		if (!tmp->next) {
			tmp->next = stat;
			return;
		}
		tmp = tmp->next;
	}
}

void insert_list(do_action_t** act_list, do_action_t* node)
{
	do_action_t* tmp = NULL;

	if (!*act_list) {
		*act_list = node;
		return;
	}

	tmp = *act_list;
	while (tmp) {
		if (!tmp->next) {
			tmp->next = node;
			return;
		}
		tmp = tmp->next;
	}
}

void del_list(do_action_t** act_list, do_action_t* node)
{
	int first = 1;
	do_action_t* tmp = NULL;
	do_action_t* tmp1 = NULL;

	if (!*act_list)
		return;

	tmp = *act_list;
	while (tmp) {
		if (tmp == node) {
			if (first) {
				*act_list = tmp->next;
				first = 0;
				return;
			} else {
				tmp1->next = tmp;
				return;
			}
		}

		tmp1 = tmp;
		tmp = tmp->next;
	}
}

int IsReGet(mystat_t* st_list, do_action_t* action)
{
	int i = 0;
	mystat_t* tmp = NULL;
	int same = 0;

	if (!st_list) {
		return 0;
	}

	tmp = st_list;
	while (tmp) {
		same = 0;
		for (i = 0; i < BUCKET_COUNTS; i++) {
			if (tmp->cur[i] == action->cur[i]) {
				same++;
			}
		}

		if (same == BUCKET_COUNTS)
			return 1;

		tmp = tmp->next;
	}

	return 0;
}

void UndoAction(mystat_t *st, do_action_t *action)
{
	st->cur[action->to] -= action->water;
	st->cur[action->from] += action->water;
}

void TryAction(mystat_t *st, do_action_t** act_list, mystat_t** st_list, int from, int to)
{
	int from_w = st->cur[from];	/* now from water */
	int to_w = st->cur[to];		/* now to water */
	int water = 0;
	int i = 0;
	do_action_t* action = NULL;
	mystat_t *st1 = NULL;

	if (from == to || IsFull(st, to) || IsEmpty(st, from))
		return;

	/* checked before IsFull & IsEmpty */
	water = (buckets[to] - to_w) > from_w ? from_w : buckets[to] - to_w;
	
	action = (do_action_t *)calloc(1, sizeof(do_action_t));
	action->from = from;
	action->to = to;
	action->water = water;

	/* do action */
	st->cur[from] -= water;
	st->cur[to] += water;

	action->cur[0] = st->cur[0];
	action->cur[1] = st->cur[1];
	action->cur[2] = st->cur[2];

	if (IsReGet(*st_list, action) && !IsEnd(st)) {
		UndoAction(st, action);
		free(action);
		action = NULL;
		return;
	}

	st1 = (mystat_t *)calloc(1, sizeof(mystat_t));
	for (i = 0; i < BUCKET_COUNTS; i++)
		st1->cur[i] = action->cur[i];

	insert_stat(st_list, st1);

	/* push list */
	insert_list(act_list, action);

	SearchAction(st, act_list, st_list);

	/* pop list */
	del_list(act_list, action);

	UndoAction(st, action);

	free(action);
}

void SearchAction(mystat_t *st, do_action_t** act_list, mystat_t **st_list)
{
	int from, to = 0;

	if (IsEnd(st)) {
		printf("\n--------METHOD--------\n");
		dump_action(*act_list);
		return;
	}

	for (from = 0; from < BUCKET_COUNTS; from++) {
		for (to = 0; to < BUCKET_COUNTS; to++) {
			TryAction(st, act_list, st_list, from, to);
		}
	}

}

void BucketWater(void)
{
	do_action_t* act_list = NULL;
	int i = 0;
	mystat_t st = {
		.start = {8, 0, 0},
		.end = {4, 4, 0},
		.cur = {8, 0, 0},
		.next = NULL,
	};

	mystat_t* head = (mystat_t *)calloc(1, sizeof(mystat_t));
	for (i = 0; i < BUCKET_COUNTS; i++)
		head->cur[i] = st.cur[i];
	mystat_t *stat_list = NULL;
	insert_stat(&stat_list, head);

	SearchAction(&st, &act_list, &stat_list);
	if (!find)
		printf("No result find.\n");
}
