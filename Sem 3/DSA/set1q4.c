#include <stdio.h>
#include <math.h>
// Structure to represent a term in the polynomial
typedef struct
{
    int coefficient;
    int exponent;
} Term;

// Function to evaluate the polynomial
int evaluatePolynomial(Term polynomial[], int numTerms, int x)
{
    int result = 0;
    for (int i = 0; i < numTerms; i++)
    {
        result += polynomial[i].coefficient * pow(x, polynomial[i].exponent);
    }
    return result;
}

int main()
{
    // Example usage
    Term polynomial[100];
    int result, x, num;
    printf("Enter the number of terms : ");
    scanf(%d,&num);
    printf("Enter the terms of the polynomial: ");
    for(int i = 0;i<num;i++)
        {
            scanf("%d %d",&poly[i].coefficient,&poly[i].exponent);
        }
    printf("Enter the value of x: ");
    scanf("%d",&x);
    printf("Result : %d\n",result);
    return 0;
}
