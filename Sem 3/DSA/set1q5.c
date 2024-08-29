#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 100

// Structure to represent a term in the polynomial
typedef struct {
    int coeff;  
    int exp;    
} Term;

void multiplyPolynomials(Term poly1[], int size1, Term poly2[], int size2, Term result[], int *sizeR) {
    // Temporary array to store intermediate terms
    Term temp[MAX_TERMS * MAX_TERMS];
    int tempSize = 0;

    // Multiply each term of poly1 with each term of poly2
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            int coeff = poly1[i].coeff * poly2[j].coeff;
            int exp = poly1[i].exp + poly2[j].exp;

            // Check if the term with this exponent already exists in temp
            int k;
            for (k = 0; k < tempSize; k++) {
                if (temp[k].exp == exp) {
                    temp[k].coeff += coeff;
                    break;
                }
            }
            if (k == tempSize) {
                // New term
                temp[tempSize].coeff = coeff;
                temp[tempSize].exp = exp;
                tempSize++;
            }
        }
    }

    // Copy the non-zero terms from temp to result
    int resultSize = 0;
    for (int i = 0; i < tempSize; i++) {
        if (temp[i].coeff != 0) {
            result[resultSize++] = temp[i];
        }
    }

    *sizeR = resultSize;  // Set the size of the result polynomial
}

// Function to display a polynomial
void displayPolynomial(Term poly[], int size) {
    if (size == 0) {
        printf("0");
        return;
    }

    for (int i = 0; i < size; i++) {
        if (i > 0 && poly[i].coeff > 0) {
            printf(" + ");
        }
        if (poly[i].coeff < 0) {
            printf(" - ");
        } else if (poly[i].coeff > 0 && i > 0) {
            printf(" + ");
        }
        if (poly[i].coeff != 0) {
            printf("%d", abs(poly[i].coeff));
            if (poly[i].exp != 0) {
                printf("x^%d", poly[i].exp);
            }
        }
    }
    printf("\n");
}
int main() {
    Term poly1[MAX_TERMS], poly2[MAX_TERMS], result[MAX_TERMS];
    int size1, size2, sizeR;

    // Input first polynomial
    printf("Enter the number of terms in the first polynomial: ");
    scanf("%d", &size1);
    printf("Enter the terms (coefficient exponent) of the first polynomial:\n");
    for (int i = 0; i < size1; i++) {
        scanf("%d %d", &poly1[i].coeff, &poly1[i].exp);
    }

    // Input second polynomial
    printf("Enter the number of terms in the second polynomial: ");
    scanf("%d", &size2);
    printf("Enter the terms (coefficient exponent) of the second polynomial:\n");
    for (int i = 0; i < size2; i++) {
        scanf("%d %d", &poly2[i].coeff, &poly2[i].exp);
    }

    // Multiply the polynomials
    multiplyPolynomials(poly1, size1, poly2, size2, result, &sizeR);

    // Display the result
    printf("The product of the polynomials is:\n");
    displayPolynomial(result, sizeR);

    return 0;
}

/* #include <stdio.h>

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
} */
