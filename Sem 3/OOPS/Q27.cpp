#include <iostream>
using namespace std;

class Queue
{
    int *data;
    int front, rear;
    int size;

public:
    Queue(int);    
    void add(int); 
    int remove();  
    void disp();   
};

Queue::Queue(int sz)
{
    size = sz;
    data = (int *)malloc(size * sizeof(int));
    front = rear = -1;
}

void Queue::add(int x)
{
    if (rear == front - 1 || (front == 0 && rear == size - 1))
    {
        cout << "Queue overflow\n";
        return;
    }
    if (front == -1){
        front = rear = 0, data[rear] = x;
    }
    else if (front != 0 && rear == size - 1){
        rear = 0, data[rear] = x;
    } 
    else{
        data[++rear] = x;
    }
}

int Queue::remove()
{
    if (front == -1){ 
        return -99999;
    }
    int top;           
    if (front == rear){ 
        top = data[front], front = rear = -1;
    }
    else if (front == size - 1){
        top = data[front], front = 0;
    }
    else{
        top = data[front++];
    }
    return top;
}

void Queue::disp()
{
    cout << "Contents of queue:\n";
    if (front <= rear)
    {
        for (int i = front; i <= rear; i++)
            cout << data[i] << " ";
    }
    else
    {
        for (int i = front; i < size; i++)
            cout << data[i] << " ";
        for (int i = 0; i <= rear; i++)
            cout << data[i] << " ";
    }
    cout << "\n";
}

int main()
{
    Queue q(10);
    q.add(2);
    q.add(4);
    q.add(6);
    q.add(8);
    int d = q.remove();
    d = q.remove();
    q.disp();
}