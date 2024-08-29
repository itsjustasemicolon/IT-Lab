#include <stdio.h>
#include <stdlib.h>
#define MAX 100

struct CircularArrayQueue
{
    int front, rear, size;
    int array[MAX];
};

struct Node
{
    int data;
    struct Node *next;
};

struct CircularLinkedListQueue
{
    struct Node *front;
    struct Node *rear;
    int size;
};

void initCircularArrayQueue(struct CircularArrayQueue *q);
int isFullCircularArray(struct CircularArrayQueue *q);
int isEmptyCircularArray(struct CircularArrayQueue *q);
void enqueueCircularArray(struct CircularArrayQueue *q, int data);
int dequeueCircularArray(struct CircularArrayQueue *q);
int sizeCircularArray(struct CircularArrayQueue *q);
void displayCircularArrayQueue(struct CircularArrayQueue *q);

struct Node *createNode(int data);
void initCircularLinkedListQueue(struct CircularLinkedListQueue *q);
int isEmptyCircularLinkedList(struct CircularLinkedListQueue *q);
void enqueueCircularLinkedList(struct CircularLinkedListQueue *q, int data);
int dequeueCircularLinkedList(struct CircularLinkedListQueue *q);
int sizeCircularLinkedList(struct CircularLinkedListQueue *q);
void displayCircularLinkedListQueue(struct CircularLinkedListQueue *q);

int main()
{
    struct CircularArrayQueue arrayQueue;
    struct CircularLinkedListQueue linkedListQueue;
    int choice, element, method;

    initCircularArrayQueue(&arrayQueue);
    initCircularLinkedListQueue(&linkedListQueue);

    while (1)
    {
        printf("\nChoose the method:\n");
        printf("1. Array-based Circular Queue\n");
        printf("2. Linked List-based Circular Queue\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &method);

        if (method == 3)
        {
            printf("Exiting...\n");
            break;
        }

        printf("\nMenu:\n");
        printf("1. Insertion\n");
        printf("2. Deletion\n");
        printf("3. Check number of elements\n");
        printf("4. Display Queue\n");
        printf("5. Check Overflow/Underflow\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the element to insert: ");
            scanf("%d", &element);
            if (method == 1)
            {
                enqueueCircularArray(&arrayQueue, element);
            }
            else
            {
                enqueueCircularLinkedList(&linkedListQueue, element);
            }
            break;

        case 2:
            if (method == 1)
            {
                element = dequeueCircularArray(&arrayQueue);
            }
            else
            {
                element = dequeueCircularLinkedList(&linkedListQueue);
            }
            if (element != -1)
            {
                printf("%d deleted from queue\n", element);
            }
            break;

        case 3:
            if (method == 1)
            {
                printf("Number of elements: %d\n", sizeCircularArray(&arrayQueue));
            }
            else
            {
                printf("Number of elements: %d\n", sizeCircularLinkedList(&linkedListQueue));
            }
            break;

        case 4:
            if (method == 1)
            {
                displayCircularArrayQueue(&arrayQueue);
            }
            else
            {
                displayCircularLinkedListQueue(&linkedListQueue);
            }
            break;

        case 5:
            if (method == 1)
            {
                if (isFullCircularArray(&arrayQueue))
                {
                    printf("Queue overflow\n");
                }
                else if (isEmptyCircularArray(&arrayQueue))
                {
                    printf("Queue underflow\n");
                }
                else
                {
                    printf("Queue is neither full nor empty\n");
                }
            }
            else
            {
                if (isEmptyCircularLinkedList(&linkedListQueue))
                {
                    printf("Queue underflow\n");
                }
                else
                {
                    printf("Queue is not empty\n");
                }
            }
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void initCircularArrayQueue(struct CircularArrayQueue *q)
{
    q->front = -1;
    q->rear = -1;
    q->size = 0;
}

int isFullCircularArray(struct CircularArrayQueue *q)
{
    return ((q->rear + 1) % MAX == q->front);
}

int isEmptyCircularArray(struct CircularArrayQueue *q)
{
    return (q->front == -1);
}

void enqueueCircularArray(struct CircularArrayQueue *q, int data)
{
    if (isFullCircularArray(q))
    {
        printf("Queue overflow\n");
        return;
    }
    if (q->front == -1)
    { 
        q->front = 0;
    }
    q->rear = (q->rear + 1) % MAX;
    q->array[q->rear] = data;
    q->size++;
    printf("%d inserted into queue\n", data);
}

int dequeueCircularArray(struct CircularArrayQueue *q)
{
    if (isEmptyCircularArray(q))
    {
        printf("Queue underflow\n");
        return -1;
    }
    int data = q->array[q->front];
    if (q->front == q->rear)
    { 
        q->front = q->rear = -1;
    }
    else
    {
        q->front = (q->front + 1) % MAX;
    }
    q->size--;
    return data;
}

int sizeCircularArray(struct CircularArrayQueue *q)
{
    return q->size;
}

void displayCircularArrayQueue(struct CircularArrayQueue *q)
{
    if (isEmptyCircularArray(q))
    {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements: ");
    int i = q->front;
    while (i != q->rear)
    {
        printf("%d ", q->array[i]);
        i = (i + 1) % MAX;
    }
    printf("%d\n", q->array[i]);
}

struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void initCircularLinkedListQueue(struct CircularLinkedListQueue *q)
{
    q->front = q->rear = NULL;
    q->size = 0;
}

int isEmptyCircularLinkedList(struct CircularLinkedListQueue *q)
{
    return q->front == NULL;
}

void enqueueCircularLinkedList(struct CircularLinkedListQueue *q, int data)
{
    struct Node *newNode = createNode(data);
    if (isEmptyCircularLinkedList(q))
    {
        q->front = q->rear = newNode;
        q->rear->next = q->front; 
    }
    else
    {
        q->rear->next = newNode;
        q->rear = newNode;
        q->rear->next = q->front; 
    }
    q->size++;
    printf("%d inserted into queue\n", data);
}

int dequeueCircularLinkedList(struct CircularLinkedListQueue *q)
{
    if (isEmptyCircularLinkedList(q))
    {
        printf("Queue underflow\n");
        return -1;
    }
    int data = q->front->data;
    struct Node *temp = q->front;
    if (q->front == q->rear)
    { // Only one element in the queue
        q->front = q->rear = NULL;
    }
    else
    {
        q->front = q->front->next;
        q->rear->next = q->front; 
    }
    free(temp);
    q->size--;
    return data;
}

int sizeCircularLinkedList(struct CircularLinkedListQueue *q)
{
    return q->size;
}

void displayCircularLinkedListQueue(struct CircularLinkedListQueue *q)
{
    if (isEmptyCircularLinkedList(q))
    {
        printf("Queue is empty\n");
        return;
    }
    struct Node *temp = q->front;
    printf("Queue elements: ");
    do
    {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != q->front);
    printf("\n");
}
