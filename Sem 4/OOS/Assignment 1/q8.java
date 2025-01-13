class Account {
    String accountNumber;
    String holderName;
    double balance;

    Account(String accountNumber, String holderName, double balance) {
        this.accountNumber = accountNumber;
        this.holderName = holderName;
        this.balance = balance;
    }

    public String getAccNo() {
        return accountNumber;
    }

    public String getHolderName() {
        return holderName;
    }

    public double getBalance() {
        return balance;
    }

    public void setBalance(double balance) {
        this.balance = balance;
    }

    public void printDetails() {
        System.out.println("Account Number: " + accountNumber);
        System.out.println("Holder Name: " + holderName);
        System.out.println("Balance: " + balance);
    }
}

class SavingsAccount extends Account {
    double interestRate;

    public SavingsAccount(String accountNumber, String holderName, double balance, double interestRate) {
        super(accountNumber, holderName, balance);
        this.interestRate = interestRate;
    }

    public double calcYearlyInt() {
        return getBalance() * interestRate / 100;
    }

    public void printSavingsDetails() {
        printDetails();
        System.out.println("Interest Rate: " + interestRate + "%");
    }
}

class CurrentAccount extends Account {
    double overdraftLimit;

    public CurrentAccount(String accountNumber, String holderName, double balance, double overdraftLimit) {
        super(accountNumber, holderName, balance);
        this.overdraftLimit = overdraftLimit;
    }

    public double getOverdraftLimit() {
        return overdraftLimit;
    }

    public void printCurrentDetails() {
        printDetails();
        System.out.println("Overdraft Limit: " + overdraftLimit);
    }
}

class Manager {
    private Account[] accounts;
    private int count;

    public Manager(int size) {
        accounts = new Account[size];
        count = 0;
    }

    public void addAccount(Account account) {
        if (count < accounts.length) {
            accounts[count++] = account;
        } else {
            System.out.println("No more accounts can be added.");
        }
    }

    public void displayAllAccounts() {
        for (int i = 0; i < count; i++) {
            if (accounts[i] instanceof SavingsAccount) {
                ((SavingsAccount) accounts[i]).printSavingsDetails();
            } else if (accounts[i] instanceof CurrentAccount) {
                ((CurrentAccount) accounts[i]).printCurrentDetails();
            }
            System.out.println();
        }
    }

    public void calcIntForSavings() {
        for (int i = 0; i < count; i++) {
            if (accounts[i] instanceof SavingsAccount) {
                SavingsAccount sa = (SavingsAccount) accounts[i];
                System.out.println("Yearly Interest for Account " + sa.getAccNo() + ": " + sa.calcYearlyInt());
            }
        }
    }
}

class Demo {
    public static void main(String[] args) {
        Manager manager = new Manager(5);

        SavingsAccount sa1 = new SavingsAccount("SA101", "Soham", 10000, 5);
        SavingsAccount sa2 = new SavingsAccount("SA102", "Debodit", 15000, 4.5);

        CurrentAccount ca1 = new CurrentAccount("CA201", "Prama", 20000, 5000);
        CurrentAccount ca2 = new CurrentAccount("CA202", "Rishika", 25000, 7000);
        CurrentAccount ca3 = new CurrentAccount("CA203", "Anuska", 30000, 10000);

        manager.addAccount(sa1);
        manager.addAccount(sa2);
        manager.addAccount(ca1);
        manager.addAccount(ca2);
        manager.addAccount(ca3);

        System.out.println("Details of all accounts:");
        manager.displayAllAccounts();

        System.out.println("Calculating yearly interest for Savings Accounts:");
        manager.calcIntForSavings();
    }
}
