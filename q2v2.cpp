#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;
const double r = 0.05; // Assuming 5% interest rate
const double min_bal=1000.0;


struct SavingsAccount {
    char name[50];
    int acc;
    double bal;
};


// Function to withdraw from the account
bool withdraw(SavingsAccount &account, double amount) {
    if (account.bal - amount < min_bal) {
        cout << "Withdrawal denied! Minimum bal requirement not met." << endl;
        return false;
    } else {
        account.bal -= amount;
        return true;
    }
}

// Function to deposit into the account
void deposit(SavingsAccount &account, double amount) {
    account.bal += amount;
}

void interest(SavingsAccount *account,const int n)
{
    double interest[n],s=0;
    for(int i=0;i<n;i++)
    {
        interest[i]=(account[i].bal)*r;
        cout<<"\nInterest paid to acc no. "<<account[i].acc<<" : "<<interest[i];
        s+=interest[i];
        deposit(account[i],interest[i]);
    }
    cout<<"\nTotal interest: "<<s;
}
int main() {
    const int n = 3;
    SavingsAccount account[n];
    
    // Creating 100 account with random balances
    for (int i = 0; i < n; i++) {
        cout<<"\nAccount "<<(i+1)<<"\n";
        cout<<"Name: ";
        cin>>account[i].name;
        account[i].acc = 1000 + i; // Assuming account numbers start from 1000
        cout<<"Acc no.: "<<account[i].acc;
        account[i].bal = min_bal + rand() % 99001;
        cout<<"\nBalance.: "<<account[i].bal;
    }
    
    interest(account,n);
    
    // Displaying account details and total interest paid
    cout << "\nAccount details after interest calculation:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Name: " << account[i].name << ", Account Number: " << account[i].acc 
             << ", Balance: " << account[i].bal << endl;
    }
    
    return 0;
}