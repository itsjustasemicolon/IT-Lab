#include <iostream>
#include <string>

using namespace std;

class Person
{
protected:
    string name;
    int age;
    double height;

public:
    Person(string personName, int personAge, double personHeight)
    {
        name = personName;
        age = personAge;
        height = personHeight;
    }

    void printDetails()
    {
        cout << "Name: " << name << ", Age: " << age << ", Height: " << height << endl;
    }
};

class Student : public Person
{
private:
    int roll;
    int yearOfAdmission;

public:
    Student(string studentName, int studentAge, double studentHeight, int studentRoll, int studentYearOfAdmission)
        : Person(studentName, studentAge, studentHeight)
    {
        roll = studentRoll;
        yearOfAdmission = studentYearOfAdmission;
    }

    void printDetails()
    {
        cout << "Name: " << name << ", Age: " << age << ", Height: " << height
             << ", Roll: " << roll << ", Year of Admission: " << yearOfAdmission << endl;
    }
};

int main()
{
    Person person("John Doe", 45, 5.9);
    Student student("Jane Smith", 20, 5.6, 101, 2022);

    person.printDetails();
    student.printDetails();

    Person *people[4];

    people[0] = new Person("Alice Brown", 50, 5.7);
    people[1] = new Person("Bob White", 55, 5.8);
    people[2] = new Student("Charlie Green", 22, 5.9, 102, 2021);
    people[3] = new Student("David Black", 21, 5.7, 103, 2020);

    for (int i = 0; i < 4; ++i)
    {
        people[i]->printDetails();
    }

    for (int i = 0; i < 4; ++i)
    {
        delete people[i];
    }

    return 0;
}
