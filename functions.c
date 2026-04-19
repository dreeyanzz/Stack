#include "functions.h"
#include "stack.h"
#include "struct.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// ---------------------- Helpers
static void silentPop(Stack stack)
{

    // Only pop if there is at least 1 node
    if (stack->top == NULL || isEmpty(stack))
    {
        printf("Nothing to pop.");
        return;
    }

    // Guaranteed to only pop if there is 1 or more node in the stack

    NodePtr top = stack->top;
    NodePtr newTop = stack->top->next;

    stack->top = newTop;
    free(top);
    (stack->count)--;
}

// Returns the top node of the stack
static NodePtr silentPeek(Stack stack)
{
    // Peek only if there is at least 1 node
    if (stack->top == NULL || isEmpty(stack))
    {
        printf("Nothing to peek.");
        return NULL;
    }

    return stack->top;
}

// ---------------------- Main methods

void reverseString()
{
    char str[100];

    printf("Enter string: ");
    scanf(" %99[^\n]", str);

    Stack stack = createStack();
    int stringLength = strlen(str);

    int charIndex;
    for (charIndex = 0; charIndex < stringLength; charIndex++)
        push(stack, str[charIndex]);

    NodePtr walker = stack->top;
    while (walker != NULL)
    {
        printf("%c", walker->data);

        NodePtr temp = walker;
        walker = walker->next;
        free(temp);
    }
}

void checkBalanced()
{
    char inputBrackets[100];

    printf("Enter the brackets: ");
    scanf(" %99[^\n]", inputBrackets);

    int inputLen = strlen(inputBrackets);
    if (inputLen % 2 != 0)
    {
        printf("Brackets are not balanced.");
        return;
    }

    Stack stack = createStack();

    int index;
    for (index = 0; index < inputLen; index++)
    {
        char currentChar = inputBrackets[index];

        if (currentChar == '(' || currentChar == '[' || currentChar == '{')
        {
            push(stack, currentChar);
            continue;
        }

        if (stack->top == NULL)
            break;

        char lastChar = stack->top->data;

        if ((lastChar == '(' && currentChar == ')') || (lastChar == '[' && currentChar == ']') || (lastChar == '{' && currentChar == '}'))
            pop(stack);
        else
            break;
    }

    printf("Brackets are %s.", stack->top == NULL ? "balanced" : "not balanced");
}

void decimalToBinary()
{

    int decimal;

    printf("Enter a number: ");
    scanf(" %d", &decimal);

    Stack binaryStack = createStack();

    do
    {
        push(binaryStack, decimal % 2);
        decimal /= 2;
    } while (decimal != 0);

    int numPadding = 8 - binaryStack->count;
    while (numPadding-- > 0)
        printf("0");

    NodePtr walker = binaryStack->top;
    while (walker != NULL)
    {
        printf("%d", walker->data);

        NodePtr temp = walker;
        walker = walker->next;
        free(temp);
    }
}

void palindromeCheck()
{
    char str[100];
    char reversedStr[100] = "";

    printf("Enter string: ");
    scanf(" %99[^\n]", str);

    Stack stack = createStack();
    int stringLength = strlen(str);

    int charIndex;
    for (charIndex = 0; charIndex < stringLength; charIndex++)
        push(stack, str[charIndex]);

    NodePtr walker = stack->top;
    while (walker != NULL)
    {
        int currentRevLen = strlen(reversedStr);
        char currentChar = walker->data;

        reversedStr[currentRevLen] = currentChar;
        reversedStr[currentRevLen + 1] = '\0';

        NodePtr temp = walker;
        walker = walker->next;

        free(temp);
    }

    printf("Is palindrome: %s", strcmp(str, reversedStr) == 0 ? "True" : "False");
}

// Sorts stack from least to greatest
void sortStack(Stack stack)
{
    // Only sort if there is two or more nodes in the stack
    if (stack->count < 2)
    {
        printf("There is nothing to sort...");
        return;
    }

    // Guaranteed to start only if stack has two or more nodes
    Stack auxStack = createStack();

    while (stack->count > 0)
    {
        NodePtr origTop = silentPeek(stack);
        int topData = origTop->data;
        silentPop(stack);

        while (auxStack->count > 0 && auxStack->top->data < topData)
        {
            NodePtr auxTop = silentPeek(auxStack);
            push(stack, auxTop->data);
            silentPop(auxStack);
        }

        push(auxStack, topData);
    }

    stack->top = auxStack->top;
    stack->count = auxStack->count;

    free(auxStack);
}
