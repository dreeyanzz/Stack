#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "struct.h"
#include "functions.h"
#include "stack.h"
#include "queue_struct.h"
#include "queue.h"

#define QUEUE_CAPACITY 10

// ── Shared UI helpers ────────────────────────────────────────────────────────

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
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();
}

static void printDivider()
{
    printf("==================================================\n");
}

static void printThinDivider()
{
    printf("--------------------------------------------------\n");
}

// ── Main menu ────────────────────────────────────────────────────────────────

static void printMainMenu()
{
    printDivider();
    printf("        STACK & QUEUE — LINKED LIST / ARRAY       \n");
    printDivider();
    printf("  [1]  Stack Operations\n");
    printf("  [2]  Queue Operations\n");
    printf("\n  [0]  Exit\n");
    printDivider();
    printf("  Choice: ");
}

// ── Stack sub-menu ───────────────────────────────────────────────────────────

static void printStackMenu()
{
    printDivider();
    printf("         STACK OPERATIONS  (Linked List)          \n");
    printDivider();
    printf(" --- Core ---\n");
    printf("  [1]  Push a value\n");
    printf("  [2]  Pop top value\n");
    printf("  [3]  Peek at top value\n");
    printf("  [4]  Display stack\n");
    printf("  [5]  Check isFull\n");
    printf("  [6]  Check isEmpty\n");
    printf("\n --- Applications ---\n");
    printf("  [7]  Reverse a string\n");
    printf("  [8]  Check balanced brackets\n");
    printf("  [9]  Infix to Postfix\n");
    printf("  [10] Evaluate Postfix expression\n");
    printf("  [11] Decimal to Binary\n");
    printf("  [12] Palindrome check\n");
    printf("  [13] Sort the stack\n");
    printf("  [14] Undo last push\n");
    printf("\n  [0]  Back to main menu\n");
    printDivider();
    printf("  Choice: ");
}

static void runStackMenu(Stack stack)
{
    int choice;

    do
    {
        clearScreen();
        printStackMenu();
        scanf(" %d", &choice);
        clearScreen();

        printDivider();
        printf("         STACK OPERATIONS  (Linked List)          \n");
        printThinDivider();

        switch (choice)
        {
            case 1:
            {
                if (isFull(stack)) { printf("Overflow: Stack is full.\n"); break; }
                int value;
                printf("Enter value to push: ");
                scanf(" %d", &value);
                push(stack, value);
                printf("Pushed %d.\n\n", value);
                display(stack);
                break;
            }
            case 2:
                pop(stack);
                printf("\n");
                display(stack);
                break;

            case 3:
                peek(stack);
                break;

            case 4:
                display(stack);
                break;

            case 5:
                printf("Stack is %s.\n",
                       isFull(stack)
                           ? "FULL"
                           : "NOT full  (linked list — no fixed capacity)");
                break;

            case 6:
                printf("Stack is %s.\n",
                       isEmpty(stack) ? "EMPTY" : "NOT empty");
                break;

            case 7:  reverseString();        break;
            case 8:  checkBalanced();        break;
            case 9:  infixToPostfix();       break;
            case 10: evaluatePostfix();      break;
            case 11: decimalToBinary();      break;
            case 12: palindromeCheck();      break;

            case 13:
                if (isEmpty(stack)) { printf("Stack is empty. Nothing to sort.\n"); break; }
                printf("Before sort:\n");
                display(stack);
                printf("\n");
                sortStack(stack);
                printf("\nAfter sort (greatest on top):\n");
                display(stack);
                break;

            case 14:
                undoOperation(stack);
                break;

            case 0:
                printf("Returning to main menu...\n");
                break;

            default:
                printf("Invalid choice.\n");
                break;
        }

        if (choice != 0) pauseScreen();

    } while (choice != 0);
}

// ── Queue sub-menu ───────────────────────────────────────────────────────────

static void printQueueMenu()
{
    printDivider();
    printf("          QUEUE OPERATIONS  (Array / FIFO)         \n");
    printDivider();
    printf(" --- Core ---\n");
    printf("  [1]  Enqueue a value\n");
    printf("  [2]  Dequeue front value\n");
    printf("  [3]  Peek at front\n");
    printf("  [4]  Peek at rear\n");
    printf("  [5]  Display queue\n");
    printf("  [6]  Check isFull\n");
    printf("  [7]  Check isEmpty\n");
    printf("\n --- Applications ---\n");
    printf("  [8]  Reverse the queue\n");
    printf("  [9]  Palindrome check\n");
    printf("  [10] Generate binary numbers (1 to N)\n");
    printf("\n  [0]  Back to main menu\n");
    printDivider();
    printf("  Choice: ");
}

static void runQueueMenu(Queue queue)
{
    int choice;

    do
    {
        clearScreen();
        printQueueMenu();
        scanf(" %d", &choice);
        clearScreen();

        printDivider();
        printf("          QUEUE OPERATIONS  (Array / FIFO)         \n");
        printThinDivider();

        switch (choice)
        {
            case 1:
            {
                int value;
                printf("Enter value to enqueue: ");
                scanf(" %d", &value);
                enqueue(queue, value);
                if (!isQueueFull(queue) || queue->count > 0)
                {
                    printf("\n");
                    displayQueue(queue);
                }
                break;
            }

            case 2:
                dequeue(queue);
                printf("\n");
                displayQueue(queue);
                break;

            case 3:  peekFront(queue);    break;
            case 4:  peekRear(queue);     break;
            case 5:  displayQueue(queue); break;

            case 6:
                printf("Queue is %s  (capacity: %d).\n",
                       isQueueFull(queue)  ? "FULL" : "NOT full",
                       queue->capacity);
                break;

            case 7:
                printf("Queue is %s.\n",
                       isQueueEmpty(queue) ? "EMPTY" : "NOT empty");
                break;

            case 8:  reverseQueue(queue); break;
            case 9:  palindromeQueue();   break;
            case 10: generateBinary();    break;

            case 0:
                printf("Returning to main menu...\n");
                break;

            default:
                printf("Invalid choice.\n");
                break;
        }

        if (choice != 0) pauseScreen();

    } while (choice != 0);
}

// ── Entry point ───────────────────────────────────────────────────────────────

int main(void)
{
    srand((unsigned int)time(NULL));

    Stack stack = createStack();
    Queue queue = createQueue(QUEUE_CAPACITY);

    int choice;

    do
    {
        clearScreen();
        printMainMenu();
        scanf(" %d", &choice);

        switch (choice)
        {
            case 1:  runStackMenu(stack); break;
            case 2:  runQueueMenu(queue); break;
            case 0:
                clearScreen();
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice.\n");
                pauseScreen();
                break;
        }

    } while (choice != 0);

    // ── Cleanup ────────────────────────────────────────────────────────────
    while (stack->top != NULL)
    {
        NodePtr temp = stack->top;
        stack->top   = stack->top->next;
        free(temp);
    }
    free(stack);

    free(queue->data);
    free(queue);

    return 0;
}