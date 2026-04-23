#include "functions.h"
#include "stack.h"
#include "struct.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// ---------------------- Helpers

static void silentPop(Stack stack)
{
    if (stack->top == NULL || isEmpty(stack))
        return;

    NodePtr top = stack->top;
    stack->top = stack->top->next;
    free(top);
    (stack->count)--;
}

static NodePtr silentPeek(Stack stack)
{
    if (stack->top == NULL || isEmpty(stack))
        return NULL;

    return stack->top;
}

// Returns operator precedence level
static int precedence(char op)
{
    if (op == '^')             return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

static int isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
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

    printf("Reversed: ");
    NodePtr walker = stack->top;
    while (walker != NULL)
    {
        printf("%c", walker->data);
        NodePtr temp = walker;
        walker = walker->next;
        free(temp);
    }
    printf("\n");

    free(stack);
}

void checkBalanced()
{
    char inputBrackets[100];

    printf("Enter expression: ");
    scanf(" %99[^\n]", inputBrackets);

    int inputLen = strlen(inputBrackets);
    Stack stack = createStack();
    bool balanced = true;

    int index;
    for (index = 0; index < inputLen; index++)
    {
        char c = inputBrackets[index];

        if (c == '(' || c == '[' || c == '{')
        {
            push(stack, c);
            continue;
        }

        if (c == ')' || c == ']' || c == '}')
        {
            if (stack->top == NULL)
            {
                balanced = false;
                break;
            }

            char top = stack->top->data;
            if ((top == '(' && c == ')') ||
                (top == '[' && c == ']') ||
                (top == '{' && c == '}'))
            {
                silentPop(stack);
            }
            else
            {
                balanced = false;
                break;
            }
        }
    }

    if (balanced && stack->top == NULL)
        printf("Result: Balanced\n");
    else
        printf("Result: Not Balanced\n");

    // Free remaining nodes
    while (stack->top != NULL)
        silentPop(stack);
    free(stack);
}

void decimalToBinary()
{
    int decimal;

    printf("Enter a decimal number: ");
    scanf(" %d", &decimal);

    if (decimal == 0)
    {
        printf("Binary: 00000000\n");
        return;
    }

    Stack binaryStack = createStack();
    int original = decimal;

    do
    {
        push(binaryStack, decimal % 2);
        decimal /= 2;
    } while (decimal != 0);

    printf("Binary: ");
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
    printf("\n");

    free(binaryStack);
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
        reversedStr[currentRevLen]     = walker->data;
        reversedStr[currentRevLen + 1] = '\0';

        NodePtr temp = walker;
        walker = walker->next;
        free(temp);
    }
    free(stack);

    printf("Result: %s\n", strcmp(str, reversedStr) == 0 ? "Palindrome" : "Not Palindrome");
}

// Sorts stack from least (bottom) to greatest (top)
void sortStack(Stack stack)
{
    if (stack->count < 2)
    {
        printf("Need at least 2 elements to sort.\n");
        return;
    }

    Stack auxStack = createStack();

    while (stack->count > 0)
    {
        int topData = silentPeek(stack)->data;
        silentPop(stack);

        while (auxStack->count > 0 && auxStack->top->data < topData)
        {
            push(stack, silentPeek(auxStack)->data);
            silentPop(auxStack);
        }

        push(auxStack, topData);
    }

    stack->top   = auxStack->top;
    stack->count = auxStack->count;
    free(auxStack);
}

/*
 * Converts an infix expression to postfix notation.
 * Supports single-character operands (letters/digits) and
 * operators: +  -  *  /  ^  with parentheses.
 * Example:  a+b*c   →   a b c * +
 */
void infixToPostfix()
{
    char infix[200];
    char postfix[400];
    int  postfixLen = 0;

    printf("Enter infix expression: ");
    scanf(" %199[^\n]", infix);

    Stack stack = createStack();
    int len = strlen(infix);

    for (int i = 0; i < len; i++)
    {
        char c = infix[i];

        if (c == ' ') continue;

        // Operand — copy directly to output
        if (isalnum(c))
        {
            postfix[postfixLen++] = c;
            postfix[postfixLen++] = ' ';
        }
        // Left parenthesis — push onto stack
        else if (c == '(')
        {
            push(stack, c);
        }
        // Right parenthesis — pop until matching '('
        else if (c == ')')
        {
            while (stack->top != NULL && stack->top->data != '(')
            {
                postfix[postfixLen++] = (char)stack->top->data;
                postfix[postfixLen++] = ' ';
                silentPop(stack);
            }
            if (stack->top != NULL)
                silentPop(stack); // discard the '('
        }
        // Operator
        else if (isOperator(c))
        {
            // For right-associative '^', only pop operators of strictly higher precedence
            while (stack->top != NULL &&
                   stack->top->data != '(' &&
                   (c == '^' ? precedence(stack->top->data) > precedence(c)
                              : precedence(stack->top->data) >= precedence(c)))
            {
                postfix[postfixLen++] = (char)stack->top->data;
                postfix[postfixLen++] = ' ';
                silentPop(stack);
            }
            push(stack, c);
        }
        else
        {
            printf("Warning: unknown character '%c' skipped.\n", c);
        }
    }

    // Pop any remaining operators
    while (stack->top != NULL)
    {
        postfix[postfixLen++] = (char)stack->top->data;
        postfix[postfixLen++] = ' ';
        silentPop(stack);
    }

    postfix[postfixLen] = '\0';
    free(stack);

    printf("Postfix: %s\n", postfix);
}

/*
 * Evaluates a postfix expression.
 * Tokens must be separated by spaces.
 * Supports multi-digit integers and operators: +  -  *  /
 * Example input:  3 4 2 * +   →   Result: 11
 */
void evaluatePostfix()
{
    char expr[200];

    printf("Enter postfix expression (tokens separated by spaces): ");
    scanf(" %199[^\n]", expr);

    Stack stack = createStack();

    char *token = strtok(expr, " ");
    while (token != NULL)
    {
        // Single-character operator
        if (strlen(token) == 1 && isOperator(token[0]))
        {
            if (stack->count < 2)
            {
                printf("Error: not enough operands for operator '%c'.\n", token[0]);
                while (stack->top != NULL) silentPop(stack);
                free(stack);
                return;
            }

            int b = stack->top->data; silentPop(stack);
            int a = stack->top->data; silentPop(stack);
            int result = 0;

            switch (token[0])
            {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/':
                    if (b == 0)
                    {
                        printf("Error: division by zero.\n");
                        while (stack->top != NULL) silentPop(stack);
                        free(stack);
                        return;
                    }
                    result = a / b;
                    break;
            }

            push(stack, result);
        }
        else
        {
            // Assume it is an integer operand
            push(stack, atoi(token));
        }

        token = strtok(NULL, " ");
    }

    if (stack->count != 1)
    {
        printf("Error: invalid postfix expression.\n");
    }
    else
    {
        printf("Result: %d\n", stack->top->data);
    }

    while (stack->top != NULL) silentPop(stack);
    free(stack);
}

/*
 * Simulates an undo operation: removes the most recently pushed element
 * and displays the updated stack.
 */
void undoOperation(Stack stack)
{
    if (isEmpty(stack))
    {
        printf("Nothing to undo. Stack is empty.\n");
        return;
    }

    printf("Undo: removing top element %d.\n", stack->top->data);
    silentPop(stack);

    printf("Updated ");
    display(stack);
}