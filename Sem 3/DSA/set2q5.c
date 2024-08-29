#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Structure for stack
struct Stack
{
    int top;
    int capacity;
    char *array;
};

// Function to create a stack of given capacity
struct Stack *createStack(int capacity)
{
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (char *)malloc(stack->capacity * sizeof(char));
    return stack;
}

// Function to check if the stack is empty
int isEmpty(struct Stack *stack)
{
    return stack->top == -1;
}

// Function to check if the stack is full
int isFull(struct Stack *stack)
{
    return stack->top == stack->capacity - 1;
}

// Function to push an element onto the stack
void push(struct Stack *stack, char item)
{
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

// Function to pop an element from the stack
char pop(struct Stack *stack)
{
    if (isEmpty(stack))
        return -1;
    return stack->array[stack->top--];
}

// Function to peek the top element of the stack
char peek(struct Stack *stack)
{
    if (isEmpty(stack))
        return -1;
    return stack->array[stack->top];
}

// Function to check if a character is an operand
int isOperand(char ch)
{
    return isalnum(ch);
}

// Function to return the precedence of operators
int precedence(char ch)
{
    switch (ch)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    }
    return -1;
}

// Function to convert infix to postfix
void infixToPostfix(char *exp)
{
    int i, k;
    struct Stack *stack = createStack(strlen(exp));
    if (!stack) // Check if stack was created successfully
        return;

    for (i = 0, k = -1; exp[i]; ++i)
    {
        // If the character is an operand, add it to the output
        if (isOperand(exp[i]))
            exp[++k] = exp[i];

        // If the character is '(', push it to the stack
        else if (exp[i] == '(')
            push(stack, exp[i]);

        // If the character is ')', pop and output from the stack until '(' is found
        else if (exp[i] == ')')
        {
            while (!isEmpty(stack) && peek(stack) != '(')
                exp[++k] = pop(stack);
            if (!isEmpty(stack) && peek(stack) != '(')
                return; // Invalid expression
            else
                pop(stack);
        }
        else
        { // An operator is encountered
            while (!isEmpty(stack) && precedence(exp[i]) <= precedence(peek(stack)))
                exp[++k] = pop(stack);
            push(stack, exp[i]);
        }
    }

    // Pop all the operators from the stack
    while (!isEmpty(stack))
        exp[++k] = pop(stack);

    exp[++k] = '\0';
    printf("Postfix expression: %s\n", exp);
}

// Main function
int main()
{
    char exp[MAX];
    printf("Enter infix expression: ");
    fgets(exp, MAX, stdin);
    exp[strcspn(exp, "\n")] = 0; // Remove the newline character from input

    infixToPostfix(exp);

    return 0;
}
