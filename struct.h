#ifndef STRUCT_H

#define STRUCT_H

typedef struct node *NodePtr;
typedef struct node
{
    int data;
    NodePtr next;
} STACK_NODE;

typedef struct
{
    int count;
    NodePtr top;
} STACK_HEAD;

typedef STACK_HEAD *Stack;

#endif