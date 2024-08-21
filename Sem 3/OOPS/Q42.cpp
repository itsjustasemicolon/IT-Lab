#include <iostream>
using namespace std;

class Employee
{
protected:
    string name;
    double salary;

public:
    Employee(string n, double s)
    {
        name = n;
        salary = s;
    }
    string getName() { return name; }
    double getSalary() { return salary; }
    virtual void printDetails()
    {
        cout << "Name of employee: " << name << "\n";
        cout << "Salary of employee: " << salary << "\n";
    }
};

class Manager : public Employee
{
    string type;

public:
    Manager(string n, string t, double s) : Employee(n, s)
    {
        name = n;
        type = t;
        salary = s;
    }
    string getType() { return type; }
    void printDetails()
    {
        cout << "Name of manager: " << name << "\n";
        cout << "Type of manager: " << type << "\n";
        cout << "Salary of manager: " << salary << "\n";
    }
};

class Clerk : public Employee
{
    double allowance;

public:
    Clerk(string n, double s, double al) : Employee(n, s)
    {
        name = n;
        salary = s;
        allowance = al;
    }
    double getAllowance() { return allowance; }
    void printDetails()
    {
        cout << "Name of clerk: " << name << "\n";
        cout << "salary of clerk: " << salary << "\n";
        cout << "allowance of clerk: " << allowance << "\n";
    }
};

int main()
{

    Employee e1("Babbar", 50000), e2("Dhattarwal", 45000);
    Manager m1("Solksjaer", "Team Manager", 90000), m2("Guardiola", "Development Manager", 80000);
    Clerk c1("Mudi", 10000, 500), c2("Tramp", 9000, 300);

    Employee *E[6];

    E[0] = &e1;
    E[1] = &e2;

    E[2] = &m1;
    E[3] = &m2;

    E[4] = &c1;
    E[5] = &c2;

    for (int i = 0; i < 6; i++)
    {
        E[i]->printDetails();
        cout << "\n\n";
    }
}