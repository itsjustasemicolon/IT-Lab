#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct SavingsAccount
{
    char name[50];
    int accountNumber;
    double balance;
};

const double ir = 0.03; // 3% intr rate
const int min_bal = 1000;
const int total_acc = 100;

void deposit(SavingsAccount &account, double amount)
{
    account.balance += amount;
    cout << "Deposited Rs. " << amount << " to account number " << account.accountNumber << ". New balance: Rs. " << account.balance << endl;
}

void withdraw(SavingsAccount &account, double amount)
{
    if (account.balance - amount >= min_bal)
    {
        account.balance -= amount;
        cout << "Withdrawn Rs. " << amount << " from account number " << account.accountNumber << ". New balance: Rs. " << account.balance << endl;
    }
    else
    {
        cout << "Withdrawal amount exceeds minimum balance requirement." << endl;
    }
}

void calcInt(SavingsAccount accounts[], int size)
{
    double totInt = 0;
    for (int i = 0; i < size; ++i)
    {
        double intr = accounts[i].balance * ir;
        deposit(accounts[i], intr);
        totInt += intr;
    }
    cout << "Total intr paid to all accounts in one year: Rs. " << totInt << endl;
}

int main()
{
    srand(time(0));

    SavingsAccount accounts[total_acc];

    // Create accounts with random balances
    for (int i = 0; i < total_acc; ++i)
    {
        printf(accounts[i].name, "AccountHolder%d", i + 1);
        accounts[i].accountNumber = i + 1;
        accounts[i].balance = min_bal + rand() % 99001; // Random balance between 1000 and 100000
    }

    // Perform some operations on a few accounts for demonstration
    deposit(accounts[0], 5000);
    withdraw(accounts[1], 2000);
    withdraw(accounts[2], 95000);

    // Calculate and deposit intr for all accounts
    calcInt(accounts, total_acc);

    return 0;
}