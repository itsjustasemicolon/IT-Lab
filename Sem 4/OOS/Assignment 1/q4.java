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
        manager.create(10,"Soham",1000,10560f);
        manager.create(20,"Anuska",1001,65200f);
        manager.create(30,"Debodit",1002,84300f);
        manager.create(40,"Rishika",1003,12400f);
        manager.create(50,"Prama",1004,96500f);
        manager.details(10);
        manager.details(20);
        manager.details(30);
        manager.details(40);
        manager.details(50);
    }
}
