#include <iostream>

using namespace std;

class IntArray
{
private:
    int *arr;
    int size;

public:
    IntArray(int size)
    {
        this->size = size;
        arr = new int[size];
    }

    ~IntArray()
    {
        delete[] arr;
    }

    int &operator[](int index)
    {
        if (index >= 0 && index < size)
        {
            return arr[index];
        }
        else
        {
            cout << "Index out of bounds";
            exit(-1);
        }
    }

    friend ostream &operator<<(ostream &os, const IntArray &iArray)
    {
        for (int i = 0; i < iArray.size; i++)
        {
            os << iArray.arr[i] << " ";
        }
        return os;
    }
};

int main()
{
    IntArray i(10);
    for (int k = 0; k < 10; k++)
        i[k] = k;

    cout << i;
    return 0;
}
