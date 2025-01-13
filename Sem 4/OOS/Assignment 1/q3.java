class Stack
{
    int[] arr;
    int top;
    int capacity;

    Stack(int size)
    {
        capacity = size;
        arr = new int[capacity];
        top = -1;
    }

    void push(int data)
    {
        if(top==(capacity-1))
        {
            System.out.println("Stack Overflow");
            return;
        }
        arr[++top]=data;
    }

    int pop()
    {
        if(top == -1)
        {
            System.out.println("Stack Underflow");
            return -1;
        }
        return arr[top--];
    }

    void print()
      {
        if(top == -1)
        {
            System.out.println("Stack is empty");
            return;
        }
        System.out.println("Stack contents : ");
        for(int i = top;i>=0;i--)
        {
            System.out.print(arr[i]+ " ");
        }
        System.out.println();
    }
}

class Demo
{
    public static void main(String args[])
    {
        Stack stk = new Stack(30);
        stk.push(10);
        stk.push(20);
        stk.push(30);
        stk.push(15);
        stk.push(9);

        System.out.println("Stack : ");
        stk.print();
        System.out.println("Popping 3 elements : ");
       System.out.println(stk.pop());
       System.out.println(stk.pop());
       System.out.println(stk.pop());

        System.out.println("Stack after popping : ");
        stk.print();
    }
}
