class Employee {
    String name, address;
    int id;
    float sal;

    Employee(String n, String a, int i, float s) {
        name = n;
        address = a;
        id = i;
        sal = s;
    }

    void display() {
        System.out.println("Name: " + name);
        System.out.println("Address: " + address);
        System.out.println("Employee ID: " + id);
        System.out.println("Monthly Salary: " + sal);
    }
}

class Dept {
    String name, loc;
    Employee[] employee = new Employee[5];

    Dept(String n, String l) {
        name = n;
        loc = l;
    }

    void add(int index, String n, String a, int i, float s) {
        if (index >= 0 && index < employee.length) {
            employee[index] = new Employee(n, a, i, s);
        } else {
            System.out.println("Invalid index. Cannot add employee.");
        }
    }

    void remove(int index) {
        if (index >= 0 && index < employee.length && employee[index] != null) {
            System.out.println("Employee " + employee[index].name + " (ID: " + employee[index].id + ") terminated.");
            employee[index] = null;
        } else {
            System.out.println("Invalid index or employee does not exist.");
        }
    }

    void displayAllEmployees() {
        System.out.println("\nEmployees in Department: " + name);
        for (int i = 0; i < employee.length; i++) {
            if (employee[i] != null) {
                System.out.println("Employee " + (i + 1) + ":");
                employee[i].display();
                System.out.println();
            }
        }
    }

    float calculateYearlyExpenditure() {
        float total = 0;
        for (Employee emp : employee) {
            if (emp != null) {
                total += emp.sal * 12;
            }
        }
        return total;
    }

    public static void main(String[] args) {
        Dept dept = new Dept("IT", "SL");
        dept.add(0, "Soham", "123 Main St", 101, 5070f);
        dept.add(1, "Rishika", "456 Park Avenue", 102, 6200f);
        dept.add(2, "Debodit", "273 Santosh Street", 103, 7090f);
        dept.add(3, "Anuska", "720 MT Avenue", 104, 8010f);
        dept.add(4, "Prama", "202 Greenland Avenue", 105, 9040f);

        dept.displayAllEmployees();

        System.out.println("Yearly Expenditure: " + dept.calculateYearlyExpenditure());

        dept.remove(2);
        dept.displayAllEmployees();

        System.out.println("Yearly Expenditure after removal: " + dept.calculateYearlyExpenditure());
    }
}
