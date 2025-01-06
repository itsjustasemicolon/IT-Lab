class BankAccount
{
    int AccountNumber;
    String ownerName;
    double balance;
    
    BankAccount(String n, int accNo, double bal)
    {
        ownerName = "";
        accNo = 0;
        balance = 0.0;
    }
    
    void balance()
    {
        System.out.println("Balance : "+balance);
    }
    
    void add(double x)
    {
        balance += x;
    }
    
    void sub(double x)
    {
        if((balance-x)<0)
        {
            System.out.println("Insufficient Balance");
            return;
        }
        
        balance -= x;
    }
    
}

class AccountManager
{
    int n;
    BankAccount account[];
    
    AccountManager(int n)
    {
        this.n = n;
        account = new BankAccount[n];
        
    }
    
    void create(int i, String n, int accNo, double bal )
    {
        BankAccount acc = new BankAccount(n, accNo, bal);
        account[i++]=acc;
    }
    void delete(int i)
    {
        System.out.println("Account Deleted ");
        account[i]=null;
    }
    
    void deposit(int i, double x)
    {
        account[i].add(x);
    }
    
    void withdraw(int i, double x)
    {
        account[i].sub(x);
    }
    
    void details()
    {
        System.out.println("Details = ");
        System.out.println("Name = "+account[i].ownerName);
        System.out.println("Account Number = "+account[i].AccountNumber);
        System.out.println("Balance = "+account[i].balance);
    }
}

class Bank
{
    public static void main(String args[])
    {
        AccountManager manager = new AccountManager(5);
        manager.create(0,"A",100,100.00);
        manager.create(1,"B",200,200.00);
        manager.create(2,"C",300,300.00);
        manager.create(3,"D",400,400.00);
        manager.create(4,"E",500,500.00);
        
        manager.details(0);
        manager.details(1);
        manager.details(2);
        manager.details(3);
        manager.details(4);

        
    }
}
