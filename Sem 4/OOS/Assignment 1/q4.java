class BankAccount {
    int accountNumber;
    float balance;
    String ownerName;

    BankAccount(String ownerName, int accountNumber, float balance) {
        this.ownerName = ownerName;
        this.accountNumber = accountNumber;
        this.balance = balance;
    }

    void showBalance() {
        System.out.println("Balance: " + balance);
    }

    void add(float x) {
        balance += x;
    }

    void sub(float x) {
        if ((balance - x) >= 0)
            balance -= x;
        else
            System.out.println("Insufficient balance");
    }
}

class AccountManager {
    int n;
    BankAccount account[];

    AccountManager(int n) {
        this.n = n;
        account = new BankAccount[n];
    }

    void create(int i, String n, int a, float b) {
        if (i >= 0 && i < account.length)
            account[i] = new BankAccount(n, a, b);
        else
            System.out.println("Invalid account index");
    }

    void delete(int i) {
        if (i >= 0 && i < account.length && account[i] != null) {
            System.out.println("Account terminated");
            account[i] = null;
        } else {
            System.out.println("Invalid account index");
        }
    }

    void deposit(int i, float x) {
        if (i >= 0 && i < account.length && account[i] != null) {
            account[i].add(x);
        } else {
            System.out.println("Invalid account index");
        }
    }

    void withdraw(int i, float x) {
        if (i >= 0 && i < account.length && account[i] != null) {
            account[i].sub(x);
        } else {
            System.out.println("Invalid account index");
        }
    }

    void details(int i) {
        if (i >= 0 && i < account.length && account[i] != null) {
            System.out.println("Details:\nName: " + account[i].ownerName +
                    "\nBalance: " + account[i].balance +
                    "\nAcc no: " + account[i].accountNumber);
        } else {
            System.out.println("Invalid account index");
        }
    }
}

public class bank {
    public static void main(String[] args) {
        AccountManager manager = new AccountManager(5);
        manager.create(0, "Soham", 1000, 10560f);
        manager.create(1, "Anuska", 1001, 65200f);
        manager.create(2, "Debodit", 1002, 84300f);
        manager.create(3, "Rishika", 1003, 12400f);
        manager.create(4, "Prama", 1004, 96500f);

        manager.details(0);
        manager.details(1);
        manager.details(2);
        manager.details(3);
        manager.details(4);
    }
}
