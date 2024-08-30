#include <iostream>
#include <string>
using namespace std;

class Employee {
protected:
    string name;
    float salary;

public:
    Employee() : name(""), salary(0.0f) {}
    Employee(string n, float s) : name(n), salary(s) {}

    void setName(string n) { name = n; }
    string getName() const { return name; }

    void setSalary(float s) { salary = s; }
    float getSalary() const { return salary; }

    virtual void printDetails() const {
        cout << "Name: " << name << ", Salary: " << salary << endl;
    }
};

class Manager : public Employee {
private:
    string type;

public:
    Manager() : Employee(), type("") {}
    Manager(string n, float s, string t) : Employee(n, s), type(t) {}

    void setType(string t) { type = t; }
    string getType() const { return type; }

    void printDetails() const override {
        cout << "Name: " << name << ", Salary: " << salary << ", Type: " << type << endl;
    }
};

class Clerk : public Employee {
private:
    float allowance;

public:
    Clerk() : Employee(), allowance(0.0f) {}
    Clerk(string n, float s, float a) : Employee(n, s), allowance(a) {}

    void setAllowance(float a) { allowance = a; }
    float getAllowance() const { return allowance; }

    void printDetails() const override {
        cout << "Name: " << name << ", Salary: " << salary << ", Allowance: " << allowance << endl;
    }
};

int main() {
    Manager m1("Alice", 50000.0f, "Senior Manager");
    Clerk c1("Bob", 25000.0f, 2000.0f);

    m1.printDetails();
    c1.printDetails();

    Employee* employees[6];
    employees[0] = new Employee("John", 30000.0f);
    employees[1] = new Employee("Mary", 32000.0f);
    employees[2] = new Manager("Charlie", 60000.0f, "Project Manager");
    employees[3] = new Manager("Diana", 55000.0f, "Assistant Manager");
    employees[4] = new Clerk("Eve", 27000.0f, 1500.0f);
    employees[5] = new Clerk("Frank", 28000.0f, 1800.0f);

    float totalSalary = 0.0f;
    for (int i = 0; i < 6; i++) {
        employees[i]->printDetails();
        totalSalary += employees[i]->getSalary();
    }

    cout << "Total salary drawn by all employees: " << totalSalary << endl;

    for (int i = 0; i < 6; i++) {
        delete employees[i];
    }

    return 0;
}
