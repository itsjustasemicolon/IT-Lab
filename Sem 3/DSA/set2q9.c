#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct
{
    int top;
    int array[MAX];
} Stack;

void initStack(Stack *s);
int isEmpty(Stack *s);
int isFull(Stack *s);
void push(Stack *s, int data);
int pop(Stack *s);
int peek(Stack *s);
void displayStack(Stack *s);

typedef struct
{
    Stack input;
    Stack output;
} Queue;

void initQueue(Queue *q);
void enqueue(Queue *q, int data);
int dequeue(Queue *q);
void displayQueue(Queue *q);

int main()
{
    Queue q;
    int choice, element;

   initQueue(&q);

    while (1)
    {
        printf("\nQueue Operations using Two Stacks\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the element to enqueue: ");
            scanf("%d", &element);
            enqueue(&q, element);
            break;

        case 2:
            element = dequeue(&q);
            if (element != -1)
            {
                printf("Dequeued element: %d\n", element);
            }
            break;

        case 3:
            displayQueue(&q);
            break;

        case 4:
            printf("Exiting...\n");
            exit(0);

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void initStack(Stack *s)
{
    s->top = -1;
}

int isEmpty(Stack *s)
{
    return s->top == -1;
}

int isFull(Stack *s)
{
    return s->top == MAX - 1;
}

void push(Stack *s, int data)
{
    if (isFull(s))
    {
        printf("Stack overflow\n");
        return;
    }
    s->array[++(s->top)] = data;
}

int pop(Stack *s)
{
    if (isEmpty(s))
    {
        printf("Stack underflow\n");
        return -1;
    }
    return s->array[(s->top)--];
}

int peek(Stack *s)
{
    if (isEmpty(s))
    {
        printf("Stack is empty\n");
        return -1;
    }
    return s->array[s->top];
}

void displayStack(Stack *s)
{
    if (isEmpty(s))
    {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack elements: ");
    for (int i = 0; i <= s->top; i++)
    {
        printf("%d ", s->array[i]);
    }
    printf("\n");
}

void initQueue(Queue *q)
{
    initStack(&q->input);
    initStack(&q->output);
}

void enqueue(Queue *q, int data)
{
    push(&q->input, data);
}

int dequeue(Queue *q)
{
    if (isEmpty(&q->output))
    {
        while (!isEmpty(&q->input))
        {
            push(&q->output, pop(&q->input));
        }
    }
    return pop(&q->output);
}

void displayQueue(Queue *q)
{
    if (isEmpty(&q->input) && isEmpty(&q->output))
    {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue elements: ");
    Stack temp;
    initStack(&temp);

    while (!isEmpty(&q->input))
    {
        push(&temp, pop(&q->input));
    }

    while (!isEmpty(&temp))
    {
        printf("%d ", pop(&temp));
    }

    while (!isEmpty(&q->output))
    {
        printf("%d ", pop(&q->output));
    }
    printf("\n");

    while (!isEmpty(&temp))
    {
        push(&q->input, pop(&temp));
    }
}
