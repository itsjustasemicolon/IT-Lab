#include <iostream>
#include <math.h>

using namespace std;


class Complex
{
private:
    float real, imag;

public:
    Complex()
    {
        real = imag = 0;
    }
    Complex(float r, float i)
    {
        real = r;
        imag = i;
    }
    void disp()
    {
        cout << '(' << real << ',' << imag << ")";
    }
};


class Stack
{
private:
    int *buffer;
    int top;
    int size;

public:
    Stack()
    {
        size = 0;
        top = -1;
    }
    Stack(int sz)
    {
        size = sz;
        buffer = (int *)malloc(size * sizeof(int));
        top = -1;
    }
    void push(int x)
    {
        if (top == size - 1)
        {
            cout << "Overflow\n";
            return;
        }
        buffer[++top] = x;
    }
    int pop()
    {
        if (top == -1){
            return -99999;
        }
        else{
            return buffer[top--];
        }
    }
    void disp()
    {
        int ptr = top;
        while (ptr >= 0)
        {
            cout << buffer[ptr--] << " ";
        }
        cout << "\n";
    }
};


template <class T>
void _swap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <>
void _swap(Stack &s1, Stack &s2)
{
    Stack temp = s1;
    s1 = s2;
    s2 = temp;
}

int main()
{
    int x1 = 7, x2 = 10;

    cout << "Before swapping :\n";
    cout << "x1=" << x1 << "\nx2=" << x2 << "\n\n";

    _swap(x1, x2);

    cout << "After swapping :\n";
    cout << "x1=" << x1 << "\nx2=" << x2 << "\n\n";

    Complex c1(3, -3), c2(-6, 6);

    cout << "Before swapping :\n";
    cout << "c1=";
    c1.disp();
    cout << "\nc2=";
    c2.disp();
    cout << "\n\n";


    _swap(c1, c2);

    cout << "After swapping :\n";
    cout << "c1=";
    c1.disp();
    cout << "\nc2=";
    c2.disp();
    cout << "\n\n";

    Stack s1(5), s2(6);
    s1.push(2), s1.push(3), s1.push(4), s1.push(5);
    s2.push(6), s2.push(7), s2.push(8), s2.push(9), s2.push(1);

    cout << "Before swapping :\n";
    cout << "s1: ";
    s1.disp();
    cout << "s2: ";
    s2.disp();

    _swap(s1, s2);

    cout << "After swapping :\n";
    cout << "s1: ";
    s1.disp();
    cout << "s2: ";
    s2.disp();
}