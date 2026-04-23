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
    {
        printf("Underflow: Nothing to pop.\n");
        return;
    }

    NodePtr top = stack->top;
    NodePtr newTop = stack->top->next;

    stack->top = newTop;
    printf("Popped %d from the stack.\n", top->data);

    (stack->count)--;
    top->next = NULL;
    free(top);
}

void peek(Stack stack)
{
    if (isEmpty(stack) || stack->top == NULL)
    {
        printf("Stack is empty. Nothing to peek.\n");
        return;
    }

    printf("Top of stack: %d\n", stack->top->data);
}

void display(Stack stack)
{
    if (isEmpty(stack) || stack->top == NULL)
    {
        printf("Stack is empty. Nothing to display.\n");
        return;
    }

    NodePtr walker = stack->top;

    printf("Stack (top -> bottom): [ ");
    printf("|%3d|", walker->data);
    walker = walker->next;

    while (walker != NULL)
    {
        printf(" -> |%3d|", walker->data);
        walker = walker->next;
    }

    printf(" ]\n");
}

bool isEmpty(Stack stack)
{
    return stack->count <= 0;
}

// A linked-list stack has no fixed capacity, so it never overflows
bool isFull(Stack stack)
{
    return false;
}