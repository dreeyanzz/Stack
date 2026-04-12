#include "functions.h"
#include "stack.h"
#include "struct.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

void checkPalindrome()
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