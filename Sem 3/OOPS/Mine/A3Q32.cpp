#include <iostream>
#include <string>

using namespace std;

class Employee
{
protected:
    string name;
    double salary;

public:
    Employee(string empName, double empSalary)
    {
        name = empName;
        salary = empSalary;
    }

    virtual void printDetails()
    {
        cout << "Name: " << name << ", Salary: " << salary << endl;
    }

    double getSalary()
    {
        return salary;
    }

    virtual ~Employee() {}
};

class Manager : public Employee
{
private:
    string type;

public:
    Manager(string mgrName, double mgrSalary, string mgrType)
        : Employee(mgrName, mgrSalary)
    {
        type = mgrType;
    }

    void printDetails()
    {
        cout << "Name: " << name << ", Salary: " << salary
             << ", Type: " << type << endl;
    }
};

class Clerk : public Employee
{
private:
    double allowance;

public:
    Clerk(string clerkName, double clerkSalary, double clerkAllowance)
        : Employee(clerkName, clerkSalary)
    {
        allowance = clerkAllowance;
    }

    void printDetails()
    {
        cout << "Name: " << name << ", Salary: " << salary
             << ", Allowance: " << allowance << endl;
    }
};

int main()
{
    Manager mgr("John Doe", 75000, "Operations");
    Clerk clk("Jane Smith", 35000, 5000);

    mgr.printDetails();
    clk.printDetails();

    Employee *employees[6];

    employees[0] = new Employee("Alice Brown", 50000);
    employees[1] = new Employee("Bob White", 55000);
    employees[2] = new Manager("Charlie Green", 80000, "Sales");
    employees[3] = new Manager("David Black", 82000, "HR");
    employees[4] = new Clerk("Eve Blue", 36000, 4000);
    employees[5] = new Clerk("Frank Red", 37000, 4500);

    double totalSalary = 0;
    for (int i = 0; i < 6; ++i)
    {
        employees[i]->printDetails();
        totalSalary += employees[i]->getSalary();
    }

    cout << "Total Salary drawn by all employees: " << totalSalary << endl;

    for (int i = 0; i < 6; ++i)
    {
        delete employees[i];
    }

    return 0;
}
