#include <stdio.h>

// Structure to represent a term in the polynomial
typedef struct
{
    int coefficient;
    int exponent;
} Term;

// Function to multiply two sparse polynomials
void multiplyPolynomials(Term poly1[], int size1, Term poly2[], int size2, Term result[])
{
    int i, j, k = 0;

    // Initialize the result polynomial
    for (i = 0; i < size1 + size2; i++)
    {
        result[i].coefficient = 0;
        result[i].exponent = 0;
    }

    // Multiply each term of poly1 with each term of poly2
    for (i = 0; i < size1; i++)
    {
        for (j = 0; j < size2; j++)
        {
            result[k].coefficient = poly1[i].coefficient * poly2[j].coefficient;
            result[k].exponent = poly1[i].exponent + poly2[j].exponent;
            k++;
        }
    }
}

int main()
{
    // Example sparse polynomials
    Term poly1[] = {{2, 3}, {4, 1}, {3, 0}};
    int size1 = sizeof(poly1) / sizeof(poly1[0]);

    Term poly2[] = {{-1, 2}, {2, 1}, {1, 0}};
    int size2 = sizeof(poly2) / sizeof(poly2[0]);

    // Resultant polynomial
    Term result[size1 + size2];

    // Multiply the polynomials
    multiplyPolynomials(poly1, size1, poly2, size2, result);

    // Display the result
    printf("Resultant Polynomial:\n");
    for (int i = 0; i < size1 + size2; i++)
    {
        printf("%dx^%d ", result[i].coefficient, result[i].exponent);
        if (i != size1 + size2 - 1)
        {
            printf("+ ");
        }
    }
    printf("\n");

    return 0;
}