/*
 * test for create new thread
 */

#include <pthread.h>
#include "common/Log.h"

#define ITER_COUNT	100

/* thread entry function */
void entry(void)
{
	int flag = 0;

	log_open("create_thread");

	while (1) {
		flag++;
		if ((flag % 1000) == 0)
			DLOG("Thread %lx running(%d)...\n", pthread_self(), flag);
		//if (flag >= ITER_COUNT)
		//	break;
		//usleep(100);
	}

	log_close();
}

int main(int argc, char **argv)
{
	int ret = 0;
	pthread_t thread_id;

	ret = pthread_create(&thread_id, NULL, (void *)entry, NULL);
	if (ret) {
		printf("Create thread failed !\n");
		ret = -1;
		goto out;
	}

	printf("Main thread %lx success create new thread %lx !\n", pthread_self(), thread_id);

	printf("Wait for thread %lx exit...\n", thread_id);
	pthread_join(thread_id, NULL);
out:
	return ret;
}
