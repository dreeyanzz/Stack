#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ── Lifecycle ────────────────────────────────────────────────────────────────

Queue createQueue(int capacity)
{
    Queue queue    = (Queue)malloc(sizeof(QUEUE_HEAD));
    queue->data    = (int *)malloc(sizeof(int) * capacity);
    queue->front   = 0;
    queue->rear    = -1;
    queue->count   = 0;
    queue->capacity = capacity;
    return queue;
}

// ── Core operations ──────────────────────────────────────────────────────────

/*
 * Uses a circular buffer so rear wraps around after reaching the end.
 * This avoids false "overflow" after interleaved enqueue/dequeue operations.
 */
void enqueue(Queue queue, int item)
{
    if (queue == NULL) { printf("Queue not initialized.\n"); return; }
    if (isQueueFull(queue))
    {
        printf("Overflow: Queue is full. Cannot enqueue %d.\n", item);
        return;
    }

    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = item;
    queue->count++;
}

void dequeue(Queue queue)
{
    if (queue == NULL) { printf("Queue not initialized.\n"); return; }
    if (isQueueEmpty(queue))
    {
        printf("Underflow: Queue is empty. Nothing to dequeue.\n");
        return;
    }

    int removed = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->count--;

    printf("Dequeued: %d\n", removed);
}

void peekFront(Queue queue)
{
    if (queue == NULL) { printf("Queue not initialized.\n"); return; }
    if (isQueueEmpty(queue)) { printf("Queue is empty. Nothing at front.\n"); return; }

    printf("Front: %d\n", queue->data[queue->front]);
}

void peekRear(Queue queue)
{
    if (queue == NULL) { printf("Queue not initialized.\n"); return; }
    if (isQueueEmpty(queue)) { printf("Queue is empty. Nothing at rear.\n"); return; }

    printf("Rear: %d\n", queue->data[queue->rear]);
}

void displayQueue(Queue queue)
{
    if (queue == NULL) { printf("Queue not initialized.\n"); return; }
    if (isQueueEmpty(queue)) { printf("Queue is empty. Nothing to display.\n"); return; }

    printf("Queue: FRONT[ ");
    for (int i = 0; i < queue->count; i++)
    {
        int idx = (queue->front + i) % queue->capacity;
        printf("|%3d|", queue->data[idx]);
        if (i < queue->count - 1) printf(" -> ");
    }
    printf(" ]REAR\n");
    printf("       Count: %d / %d\n", queue->count, queue->capacity);
}

int isQueueEmpty(Queue queue)
{
    return queue->count <= 0;
}

int isQueueFull(Queue queue)
{
    return queue->count >= queue->capacity;
}

// ── Applications ─────────────────────────────────────────────────────────────

/*
 * Reverses the queue in-place by swapping mirrored positions
 * within the circular buffer — no auxiliary structure needed.
 */
void reverseQueue(Queue queue)
{
    if (isQueueEmpty(queue))  { printf("Queue is empty. Nothing to reverse.\n"); return; }
    if (queue->count == 1)    { printf("Only one element — already reversed.\n"); return; }

    int left  = 0;
    int right = queue->count - 1;

    while (left < right)
    {
        int li = (queue->front + left)  % queue->capacity;
        int ri = (queue->front + right) % queue->capacity;

        int tmp          = queue->data[li];
        queue->data[li]  = queue->data[ri];
        queue->data[ri]  = tmp;

        left++;
        right--;
    }

    printf("Queue reversed.\n");
    displayQueue(queue);
}

/*
 * Palindrome check using a queue AND a stack:
 *   - Characters are enqueued (FIFO) and pushed onto a stack (LIFO).
 *   - Comparing dequeued chars with popped chars detects a palindrome.
 */
void palindromeQueue()
{
    char str[100];
    printf("Enter a string: ");
    scanf(" %99[^\n]", str);

    int len = strlen(str);
    if (len == 0) { printf("Empty input.\n"); return; }

    // Local array-based queue
    char charQueue[100];
    int  qFront = 0, qRear = 0;

    // Local array-based stack
    char charStack[100];
    int  top = -1;

    for (int i = 0; i < len; i++)
    {
        charQueue[qRear++]  = str[i];   // enqueue
        charStack[++top]    = str[i];   // push
    }

    int isPalin = 1;
    while (qFront < qRear)
    {
        // dequeue from front, pop from top
        if (charQueue[qFront++] != charStack[top--])
        {
            isPalin = 0;
            break;
        }
    }

    printf("Result: %s\n", isPalin ? "Palindrome" : "Not Palindrome");
}

/*
 * Generates binary representations of 1 to N using a string queue.
 * Classic BFS approach: dequeue current, enqueue current+"0" and current+"1".
 */
void generateBinary()
{
    int n;
    printf("Enter N (generate binary for 1 to N): ");
    scanf(" %d", &n);

    if (n <= 0) { printf("N must be a positive integer.\n"); return; }

    // String queue — supports up to ~512 nodes, 32 chars each
    char strQueue[512][32];
    int  qFront = 0, qRear = 0;

    // Seed the queue with "1"
    strcpy(strQueue[qRear++], "1");

    printf("\n  Binary representations from 1 to %d:\n", n);
    printf("  %-6s  %s\n", "Decimal", "Binary");
    printf("  %-6s  %s\n", "-------", "------");

    for (int i = 1; i <= n; i++)
    {
        char *current = strQueue[qFront++];
        printf("  %-6d  %s\n", i, current);

        // Enqueue current + "0"
        snprintf(strQueue[qRear], sizeof(strQueue[qRear]), "%s0", current);
        qRear++;

        // Enqueue current + "1"
        snprintf(strQueue[qRear], sizeof(strQueue[qRear]), "%s1", current);
        qRear++;
    }
}