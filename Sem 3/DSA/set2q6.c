#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

// Structure for stack
struct Stack
{
    int top;
    int capacity;
    int *array;
};

// Function to create a stack of given capacity
struct Stack *createStack(int capacity)
{
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (int *)malloc(stack->capacity * sizeof(int));
    return stack;
}

// Function to check if the stack is empty
int isEmpty(struct Stack *stack)
{
    return stack->top == -1;
}

// Function to push an element onto the stack
void push(struct Stack *stack, int item)
{
    stack->array[++stack->top] = item;
}

// Function to pop an element from the stack
int pop(struct Stack *stack)
{
    if (isEmpty(stack))
        return -1;
    return stack->array[stack->top--];
}

// Function to evaluate a postfix expression
int evaluatePostfix(char *exp)
{
    struct Stack *stack = createStack(strlen(exp));
    int i;

    // Scan all characters in the postfix expression
    for (i = 0; exp[i]; ++i)
    {
        // If the character is a number, push it onto the stack
        if (isdigit(exp[i]))
        {
            push(stack, exp[i] - '0'); // Convert character to integer
        }
        // If the character is an operator, pop two elements from the stack, apply the operator, and push the result back onto the stack
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

// Main function
int main()
{
    char exp[MAX];
    printf("Enter postfix expression: ");
    fgets(exp, MAX, stdin);
    exp[strcspn(exp, "\n")] = 0; // Remove the newline character from input

    printf("Postfix expression evaluates to: %d\n", evaluatePostfix(exp));

    return 0;
}
