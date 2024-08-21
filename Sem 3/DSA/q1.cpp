#include <iostream>
#include <cstring>
using namespace std;

struct Student
{
    char name[50];
    char address[100];
    int marks[5];
};

void inputStudentData(Student *student)
{
    cout << "Enter name: ";
    cin.getline(student->name, 50);
    cout << "Enter address: ";
    cin.getline(student->address, 100);
    cout << "Enter marks for 5 subjects:\n";
    for (int i = 0; i < 5; i++)
    {
        cout << "Subject " << i + 1 << ": ";
        cin >> student->marks[i];
    }
    cin.ignore(); // Ignore the newline character
}

void displayStudentData(const Student *student)
{
    cout << "Name: " << student->name << endl;
    cout << "Address: " << student->address << endl;
    cout << "Marks: ";
    for (int i = 0; i < 5; i++)
    {
        cout << student->marks[i] << " ";
    }
    cout << endl;
}

bool hasPassed(const Student *student)
{
    int passCount = 0;
    for (int i = 0; i < 5; i++)
    {
        if (student->marks[i] >= 40)
        {
            passCount++;
        }
    }
    return passCount >= 3;
}

void findPassedAndFailedStudents(const Student *students, int count)
{
    cout << "Students who have passed in minimum three subjects:\n";
    for (int i = 0; i < count; i++)
    {
        if (hasPassed(&students[i]))
        {
            cout << students[i].name << endl;
        }
    }

    cout << "Students who have failed in minimum three subjects:\n";
    for (int i = 0; i < count; i++)
    {
        if (!hasPassed(&students[i]))
        {
            cout << students[i].name << endl;
        }
    }
}

void findMaxMathsMarks(const Student *students, int count)
{
    int maxMarks = -1;
    const Student *maxMarksStudent = nullptr;

    for (int i = 0; i < count; i++)
    {
        if (students[i].marks[0] > maxMarks)
        {
            maxMarks = students[i].marks[0];
            maxMarksStudent = &students[i];
        }
    }

    cout << "Student with maximum marks in Mathematics:\n";
    displayStudentData(maxMarksStudent);
}

void findMinPhysicsMarks(const Student *students, int count)
{
    int minMarks = 101;
    const Student *minMarksStudent = nullptr;

    for (int i = 0; i < count; i++)
    {
        if (students[i].marks[1] < minMarks)
        {
            minMarks = students[i].marks[1];
            minMarksStudent = &students[i];
        }
    }

    cout << "Student with minimum marks in Physics:\n";
    displayStudentData(minMarksStudent);
}

void findMaxAverageMarks(const Student *students, int count)
{
    float maxAverageMarks = -1;
    const Student *maxAverageMarksStudent = nullptr;

    for (int i = 0; i < count; i++)
    {
        int sum = 0;
        for (int j = 0; j < 5; j++)
        {
            sum += students[i].marks[j];
        }
        float average = static_cast<float>(sum) / 5;

        if (average > maxAverageMarks)
        {
            maxAverageMarks = average;
            maxAverageMarksStudent = &students[i];
        }
    }

    cout << "Student with maximum average marks:\n";
    displayStudentData(maxAverageMarksStudent);
}

void printStudentRecord(const Student *student)
{
    cout << "Name: " << student->name << endl;
    cout << "Total marks: ";
    int total = 0;
    for (int i = 0; i < 5; i++)
    {
        total += student->marks[i];
    }
    cout << total << endl;
}

void printStudentRecords(const Student *students, int count)
{
    cout << "Student records:\n";
    for (int i = 0; i < count; i++)
    {
        printStudentRecord(&students[i]);
    }
}

int main()
{
    const int MAX_STUDENTS = 12;
    Student students[MAX_STUDENTS];
    int studentCount = 0;

    int choice;
    do
    {
        cout << "Menu:\n";
        cout << "1. Add student record\n";
        cout << "2. Find passed and failed students\n";
        cout << "3. Find student with maximum marks in Mathematics\n";
        cout << "4. Find student with minimum marks in Physics\n";
        cout << "5. Find student with maximum average marks\n";
        cout << "6. Print student records\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            if (studentCount < MAX_STUDENTS)
            {
                cout << "Enter student details:\n";
                cin.ignore(); // Ignore the newline character
                inputStudentData(&students[studentCount]);
                studentCount++;
            }
            else
            {
                cout << "Maximum number of students reached!\n";
            }
            break;
        case 2:
            findPassedAndFailedStudents(students, studentCount);
            break;
        case 3:
            findMaxMathsMarks(students, studentCount);
            break;
        case 4:
            findMinPhysicsMarks(students, studentCount);
            break;
        case 5:
            findMaxAverageMarks(students, studentCount);
            break;
        case 6:
            printStudentRecords(students, studentCount);
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
            break;
        }

        cout << endl;
    } while (choice != 0);

    return 0;
}