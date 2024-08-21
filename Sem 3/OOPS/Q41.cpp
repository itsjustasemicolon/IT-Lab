#include <iostream>
using namespace std;

class Person
{
protected:
    string name;
    int age;
    float height;

public:
    Person(string n, int a, float h)
    {
        name = n;
        age = a;
        height = h;
    }
    string getName() { return name; }
    int getAge() { return age; }
    float getHeight() { return height; }
    virtual void printDetails()
    {
        cout << "Name: " << name << "\n";
        cout << "Age: " << age << "\n";
        cout << "Height: " << height << "\n";
    }
};

class Student : public Person
{
    int roll, year;

public:
    Student(string n, int a, float h, int r, int yr) : Person(n, a, h)
    {
        name = n;
        age = a;
        height = h;
        roll = r;
        year = yr;
    }
    int getRoll() { return roll; }
    int getYear() { return year; }
    void printDetails()
    {
        cout << "Name: " << name << "\n";
        cout << "Age: " << age << "\n";
        cout << "Height: " << height << "\n";
        cout << "Roll: " << roll << "\n";
        cout << "Year of admission: " << year << "\n";
    }
};

int main()
{

    Person p = Person("Aritra", 18, 5.7);
    p.printDetails();

    cout << "\n\n";

    Student s = Student("Aritra", 18, 5.7, 09, 2019);
    s.printDetails();

    cout << "\n\n";

    Person *P[4];

    Person p1("Edinsonn", 33, 6.7), p2("Pogba", 27, 6.6);
    Student s1("Sattam", 19, 5.8, 15, 2019), s2("Soumitri", 19, 6.1, 83, 2019);

    P[0] = &p1;
    P[1] = &p2;
    P[2] = &s1;
    P[3] = &s2;

    for (int i = 0; i < 4; i++)
    {
        P[i]->printDetails();
        cout << "\n\n";
    }
}