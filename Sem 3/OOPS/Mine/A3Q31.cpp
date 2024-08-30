#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
    int age;
    float height;

public:
    Person() : name(""), age(0), height(0.0f) {}
    Person(string n, int a, float h) : name(n), age(a), height(h) {}

    void setName(string n) { name = n; }
    string getName() const { return name; }

    void setAge(int a) { age = a; }
    int getAge() const { return age; }

    void setHeight(float h) { height = h; }
    float getHeight() const { return height; }

    virtual void printDetails() const {
        cout << "Name: " << name << ", Age: " << age << ", Height: " << height << endl;
    }
};

class Student : public Person {
private:
    int roll;
    int yearOfAdmission;

public:
    Student() : Person(), roll(0), yearOfAdmission(0) {}
    Student(string n, int a, float h, int r, int y) : Person(n, a, h), roll(r), yearOfAdmission(y) {}

    void setRoll(int r) { roll = r; }
    int getRoll() const { return roll; }

    void setYearOfAdmission(int y) { yearOfAdmission = y; }
    int getYearOfAdmission() const { return yearOfAdmission; }


    void printDetails() const{
        cout << "Name: " << name << ", Age: " << age << ", Height: " << height
             << ", Roll: " << roll << ", Year of Admission: " << yearOfAdmission << endl;
    }
};

int main() {
    Person p1("Alice", 30, 5.5f);
    Student s1("Bob", 20, 5.9f, 101, 2022);

    p1.printDetails();
    s1.printDetails();

    Person* persons[4];
    persons[0] = new Person("John", 40, 6.0f);
    persons[1] = new Person("Mary", 25, 5.4f);
    persons[2] = new Student("Charlie", 22, 5.8f, 102, 2021);
    persons[3] = new Student("Diana", 19, 5.6f, 103, 2023);

    for (int i = 0; i < 4; i++) {
        persons[i]->printDetails();
    }

    for (int i = 0; i < 4; i++) {
        delete persons[i];
    }

    return 0;
}
