class bacc
{
    int acno;
    float bal;
    String name;
    bacc(String n, int a,float b)
    {
        name=n;
        bal=b;
        acno=a;
    }
    void balance()
    {
        System.out.println("Balance: "+ bal);
    }
    void add(float x)
    {
        bal+=x;
    }
    void sub(float x)
    {
        if((bal-x)>=0)
        bal-=x;
        else
        System.out.println("Insufficient Balance");
    }
}
class accman
{
    int n;
    bacc account[];
    accman(int n)
    {
        this.n=n;
        account=new bacc[n];
    }
    void create(int i,String n, int a,float b)
    {
        account[i]=new bacc(n,a,b);
    }
    void delete(int i)
    {
        System.out.println("Account terminated");
        account[i]=null;
    }
    void deposit(int i,float x)
    {
        account[i].add(x);
    }
    void withdraw(int i, float x)
    {
        account[i].sub(x);
    }
    void details(int i)
    {
        System.out.println("Details:\nName: "+ account[i].name+"\nBalance: "+account[i].bal+"Acc no: "+ account[i].acno);
    }
    
}

class bank
{
    public static void main(String args[])
    {
        accman manager=new accman(5);
        manager.create(0,"A",100,100f);
        manager.create(1,"B",101,200f);
        manager.create(2,"C",102,300f);
        manager.create(3,"D",103,400f);
        manager.create(4,"E",104,500f);
        manager.details(0);
        manager.details(1);
        manager.details(2);
        manager.details(3);
        manager.details(4);
    }
}
