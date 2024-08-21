#include <iostream>
using namespace std;

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
    {
        cout << "Overflow\n";
        return;
    }
    buffer[++top] = x;
}

int Stack::pop()
{
    if (top == -1)
        return -99999;
    else
        return buffer[top--];
}

void Stack::disp()
{
    cout << "Contents of stack:\n";
    int ptr = top;
    while (ptr >= 0)
    {
        cout << buffer[ptr--] << " ";
    }
    cout << "\n";
}

int main()
{
    Stack st(10);
    st.push(2);
    st.push(3);
    st.push(4);
    st.push(5);
    st.disp();
    int d = st.pop();
    st.disp();
    st.push(6);
    st.disp();
}