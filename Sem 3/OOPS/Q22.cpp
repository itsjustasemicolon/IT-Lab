#include <iostream>
using namespace std;

#define MAX_SIZE 10

class IntArray
{
private:
    int arr[MAX_SIZE];
    int size;

public:
    IntArray(int arr[], int size);
    IntArray(const IntArray &ia); 
    IntArray add(IntArray);
    void reverse();
    void display();
};

IntArray::IntArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        this->arr[i] = arr[i];
    }
    this->size = size;
}

IntArray::IntArray(const IntArray &ia)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = ia.arr[i];
    }
    size = ia.size;
}

IntArray IntArray::add(IntArray ia)
{
    int temp[size] = {0};
    for (int i = 0; i < size; i++)
    {
        temp[i] = arr[i] + ia.arr[i];
    }
    IntArray result = IntArray(temp, size);
    return result;
}

void IntArray::reverse()
{
    int l = 0, u = size - 1;
    while (l < u)
    {
        int temp = arr[l];
        arr[l] = arr[u];
        arr[u] = temp;
        l++;
        u--;
    }
}

void IntArray::display()
{
    cout << "displaying IntArray:\n";
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << "\n";
}

int main()
{
    int a[3] = {10, 20, 30};
    int b[3] = {40, 50, 60};

    IntArray ia = IntArray(a, 3);
    IntArray ib = IntArray(b, 3);

    IntArray ic = ia.add(ib);
    ic.display();

    IntArray icopy = IntArray(ib);
    icopy.display();

    icopy.reverse();

    icopy.display();
}