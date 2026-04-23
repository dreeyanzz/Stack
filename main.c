#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "struct.h"
#include "functions.h"
#include "stack.h"

// ── Helpers ──────────────────────────────────────────────────────────────────

static void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

static void pauseScreen()
{
    printf("\nPress Enter to continue...");
    // Consume any leftover newline, then wait for the user
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();
}

static void printDivider()
{
    printf("--------------------------------------------------\n");
}

static void printHeader()
{
    printDivider();
    printf("          STACK OPERATIONS — LINKED LIST          \n");
    printDivider();
}

static void printMenu()
{
    printHeader();
    printf(" --- Core Stack Operations ---\n");
    printf("  [1]  Push a value\n");
    printf("  [2]  Pop top value\n");
    printf("  [3]  Peek at top value\n");
    printf("  [4]  Display entire stack\n");
    printf("  [5]  Check if stack is full\n");
    printf("  [6]  Check if stack is empty\n");
    printf("\n --- Stack Applications ---\n");
    printf("  [7]  Reverse a string\n");
    printf("  [8]  Check balanced brackets\n");
    printf("  [9]  Infix to Postfix conversion\n");
    printf("  [10] Evaluate a Postfix expression\n");
    printf("  [11] Decimal to Binary conversion\n");
    printf("  [12] Palindrome check\n");
    printf("  [13] Sort the stack\n");
    printf("  [14] Undo last push\n");
    printf("\n  [0]  Exit\n");
    printDivider();
    printf("  Choice: ");
}

// ── Entry point ───────────────────────────────────────────────────────────────

int main(void)
{
    srand((unsigned int)time(NULL));

    Stack mainStack = createStack();
    int choice;

    do
    {
        clearScreen();
        printMenu();
        scanf(" %d", &choice);

        clearScreen();
        printHeader();

        switch (choice)
        {
            // ── [1] Push ──────────────────────────────────────────────────────
            case 1:
            {
                if (isFull(mainStack))
                {
                    printf("Overflow: Stack is full.\n");
                    break;
                }
                int value;
                printf("Enter value to push: ");
                scanf(" %d", &value);
                push(mainStack, value);
                printf("Pushed %d onto the stack.\n\n", value);
                display(mainStack);
                break;
            }

            // ── [2] Pop ───────────────────────────────────────────────────────
            case 2:
                pop(mainStack);
                printf("\n");
                display(mainStack);
                break;

            // ── [3] Peek ──────────────────────────────────────────────────────
            case 3:
                peek(mainStack);
                break;

            // ── [4] Display ───────────────────────────────────────────────────
            case 4:
                display(mainStack);
                break;

            // ── [5] isFull ────────────────────────────────────────────────────
            case 5:
                printf("Stack is %s.\n",
                       isFull(mainStack) ? "FULL" : "NOT full (linked list has no fixed capacity)");
                break;

            // ── [6] isEmpty ───────────────────────────────────────────────────
            case 6:
                printf("Stack is %s.\n",
                       isEmpty(mainStack) ? "EMPTY" : "NOT empty");
                break;

            // ── [7] Reverse String ────────────────────────────────────────────
            case 7:
                reverseString();
                break;

            // ── [8] Balanced Brackets ─────────────────────────────────────────
            case 8:
                checkBalanced();
                break;

            // ── [9] Infix → Postfix ───────────────────────────────────────────
            case 9:
                infixToPostfix();
                break;

            // ── [10] Evaluate Postfix ─────────────────────────────────────────
            case 10:
                evaluatePostfix();
                break;

            // ── [11] Decimal → Binary ─────────────────────────────────────────
            case 11:
                decimalToBinary();
                break;

            // ── [12] Palindrome Check ─────────────────────────────────────────
            case 12:
                palindromeCheck();
                break;

            // ── [13] Sort Stack ───────────────────────────────────────────────
            case 13:
                if (isEmpty(mainStack))
                {
                    printf("Stack is empty. Nothing to sort.\n");
                    break;
                }
                printf("Before sort:\n");
                display(mainStack);
                printf("\n");
                sortStack(mainStack);
                printf("After sort (greatest on top):\n");
                display(mainStack);
                break;

            // ── [14] Undo ─────────────────────────────────────────────────────
            case 14:
                undoOperation(mainStack);
                break;

            // ── [0] Exit ──────────────────────────────────────────────────────
            case 0:
                printf("Exiting program. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please enter a number from the menu.\n");
                break;
        }

        if (choice != 0)
            pauseScreen();

    } while (choice != 0);

    // Free remaining stack nodes before exiting
    while (mainStack->top != NULL)
    {
        NodePtr temp = mainStack->top;
        mainStack->top = mainStack->top->next;
        free(temp);
    }
    free(mainStack);

    return 0;
}