#ifndef QUEUE_H
#define QUEUE_H

#include "queue_struct.h"
#include <stdlib.h>

Queue createQueue(int capacity);
void  enqueue(Queue queue, int item);
void  dequeue(Queue queue);
void  peekFront(Queue queue);
void  peekRear(Queue queue);
void  displayQueue(Queue queue);
int   isQueueEmpty(Queue queue);
int   isQueueFull(Queue queue);
void  reverseQueue(Queue queue);
void  palindromeQueue();
void  generateBinary();

#endif