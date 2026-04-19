#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"
#include "functions.h"
#include "stack.h"

#include <stdlib.h> // Required for rand() and srand()
#include <time.h>   // Required for time()
void populateWithRandomData(Stack stack, int numberOfItems)
{
    // 1. Safety check
    if (stack == NULL)
    {
        printf("Error: Stack is uninitialized.\n");
        return;
    }

    if (numberOfItems <= 0)
    {
        printf("Number of items must be greater than zero.\n");
        return;
    }

    // 2. Loop and push random data
    for (int i = 0; i < numberOfItems; i++)
    {
        // Generate a random number between 0 and 99
        // You can change the 100 to whatever maximum limit you want
        int randomValue = rand() % 100;

        push(stack, randomValue);
    }
}

int main(void)
{
    srand(time(NULL));

    Stack stack = createStack();
    populateWithRandomData(stack, 10);

    display(stack);
    printf("\n");

    sortStack(stack);
    display(stack);

    return 0;
}
