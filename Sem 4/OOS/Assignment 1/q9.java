class Person {
    int age;
    double weight;
    double height;
    String dateOfBirth;
    String address;

    Person(int age, double weight, double height, String dateOfBirth, String address) {
        this.age = age;
        this.weight = weight;
        this.height = height;
        this.dateOfBirth = dateOfBirth;
        this.address = address;
    }

    public void printDetails() {
        System.out.println("Age: " + age + ", Weight: " + weight + ", Height: " + height +
                ", Date of Birth: " + dateOfBirth + ", Address: " + address);
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

    public void printDetails() {
        super.printDetails();
        System.out.println("Salary: " + salary + ", Date of Joining: " + dateOfJoining + ", Experience: " + experience + " years");
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

    public void printDetails() {
        super.printDetails();
        System.out.println("Roll Number: " + roll + ", Grade: " + calculateGrade());
    }
}

class Technician extends Employee {
    public Technician(int age, double weight, double height, String dateOfBirth, String address,
                      double salary, String dateOfJoining, int experience) {
        super(age, weight, height, dateOfBirth, address, salary, dateOfJoining, experience);
    }

    public void printDetails() {
        super.printDetails();
        System.out.println("Technician ready for technical tasks.");
    }
}

class Professor extends Employee {
    private final String[] courses;
    private String[] advisees = new String[0];

    public Professor(int age, double weight, double height, String dateOfBirth, String address,
                     double salary, String dateOfJoining, int experience, String[] courses) {
        super(age, weight, height, dateOfBirth, address, salary, dateOfJoining, experience);
        this.courses = courses;
    }

    public void addAdvisee(String adviseeName) {
        String[] newAdvisees = new String[advisees.length + 1];
        System.arraycopy(advisees, 0, newAdvisees, 0, advisees.length);
        newAdvisees[advisees.length] = adviseeName;
        advisees = newAdvisees;
    }

    public void removeAdvisee(String adviseeName) {
        int index = -1;
        for (int i = 0; i < advisees.length; i++) {
            if (advisees[i].equals(adviseeName)) {
                index = i;
                break;
            }
        }
        if (index != -1) {
            String[] newAdvisees = new String[advisees.length - 1];
            for (int i = 0, j = 0; i < advisees.length; i++) {
                if (i != index) {
                    newAdvisees[j++] = advisees[i];
                }
            }
            advisees = newAdvisees;
        }
    }

    public void printDetails() {
        super.printDetails();
        System.out.print("Courses: ");
        for (String course : courses) {
            System.out.print(course + " ");
        }
        System.out.println("\nAdvisees: ");
        for (String advisee : advisees) {
            System.out.print(advisee + " ");
        }
        System.out.println();
    }
}

public class q9 {
    public static void main(String[] args) {

        String[] subjects = {"Math", "Physics", "Chemistry"};
        int[] marks = {85, 90, 78};
        Student student = new Student(20, 65, 1.75, "17/01/2003", "123 Park Street", "S123", subjects, marks);
        student.printDetails();
        System.out.println();

        Technician technician = new Technician(30, 70, 1.80, "15/05/2004", "456 Java Avn", 45000, "01/06/2015", 8);
        technician.printDetails();
        System.out.println();

        String[] courses = {"OOS", "AI/ML"};
        Professor professor = new Professor(45, 80, 1.85, "10/02/2005", "789 Santoshpur", 75000, "01/01/2005", 20, courses);
        professor.addAdvisee("Soham");
        professor.addAdvisee("Debo");
        professor.printDetails();

        professor.removeAdvisee("Soham");
        System.out.println("After removal:");
        professor.printDetails();
    }
}
