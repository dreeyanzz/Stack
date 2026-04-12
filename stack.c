#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

Stack createStack()
{
    Stack stack = (Stack)malloc(sizeof(STACK_HEAD));

    stack->count = 0;
    stack->top = NULL;

    return stack;
}

NodePtr createNode(int item)
{
    NodePtr node = (NodePtr)malloc(sizeof(STACK_NODE));

    node->data = item;
    node->next = NULL;

    return node;
}

void push(Stack stack, int item)
{
    NodePtr newNode = createNode(item);

    newNode->next = stack->top;
    stack->top = newNode;
    stack->count++;
}

void pop(Stack stack)
{
    if (stack->top == NULL || isEmpty(stack))
        printf("Nothing to pop.");

    NodePtr top = stack->top;
    NodePtr newTop = stack->top->next;

    stack->top = newTop;
    printf("Popped %d from the stack.\n", top->data);
    free(top);
    (stack->count)--;
}

void peek(Stack stack)
{
    if (isEmpty(stack) || stack->top == NULL)
    {
        printf("Nothing to peek.");
        return;
    }

    printf("Top: %d", stack->top->data);
}

void display(Stack stack)
{
    if (isEmpty(stack) || stack->top == NULL)
    {
        printf("Nothing to display.");
        return;
    }

    NodePtr walker = stack->top;

    printf("Current Stack: [ ");
    printf("%d", walker->data);

    walker = walker->next;
    while (walker != NULL)
    {
        printf(" -> %d", walker->data);
        walker = walker->next;
    }

    printf(" ]");
}

bool isEmpty(Stack stack)
{
    return stack->count <= 0;
}