#include <iostream>

using namespace std;

class Stack
{
private:
    int *buffer;
    int top;
    int size;

public:
    Stack(int s) : size(s), top(-1)
    {
        buffer = new int[size];
    }

    void push(int item)
    {
        if (top < size - 1)
        {
            buffer[++top] = item;
        }
        else
        {
            cout << "Stack overflow, unable to push " << item << endl;
        }
    }

    int pop()
    {
        if (top >= 0)
        {
            return buffer[top--];
        }
        else
        {
            cout << "Stack underflow, no elements to pop" << endl;
            return -1;
        }
    }

    void disp()
    {
        if (top >= 0)
        {
            cout << "Stack elements (top to bottom): ";
            for (int i = top; i >= 0; --i)
            {
                cout << buffer[i] << " ";
            }
            cout << endl;
        }
        else
        {
            cout << "Stack is empty" << endl;
        }
    }

    ~Stack()
    {
        delete[] buffer;
    }
};

int main()
{
    Stack s(10);

    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);

    s.pop();

    s.disp();

    return 0;
}
