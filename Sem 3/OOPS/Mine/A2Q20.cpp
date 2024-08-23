#include <iostream>

using namespace std;

class IntArray
{
private:
    int *data;
    int size;

public:
    // Constructor
    IntArray(int size) : size(size)
    {
        data = new int[size];
    }

    // Constructor with initializer list
    IntArray(initializer_list<int> list) : size(list.size())
    {
        data = new int[size];
        int index = 0;
        for (int value : list)
        {
            data[index++] = value;
        }
    }

    // Copy constructor
    IntArray(const IntArray &other) : size(other.size)
    {
        data = new int[size];
        for (int i = 0; i < size; ++i)
        {
            data[i] = other.data[i];
        }
    }

    // Destructor
    ~IntArray()
    {
        delete[] data;
    }

    // Get size of the array
    int getSize() const
    {
        return size;
    }

    // Overload the [] operator for array access
    int &operator[](int index)
    {
        if (index < 0 || index >= size)
        {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }

    const int &operator[](int index) const
    {
        if (index < 0 || index >= size)
        {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }

    // Addition of two IntArrays
    IntArray operator+(const IntArray &other) const
    {
        if (size != other.size)
        {
            throw invalid_argument("Arrays must be of the same size for addition");
        }
        IntArray result(size);
        for (int i = 0; i < size; ++i)
        {
            result[i] = data[i] + other[i];
        }
        return result;
    }

    // Reverse the array
    void reverse()
    {
        for (int i = 0; i < size / 2; ++i)
        {
            int temp = data[i];
            data[i] = data[size - i - 1];
            data[size - i - 1] = temp;
        }
    }

    // Sort the array (Bubble Sort)
    void sort()
    {
        for (int i = 0; i < size - 1; ++i)
        {
            for (int j = 0; j < size - i - 1; ++j)
            {
                if (data[j] > data[j + 1])
                {
                    int temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }
    }

    // Print the elements of the array
    void print() const
    {
        for (int i = 0; i < size; ++i)
        {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    // Create an IntArray object with elements 1, 2, 3
    IntArray arr1 = {1, 2, 3};
    cout << "Elements of arr1: ";
    arr1.print();

    // Create a copy of arr1
    IntArray arr2 = arr1;
    cout << "Elements of arr2 (copy of arr1): ";
    arr2.print();

    // Reverse the elements of arr2
    arr2.reverse();
    cout << "Elements of arr2 after reversing: ";
    arr2.print();

    // Print elements of arr1 to ensure it is unchanged
    cout << "Elements of arr1 after reversing arr2: ";
    arr1.print();

    return 0;
}
