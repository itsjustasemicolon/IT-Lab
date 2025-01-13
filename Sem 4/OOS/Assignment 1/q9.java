class Person {
    int age;
    double weight;
    double height;
    String dateOfBirth;
    String address;

    public Person(int age, double weight, double height, String dateOfBirth, String address) {
        this.age = age;
        this.weight = weight;
        this.height = height;
        this.dateOfBirth = dateOfBirth;
        this.address = address;
    }

    public void printPersonDetails() {
        System.out.println("Age: " + age);
        System.out.println("Weight: " + weight);
        System.out.println("Height: " + height);
        System.out.println("Date of Birth: " + dateOfBirth);
        System.out.println("Address: " + address);
    }
}

class Employee extends Person {
    double salary;
    String dateOfJoining;
    int experience;

    public Employee(int age, double weight, double height, String dateOfBirth, String address,
                    double salary, String dateOfJoining, int experience) {
        super(age, weight, height, dateOfBirth, address);
        this.salary = salary;
        this.dateOfJoining = dateOfJoining;
        this.experience = experience;
    }

    public void printEmployeeDetails() {
        printPersonDetails();
        System.out.println("Salary: " + salary);
        System.out.println("Date of Joining: " + dateOfJoining);
        System.out.println("Experience: " + experience + " years");
    }
}

class Student extends Person {
    String roll;
    String[] listOfSubjects;
    int[] marks;

    public Student(int age, double weight, double height, String dateOfBirth, String address,
                   String roll, String[] listOfSubjects, int[] marks) {
        super(age, weight, height, dateOfBirth, address);
        this.roll = roll;
        this.listOfSubjects = listOfSubjects;
        this.marks = marks;
    }

    public String calculateGrade() {
        double average = 0;
        for (int mark : marks) {
            average += mark;
        }
        average /= marks.length;
        
        if (average >= 90) return "A";
        else if (average >= 75) return "B";
        else if (average >= 50) return "C";
        else return "F";
    }

    public void printStudentDetails() {
        printPersonDetails();
        System.out.println("Roll Number: " + roll);
        System.out.print("Subjects: ");
        for (String subject : listOfSubjects) {
            System.out.print(subject + " ");
        }
        System.out.println();
        System.out.print("Marks: ");
        for (int mark : marks) {
            System.out.print(mark + " ");
        }
        System.out.println("\nGrade: " + calculateGrade());
    }
}

class Technician extends Employee {
    public Technician(int age, double weight, double height, String dateOfBirth, String address,
                      double salary, String dateOfJoining, int experience) {
        super(age, weight, height, dateOfBirth, address, salary, dateOfJoining, experience);
    }

    public void printTechnicianDetails() {
        printEmployeeDetails();
        System.out.println("Technician is ready to perform technical tasks.");
    }
}

class Professor extends Employee {
    private String[] courses;
    private String[] listOfAdvisees;

    public Professor(int age, double weight, double height, String dateOfBirth, String address,
                     double salary, String dateOfJoining, int experience, String[] courses) {
        super(age, weight, height, dateOfBirth, address, salary, dateOfJoining, experience);
        this.courses = courses;
        this.listOfAdvisees = new String[0]; // Initially no advisees
    }

    public void addAdvisee(String adviseeName) {
        String[] newList = new String[listOfAdvisees.length + 1];
        System.arraycopy(listOfAdvisees, 0, newList, 0, listOfAdvisees.length);
        newList[listOfAdvisees.length] = adviseeName;
        listOfAdvisees = newList;
    }

    public void removeAdvisee(String adviseeName) {
        int index = -1;
        for (int i = 0; i < listOfAdvisees.length; i++) {
            if (listOfAdvisees[i].equals(adviseeName)) {
                index = i;
                break;
            }
        }
        if (index != -1) {
            String[] newList = new String[listOfAdvisees.length - 1];
            for (int i = 0, j = 0; i < listOfAdvisees.length; i++) {
                if (i != index) {
                    newList[j++] = listOfAdvisees[i];
                }
            }
            listOfAdvisees = newList;
        }
    }

    public void printProfessorDetails() {
        printEmployeeDetails();
        System.out.print("Courses taught: ");
        for (String course : courses) {
            System.out.print(course + " ");
        }
        System.out.println();
        System.out.print("Advisees: ");
        for (String advisee : listOfAdvisees) {
            System.out.print(advisee + " ");
        }
        System.out.println();
    }
}

public class Main {
    public static void main(String[] args) {

        String[] subjects = {"Math", "Physics", "Chemistry"};
        int[] marks = {85, 90, 78};
        Student student = new Student(20, 65, 1.75, "01/01/2003", "123 Street", "S123", subjects, marks);
        student.printStudentDetails();
        System.out.println();

        Technician technician = new Technician(30, 70, 1.80, "15/05/1993", "456 Avenue", 45000, "01/06/2015", 8);
        technician.printTechnicianDetails();
        System.out.println();

        String[] courses = {"Computer Science", "AI"};
        Professor professor = new Professor(45, 80, 1.85, "10/02/1978", "789 Boulevard", 75000, "01/01/2005", 20, courses);
        professor.addAdvisee("Alice");
        professor.addAdvisee("Bob");
        professor.printProfessorDetails();

        professor.removeAdvisee("Alice");
        System.out.println("After removal:");
        professor.printProfessorDetails();
    }
}
