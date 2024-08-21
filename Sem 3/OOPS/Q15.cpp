#include <iostream>

using namespace std;

int max(int a, int b, int c)
{
    if (a >= b && a >= c){
        return a;
    }
    else if (b >= a && b >= c){
        return b;
    }
    else{
        return c;
    }
}

int max(int a[], int size)
{
    int max_element = a[0];
    for (int i = 1; i < size; i++)
    {
        if (a[i] > max_element)
            max_element = a[i];
    }
    return max_element;
}

int main()
{
    int arr[] = {1, 23, 40, -69, 72, 83};
    int size = sizeof(arr) / sizeof(arr[0]);
    int a = 40, b = 23, c = 72;
    cout << max(a, b, c) << "\n";
    cout << max(arr, size) << "\n";
}