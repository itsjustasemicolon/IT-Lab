class Room
{
double height;
double width;
double breadth;
Room(double h, double w, double b)
{
height = h;
width = w;
breadth = b;
}
double volume()
{
return height*width*breadth;
}
}
class Demo
{
public static void main(String args[])
{
Room r1 = new Room (5,6,7);
Room r2 = new Room (8,10,12);
System.out.println("Vol of Room 1 = + r1.volume());
System.out.println("Vol of Room 2 = + r2.volume());
}
