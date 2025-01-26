import java.util.Scanner;

class Student {
    String name;
    int rollNo;
    String[] subjects;

    Student(String name, int rollNo, String[] subjects) {
        this.name = name;
        this.rollNo = rollNo;
        this.subjects = subjects;
    }

    String getName() {
        return name;
    }

    int getRollNo() {
        return rollNo;
    }

    String[] getSubjects() {
        return subjects;
    }
}

class TabulationSheet {
    String subject;
    int[] rollNos;
    int[] marks;
    int count;

    TabulationSheet(String subject, int capacity) {
        this.subject = subject;
        rollNos = new int[capacity];
        marks = new int[capacity];
        count = 0;
    }

    public void addMarks(int rollNo, int mark) {
        if (count < rollNos.length) {
            rollNos[count] = rollNo;
            marks[count] = mark;
            count++;
        }
    }

    int getMark(int rollNo) {
        for (int i = 0; i < count; i++) {
            if (rollNos[i] == rollNo) {
                return marks[i];
            }
        }
        return -1; 
    }

    String getSubject() {
        return subject;
    }
}

class MarkSheet {
    String studentName;
    String[] subjects;
    int[] marks;
    int count;

    MarkSheet(String studentName, int subjectCount) {
        this.studentName = studentName;
        subjects = new String[subjectCount];
        marks = new int[subjectCount];
        count = 0;
    }

    void addMarks(String subject, int mark) {
        if (count < subjects.length) {
            subjects[count] = subject;
            marks[count] = mark;
            count++;
        }
    }

    void printMarkSheet() {
        System.out.println("Marksheet for: " + studentName);
        for (int i = 0; i < count; i++) {
            System.out.println(subjects[i] + ": " + marks[i]);
        }
        System.out.println();
    }
}

class Main {
    public static void main(String[] args) {
        String[] subjects = {"Math", "Physics", "Chemistry", "Biology", "English"};

        Student[] students = {
            new Student("Alice", 101, subjects),
            new Student("Bob", 102, subjects),
            new Student("Charlie", 103, subjects)
        };

        TabulationSheet[] tabSheets = new TabulationSheet[subjects.length];
        for (int i = 0; i < subjects.length; i++) {
            tabSheets[i] = new TabulationSheet(subjects[i], students.length);
        }

        int[][] marksData = {
            {85, 90, 75},
            {80, 88, 70},
            {78, 84, 65},
            {92, 85, 80},
            {88, 79, 82}
        };

        for (int i = 0; i < subjects.length; i++) {
            for (int j = 0; j < students.length; j++) {
                tabSheets[i].addMarks(students[j].getRollNo(), marksData[i][j]);
            }
        }

        MarkSheet[] markSheets = new MarkSheet[students.length];
        for (int i = 0; i < students.length; i++) {
            markSheets[i] = new MarkSheet(students[i].getName(), subjects.length);
            for (TabulationSheet tabSheet : tabSheets) {
                markSheets[i].addMarks(tabSheet.getSubject(), tabSheet.getMark(students[i].getRollNo()));
            }
        }

        for (MarkSheet markSheet : markSheets) {
            markSheet.printMarkSheet();
        }
    }
}
