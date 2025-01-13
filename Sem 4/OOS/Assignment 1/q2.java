class Student
{
        String name;
        int marks1, marks2,marks3;

        void assignValues(String s, int m1, int m2, int m3)
        {
                name = s;
                marks1 = m1;
                marks2 = m2;
                marks3 = m3;
        }

        int computeTotal()
        {
                return marks1+marks2+marks3;
        }

        double computeAverage()
        {
                return computeTotal()/3.0;
        }

        void display()
        {
                System.out.println("Student Name: "+name);
                System.out.println("Total Marks : "+computeTotal());
                System.out.println("Average Marks : "+computeAverage());
        }
}

class Demo
{
        public static void main(String args[])
       {
                Student stud = new Student();
                stud.assignValues("Soham",95, 97, 91);
                stud.display();
        }
}
