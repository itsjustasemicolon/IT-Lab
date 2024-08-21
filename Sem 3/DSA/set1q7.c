#include <stdio.h>

#define MAX_SIZE 100

typedef struct
{
    int row;
    int col;
    int value;
} Element;

typedef struct
{
    Element data[MAX_SIZE];
    int rows;
    int cols;
    int count;
} SparseMatrix;

void addSparseMatrices(SparseMatrix matrix1, SparseMatrix matrix2, SparseMatrix *result)
{
    if (matrix1.rows != matrix2.rows || matrix1.cols != matrix2.cols)
    {
        printf("Error: Matrices have different dimensions\n");
        return;
    }

    result->rows = matrix1.rows;
    result->cols = matrix1.cols;
    result->count = 0;

    int i = 0, j = 0;
    while (i < matrix1.count && j < matrix2.count)
    {
        if (matrix1.data[i].row < matrix2.data[j].row ||
            (matrix1.data[i].row == matrix2.data[j].row && matrix1.data[i].col < matrix2.data[j].col))
        {
            result->data[result->count++] = matrix1.data[i++];
        }
        else if (matrix1.data[i].row > matrix2.data[j].row ||
                 (matrix1.data[i].row == matrix2.data[j].row && matrix1.data[i].col > matrix2.data[j].col))
        {
            result->data[result->count++] = matrix2.data[j++];
        }
        else
        {
            int sum = matrix1.data[i].value + matrix2.data[j].value;
            if (sum != 0)
            {
                Element element = {matrix1.data[i].row, matrix1.data[i].col, sum};
                result->data[result->count++] = element;
            }
            i++;
            j++;
        }
    }

    while (i < matrix1.count)
    {
        result->data[result->count++] = matrix1.data[i++];
    }

    while (j < matrix2.count)
    {
        result->data[result->count++] = matrix2.data[j++];
    }
}

void displaySparseMatrix(SparseMatrix matrix)
{
    printf("Sparse Matrix:\n");
    for (int i = 0; i < matrix.count; i++)
    {
        printf("%d %d %d\n", matrix.data[i].row, matrix.data[i].col, matrix.data[i].value);
    }
}

int main()
{
    SparseMatrix matrix1 = {
        .data = {{0, 0, 1}, {1, 1, 2}, {2, 2, 3}},
        .rows = 3,
        .cols = 3,
        .count = 3};

    SparseMatrix matrix2 = {
        .data = {{0, 0, 4}, {1, 1, 5}, {2, 2, 6}},
        .rows = 3,
        .cols = 3,
        .count = 3};

    SparseMatrix result;
    addSparseMatrices(matrix1, matrix2, &result);
    displaySparseMatrix(result);

    return 0;
}