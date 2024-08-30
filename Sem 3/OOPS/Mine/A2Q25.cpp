#include <iostream>

using namespace std;

class Queue
{
private:
    int *data;
    int front, rear;
    int size;

public:
    Queue(int s) : size(s), front(-1), rear(-1)
    {
        data = new int[size];
    }

    void add(int item)
    {
        if ((rear + 1) % size == front)
        {
            cout << "Queue overflow, unable to add " << item << endl;
        }
        else
        {
            if (front == -1)
                front = 0;
            rear = (rear + 1) % size;
            data[rear] = item;
        }
    }

    int remove()
    {
        if (front == -1)
        {
            cout << "Queue underflow, no elements to remove" << endl;
            return -1;
        }
        else
        {
            int removedItem = data[front];
            if (front == rear)
            {
                front = -1;
                rear = -1;
            }
            else
            {
                front = (front + 1) % size;
            }
            return removedItem;
        }
    }

    void disp()
    {
        if (front == -1)
        {
            cout << "Queue is empty" << endl;
        }
        else
        {
            cout << "Queue elements (front to rear): ";
            int i = front;
            while (true)
            {
                cout << data[i] << " ";
                if (i == rear)
                    break;
                i = (i + 1) % size;
            }
            cout << endl;
        }
    }

    ~Queue()
    {
        delete[] data;
    }
};

int main()
{
    Queue q(10);

    q.add(2);
    q.add(3);
    q.add(4);
    q.add(5);

    q.remove();
    q.remove();

    q.disp();

    return 0;
}
