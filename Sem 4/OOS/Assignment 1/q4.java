class BankAccount
{
    int AccountNumber;
    float balance;
    String name;
    BankAccount(String n, int a,float b)
    {
        name=n;
        balanceance=b;
        AccountNumber=a;
    }
    void balance()
    {
        System.out.println("balance: "+ balance);
    }
    void add(float x)
    {
        balance+=x;
    }
    void sub(float x)
    {
        if((balance-x)>=0)
        balance-=x;
        else
        System.out.println("Insufficient balance");
    }
}
class accman
{
    int n;
    BankAccount account[];
    accman(int n)
    {
        this.n=n;
        account=new BankAccount[n];
    }
    void create(int i,String n, int a,float b)
    {
        account[i]=new BankAccount(n,a,b);
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
        System.out.println("Details:\nName: "+ account[i].name+"\nbalance: "+account[i].balance+"Acc no: "+ account[i].AccountNumber);
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
