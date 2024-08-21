#include <stdio.h>

int main()
{
    int i, arr[10];
    int new_arr[8];

    printf("Enter 10 elements of the array:\n");
    for (i = 0; i < 10; i++)
    {
        scanf("%d", &arr[i]);
    }

    int j = 0;
    for (i = 0; i < 10; i++)
    {
        if (i != 2 && i != 5)
        {
            new_arr[j] = arr[i];
            j++;
        }
    }
    printf("The 5th element of the resulting array is: %d\n", new_arr[4]);

    return 0;
}
