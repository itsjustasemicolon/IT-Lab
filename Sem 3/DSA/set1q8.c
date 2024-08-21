#include <stdio.h>

#define ROWS 3
#define COLS 3

void countNonZeroElements(int matrix[ROWS][COLS])
{
    int row, col, count;

    for (row = 0; row < ROWS; row++)
    {
        count = 0;
        for (col = 0; col < COLS; col++)
        {
            if (matrix[row][col] != 0)
            {
                count++;
            }
        }
        printf("Number of non-zero elements in row %d: %d\n", row + 1, count);
    }
}

int main()
{
    int matrix[ROWS][COLS] = {
        {1, 0, 3},
        {0, 2, 0},
        {4, 0, 5}};

    countNonZeroElements(matrix);

    return 0;
}