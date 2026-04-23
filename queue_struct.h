#ifndef QUEUE_STRUCT_H
#define QUEUE_STRUCT_H

typedef struct
{
    int *data;
    int  front;
    int  rear;
    int  count;
    int  capacity;
} QUEUE_HEAD;

typedef QUEUE_HEAD *Queue;

#endif