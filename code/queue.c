#include<stdio.h>
#include<stdlib.h>
#include"../headers/queue.h"

#define MAX_QUEUE 100

struct queue {
	int head;
	int tail;
	int elements[MAX_QUEUE][2];
};

Queue newQueue()
{
	Queue newQueue;
	newQueue = malloc(sizeof(struct queue));
	newQueue->head = 0;
	newQueue->tail = 0;

	return newQueue;
}

int isEmptyQueue(Queue q) {
	return q->tail == q->head;
}

int enqueue(Queue q, int *posizione) {
	if(q->tail+1 % MAX_QUEUE == q->head) return 0;
	q->elements[q->tail][0] = *(posizione);
	q->elements[q->tail][1] = *(posizione+1);

	q->tail = (q->tail+1) % MAX_QUEUE;
}

int *dequeue(Queue q) {
	int temp[2] = {0, 0};
	if(isEmptyQueue(q)) return 0;

	int pos = q->head;
	q->head = (q->head+1) % MAX_QUEUE;
	return q->elements[pos];
}
