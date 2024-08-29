#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

struct Stack
{
    int top;
    int capacity;
    int *array;
};

struct Stack *createStack(int capacity)
{
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (int *)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isEmpty(struct Stack *stack)
{
    return stack->top == -1;
}

void push(struct Stack *stack, int item)
{
    stack->array[++stack->top] = item;
}

int pop(struct Stack *stack)
{
    if (isEmpty(stack))
        return -1;
    return stack->array[stack->top--];
}

int evaluatePostfix(char *exp)
{
    struct Stack *stack = createStack(strlen(exp));
    int i;

    for (i = 0; exp[i]; ++i)
    {
        if (isdigit(exp[i]))
        {
            push(stack, exp[i] - '0'); 
        }
        else
        {
            int val1 = pop(stack);
            int val2 = pop(stack);
            switch (exp[i])
            {
            case '+':
                push(stack, val2 + val1);
                break;
            case '-':
                push(stack, val2 - val1);
                break;
            case '*':
                push(stack, val2 * val1);
                break;
            case '/':
                push(stack, val2 / val1);
                break;
            }
        }
    }
    return pop(stack);
}

int main()
{
    char exp[MAX];
    printf("Enter postfix expression: ");
    fgets(exp, MAX, stdin);
    exp[strcspn(exp, "\n")] = 0; 
    printf("Postfix expression evaluates to: %d\n", evaluatePostfix(exp));
    return 0;
}
