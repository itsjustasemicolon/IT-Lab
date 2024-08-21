#include <stdio.h>

// Structure to represent a term in the polynomial
typedef struct {
    int coefficient;
    int exponent;
} Term;

// Function to add two sparse polynomials
void addPolynomials(Term poly1[], int size1, Term poly2[], int size2, Term result[], int *size) {
    int i = 0, j = 0, k = 0;

    while (i < size1 && j < size2) {
        if (poly1[i].exponent > poly2[j].exponent) {
            result[k++] = poly1[i++];
        } else if (poly1[i].exponent < poly2[j].exponent) {
            result[k++] = poly2[j++];
        } else {
            result[k].exponent = poly1[i].exponent;
            result[k++].coefficient = poly1[i++].coefficient + poly2[j++].coefficient;
        }
    }

    while (i < size1) {
        result[k++] = poly1[i++];
    }

    while (j < size2) {
        result[k++] = poly2[j++];
    }

    *size = k;
}

int main() {
    Term poly1[] = {{5, 4}, {3, 2}, {2, 0}};
    int size1 = sizeof(poly1) / sizeof(poly1[0]);

    Term poly2[] = {{-2, 4}, {4, 3}, {1, 2}, {5, 1}};
    int size2 = sizeof(poly2) / sizeof(poly2[0]);

    Term result[100];
    int size;

    addPolynomials(poly1, size1, poly2, size2, result, &size);

    printf("Resultant polynomial: ");
    for (int i = 0; i < size; i++) {
        printf("%dx^%d ", result[i].coefficient, result[i].exponent);
        if (i != size - 1) {
            printf("+ ");
        }
    }

    return 0;
}