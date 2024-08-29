#include <stdio.h>
#include <stdlib.h>
#define MAX 100

struct ArrayQueue
{
    int front, rear, size;
    int array[MAX];
};

struct Node
{
    int data;
    struct Node *next;
};

struct LinkedListQueue
{
    struct Node *front;
    struct Node *rear;
    int size;
};

void initArrayQueue(struct ArrayQueue *q);
int isFullArray(struct ArrayQueue *q);
int isEmptyArray(struct ArrayQueue *q);
void enqueueArray(struct ArrayQueue *q, int data);
int dequeueArray(struct ArrayQueue *q);
int sizeArray(struct ArrayQueue *q);
void displayArrayQueue(struct ArrayQueue *q);

struct Node *createNode(int data);
void initLinkedListQueue(struct LinkedListQueue *q);
int isEmptyLinkedList(struct LinkedListQueue *q);
void enqueueLinkedList(struct LinkedListQueue *q, int data);
int dequeueLinkedList(struct LinkedListQueue *q);
int sizeLinkedList(struct LinkedListQueue *q);
void displayLinkedListQueue(struct LinkedListQueue *q);

int main()
{
    struct ArrayQueue arrayQueue;
    struct LinkedListQueue linkedListQueue;
    int choice, element, method;

    initArrayQueue(&arrayQueue);
    initLinkedListQueue(&linkedListQueue);

    while (1)
    {
        printf("\nChoose the method:\n");
        printf("1. Array-based Queue\n");
        printf("2. Linked List-based Queue\n");
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
                enqueueArray(&arrayQueue, element);
            }
            else
            {
                enqueueLinkedList(&linkedListQueue, element);
            }
            break;

        case 2:
            if (method == 1)
            {
                element = dequeueArray(&arrayQueue);
            }
            else
            {
                element = dequeueLinkedList(&linkedListQueue);
            }
            if (element != -1)
            {
                printf("%d deleted from queue\n", element);
            }
            break;

        case 3:
            if (method == 1)
            {
                printf("Number of elements: %d\n", sizeArray(&arrayQueue));
            }
            else
            {
                printf("Number of elements: %d\n", sizeLinkedList(&linkedListQueue));
            }
            break;

        case 4:
            if (method == 1)
            {
                displayArrayQueue(&arrayQueue);
            }
            else
            {
                displayLinkedListQueue(&linkedListQueue);
            }
            break;

        case 5:
            if (method == 1)
            {
                if (isFullArray(&arrayQueue))
                {
                    printf("Queue overflow\n");
                }
                else if (isEmptyArray(&arrayQueue))
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
                if (isEmptyLinkedList(&linkedListQueue))
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

void initArrayQueue(struct ArrayQueue *q)
{
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

int isFullArray(struct ArrayQueue *q)
{
    return q->size == MAX;
}

int isEmptyArray(struct ArrayQueue *q)
{
    return q->size == 0;
}

void enqueueArray(struct ArrayQueue *q, int data)
{
    if (isFullArray(q))
    {
        printf("Queue overflow\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX;
    q->array[q->rear] = data;
    q->size++;
    printf("%d inserted into queue\n", data);
}

int dequeueArray(struct ArrayQueue *q)
{
    if (isEmptyArray(q))
    {
        printf("Queue underflow\n");
        return -1;
    }
    int data = q->array[q->front];
    q->front = (q->front + 1) % MAX;
    q->size--;
    return data;
}

int sizeArray(struct ArrayQueue *q)
{
    return q->size;
}

void displayArrayQueue(struct ArrayQueue *q)
{
    if (isEmptyArray(q))
    {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = q->front, count = 0; count < q->size; count++)
    {
        printf("%d ", q->array[i]);
        i = (i + 1) % MAX;
    }
    printf("\n");
}

struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void initLinkedListQueue(struct LinkedListQueue *q)
{
    q->front = q->rear = NULL;
    q->size = 0;
}

int isEmptyLinkedList(struct LinkedListQueue *q)
{
    return q->front == NULL;
}

void enqueueLinkedList(struct LinkedListQueue *q, int data)
{
    struct Node *newNode = createNode(data);
    if (isEmptyLinkedList(q))
    {
        q->front = q->rear = newNode;
    }
    else
    {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
    printf("%d inserted into queue\n", data);
}

int dequeueLinkedList(struct LinkedListQueue *q)
{
    if (isEmptyLinkedList(q))
    {
        printf("Queue underflow\n");
        return -1;
    }
    int data = q->front->data;
    struct Node *temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL)
    {
        q->rear = NULL;
    }
    free(temp);
    q->size--;
    return data;
}

int sizeLinkedList(struct LinkedListQueue *q)
{
    return q->size;
}

void displayLinkedListQueue(struct LinkedListQueue *q)
{
    if (isEmptyLinkedList(q))
    {
        printf("Queue is empty\n");
        return;
    }
    struct Node *temp = q->front;
    printf("Queue elements: ");
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
