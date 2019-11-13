typedef struct queue *Queue;

Queue newQueue();
int isEmptyQueue(Queue q);
int enqueue(Queue q, int *posizione);
int *dequeue(Queue q);
