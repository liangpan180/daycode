#include<stdlib.h>
#include<unistd.h>
#include<iostream>
#include<thread>
#include<queue>
#include<mutex>
using namespace std;

#define NUM	100000000

#define PRIORITY_DEFAULT	100
#define PRIORITY_LOW		0
#define PRIORITY_HIGH		200

/* item struct (priority and data) */
struct item {
	friend bool operator< (item a, item b)
	{
		return a.priority < b.priority;
	}

	int priority;
	int data;
};

struct cmp {
	bool operator() (struct item* a, struct item* b) {
		return *a < *b;
	}
};

/* global queue and lock */
priority_queue<struct item *, vector<struct item *>, cmp> q;
mutex g_lock;
int g_num = 0;

void create_priority_data(int priority, int count)
{
	int i = 0;
	struct item *tmp = NULL;

	for (i = 0; i < count; i++) {
		tmp = (struct item *)calloc(1, sizeof(struct item));
		tmp->priority = priority;
		//tmp->data = random() % count;
		tmp->data = i;
		g_lock.lock();
		q.push(tmp);
		g_lock.unlock();
	}
}

/* dequeue items thread entry */
void dq_entry(void) {
	struct item *tmp = NULL;

	while (g_num || q.size()) {
		if (q.size()) {
			g_lock.lock();
			tmp = q.top();
			cout << "Priority: " << tmp->priority << " Data: " << tmp->data << endl;
			free(tmp);
			q.pop();
			{
				priority_queue<struct item *, vector<struct item *>, cmp> t = q;
				q.swap(t);
			}
			g_lock.unlock();
		}
	}
}

/* enqueue high priority item entry */
void ph_entry(void) {
	create_priority_data(PRIORITY_HIGH, NUM);
	g_lock.lock();
	g_num--;
	g_lock.unlock();
}

/* enqueue low priority item entry */
void pl_entry(void) {
	create_priority_data(PRIORITY_LOW, NUM);
	g_lock.lock();
	g_num--;
	g_lock.unlock();
}

/* enqueue default priority item entry */
void pd_entry(void) {
	create_priority_data(PRIORITY_DEFAULT, NUM);
	g_lock.lock();
	g_num--;
	g_lock.unlock();
}

int main(int argc, char** argv)
{
	int i = 0;
	g_num = 3;

	cout << "Begin !" << endl;
	thread trd(dq_entry);
	thread t1(ph_entry);
	thread t2(pl_entry);
	thread t3(pd_entry);

	trd.join();
	t1.join();
	t2.join();
	t3.join();
	cout << "End !" << endl;

	return 0;
}
