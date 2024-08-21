#include <stdio.h>
#include <stdlib.h>

int main() {
    char num1[1000], num2[1000], sum[1001];
    int carry = 0, i, j;

    printf("Enter the first number: ");
    scanf("%s", num1);

    printf("Enter the second number: ");
    scanf("%s", num2);

    // Adding the numbers digit by digit
    for (i = strlen(num1) - 1, j = strlen(num2) - 1; i >= 0 || j >= 0; i--, j--) {
        int digit1 = i >= 0 ? num1[i] - '0' : 0;
        int digit2 = j >= 0 ? num2[j] - '0' : 0;
        int sumDigit = digit1 + digit2 + carry;
        sum[i + 1] = sumDigit % 10 + '0';
        carry = sumDigit / 10;
    }

    // Handling the carry if any
    sum[0] = carry + '0';

    printf("Sum: %s\n", sum);

    return 0;
}