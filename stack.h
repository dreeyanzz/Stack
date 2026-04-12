#ifndef STACK_H

#define STACK_H
#include "struct.h"
#include <stdbool.h>

NodePtr createNode(int item);
Stack createStack();
void push(Stack stack, int data);
void pop(Stack stack);
void peek(Stack stack);
void display(Stack stack);
bool isEmpty(Stack stack);

#endif