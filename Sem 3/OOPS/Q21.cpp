#include <iostream>
#include <math.h>
#include <stdbool.h>

using namespace std;

class Vector
{
private:
    int size;
    double *arr;

public:
    Vector(double *arr, int size);
    Vector add(Vector);
    Vector subtract(Vector);
    double dot(Vector);      
    Vector multiply(Vector); 
    bool equal(Vector);
    void display();
};

Vector::Vector(double *arr, int size)
{
    this->arr = arr;
    this->size = size;
}

Vector Vector::add(Vector x)
{
    double *a = (double *)malloc(x.size * sizeof(double));
    for (int i = 0; i < size; i++)
    {
        a[i] = arr[i] + x.arr[i];
    }
    Vector res = Vector(a, size);
    return res;
}

Vector Vector::subtract(Vector x)
{
    double *a = (double *)malloc(x.size * sizeof(double));
    for (int i = 0; i < size; i++)
    {
        a[i] = arr[i] - x.arr[i];
    }
    Vector res = Vector(a, size);
    return res;
}

Vector Vector::multiply(Vector x)
{
    double *a = (double *)malloc(x.size * sizeof(double));
    for (int i = 0; i < size; i++)
    {
        a[i] = arr[i] * x.arr[i];
    }
    Vector res = Vector(a, size);
    return res;
}

double Vector::dot(Vector x)
{
    double res = 0.0;
    for (int i = 0; i < size; i++)
    {
        res += arr[i] * x.arr[i];
    }
    return res;
}

bool Vector::equal(Vector x)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] != x.arr[i])
            return false;
    }
    return true;
}

void Vector::display()
{
    cout << "[ ";
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << "]\n";
}

int main()
{
    double a[5] = {1, 2, 2.1, 0.5, 4.3};
    double b[5] = {4.3, 0.8, 2.2, 5, 1.9};
    Vector A = Vector(a, 5);
    Vector B = Vector(b, 5);
    Vector C = A.add(B);
    cout << "Addition of vector A and B results: ";
    C.display();
    C = A.subtract(B);
    cout << "Subtraction of vector B from A results: ";
    C.display();
    C = A.multiply(B);
    cout << "Multiplication of elements of A and B results: ";
    C.display();
    cout << "Dot product of A and B results: " << A.dot(B) << "\n";
    cout << "A and B equal ?" << A.equal(B) << "\n";
}