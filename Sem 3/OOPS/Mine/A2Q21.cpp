#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class SavingsAccount
{
private:
    string accountHolderName;
    int accountNumber;
    double balance;
    static double interestRate;
    static int accountCounter;

public:
    SavingsAccount(string name, double initialBalance)
        : accountHolderName(name), accountNumber(++accountCounter)
    {
        if (initialBalance < 1000)
        {
            cerr << "Initial balance must be at least Rs. 1000. Setting balance to Rs. 1000.\n";
            balance = 1000;
        }
        else
        {
            balance = initialBalance;
        }
    }

    void deposit(double amount)
    {
        if (amount > 0)
        {
            balance += amount;
        }
        else
        {
            cerr << "Deposit amount must be positive.\n";
        }
    }

    void withdraw(double amount)
    {
        if (amount > 0)
        {
            if (balance - amount >= 1000)
            {
                balance -= amount;
            }
            else
            {
                cerr << "Cannot withdraw. Minimum balance of Rs. 1000 must be maintained.\n";
            }
        }
        else
        {
            cerr << "Withdrawal amount must be positive.\n";
        }
    }

    double calculateInterest() const
    {
        return balance * interestRate / 100;
    }

    void addInterest()
    {
        balance += calculateInterest();
    }

    double getBalance() const
    {
        return balance;
    }

    static double getInterestRate()
    {
        return interestRate;
    }

    static void setInterestRate(double rate)
    {
        if (rate >= 0)
        {
            interestRate = rate;
        }
        else
        {
            cerr << "Interest rate must be non-negative.\n";
        }
    }

    int getAccountNumber() const
    {
        return accountNumber;
    }
};

double SavingsAccount::interestRate = 3.5; 
int SavingsAccount::accountCounter = 0;

int main()
{
    const int NUM_ACCOUNTS = 100;
    vector<SavingsAccount> accounts;
    srand(time(0));

    for (int i = 0; i < NUM_ACCOUNTS; ++i)
    {
        double initialBalance = 1000 + rand() % 99001; 
        accounts.emplace_back("AccountHolder" + to_string(i + 1), initialBalance);
    }

    double totalInterest = 0;
    for (auto &account : accounts)
    {
        double interest = account.calculateInterest();
        totalInterest += interest;
        account.addInterest();
    }

    cout << "Total interest paid to all accounts in one year: Rs. " << totalInterest << endl;

    return 0;
}
