#include <iostream>
using namespace std;


class OverflowException
{
public:
    OverflowException() {}
};

class UnderflowException
{
public:
    UnderflowException() {}
};

class Stack
{
private:
    int *buffer;
    int top;
    int size;

public:
    Stack(int);     
    void push(int); 
    int pop();      
    void disp();    
};

Stack::Stack(int sz)
{
    size = sz;
    buffer = (int *)malloc(size * sizeof(int));
    top = -1;
}

void Stack::push(int x)
{
    if (top == size - 1)
        throw OverflowException();
    else
        buffer[++top] = x;
}

int Stack::pop()
{
    if (top == -1)
        throw UnderflowException();
    else
        return buffer[top--];
}

void Stack::disp()
{
    cout << "Content of stack:\n";
    int ptr = top;
    while (ptr >= 0)
    {
        cout << buffer[ptr--] << " ";
    }
    cout << "\n";
}

int main()
{
    Stack st(5);

    try
    {
        /* int d1=st.pop();*/ //underflowException to be thrown
        st.push(1);
        st.push(2);
        st.push(3);
        st.push(4);
        st.disp();
        int d = st.pop();
        st.disp();
        st.push(5);
        st.push(6);
        st.disp();
        st.push(7); // OverflowException to be thrown
        st.disp();
        d = st.pop();
        st.disp();
    }
    catch (UnderflowException e)
    {
        cout << "Stack is empty!!\n";
    }
    catch (OverflowException e)
    {
        cout << "Stack overflow!!\n";
    }
}