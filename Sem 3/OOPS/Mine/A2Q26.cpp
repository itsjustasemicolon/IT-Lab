#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class GradeCard
{
private:
    string department;
    string studentName;
    string rollNumber;
    int semester;
    string subjects[5];
    double marks[5];
    double CGPA;

    double calculateCGPA()
    {
        double totalMarks = 0;
        for (int i = 0; i < 5; ++i)
        {
            totalMarks += marks[i];
        }
        return totalMarks / 5;
    }

public:
    GradeCard(string dept, string name, string roll, int sem, string subs[5], double mks[5])
        : department(dept), studentName(name), rollNumber(roll), semester(sem)
    {
        for (int i = 0; i < 5; ++i)
        {
            subjects[i] = subs[i];
            marks[i] = mks[i];
        }
        CGPA = calculateCGPA();
    }

    double getCGPA() const
    {
        return CGPA;
    }

    string getStudentName() const
    {
        return studentName;
    }

    string getRollNumber() const
    {
        return rollNumber;
    }

    void disp() const
    {
        cout << "Department: " << department << endl;
        cout << "Student Name: " << studentName << endl;
        cout << "Roll Number: " << rollNumber << endl;
        cout << "Semester: " << semester << endl;
        cout << "Subjects and Marks: " << endl;
        for (int i = 0; i < 5; ++i)
        {
            cout << subjects[i] << ": " << marks[i] << endl;
        }
        cout << "CGPA: " << CGPA << endl;
    }
};

int main()
{
    const int numStudents = 60;
    GradeCard *gradeCards[numStudents];
    string department = "Computer Science";
    int semester = 3;
    string subjects[5] = {"Math", "Physics", "Chemistry", "Computer Science", "Electronics"};

    for (int i = 0; i < numStudents; ++i)
    {
        string studentName = "Student" + to_string(i + 1);
        string rollNumber = "CS2023" + to_string(100 + i);
        double marks[5];
        for (int j = 0; j < 5; ++j)
        {
            marks[j] = rand() % 101;
        }
        gradeCards[i] = new GradeCard(department, studentName, rollNumber, semester, subjects, marks);
    }

    GradeCard *highestCGPAStudent = gradeCards[0];
    for (int i = 1; i < numStudents; ++i)
    {
        if (gradeCards[i]->getCGPA() > highestCGPAStudent->getCGPA())
        {
            highestCGPAStudent = gradeCards[i];
        }
    }

    cout << "Student with the highest CGPA:\n";
    cout << "Name: " << highestCGPAStudent->getStudentName() << endl;
    cout << "Roll Number: " << highestCGPAStudent->getRollNumber() << endl;
    cout << "CGPA: " << highestCGPAStudent->getCGPA() << endl;

    for (int i = 0; i < numStudents; ++i)
    {
        delete gradeCards[i];
    }

    return 0;
}
