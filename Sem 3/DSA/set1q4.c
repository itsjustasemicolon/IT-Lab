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
    Term polynomial[] = {
        {2, 3},  // 2x^3
        {-4, 2}, // -4x^2
        {3, 1}   // 3x^1
    };
    int numTerms = sizeof(polynomial) / sizeof(polynomial[0]);
    int x = 2;
    int result = evaluatePolynomial(polynomial, numTerms, x);
    printf("Result: %d\n", result);

    return 0;
}
