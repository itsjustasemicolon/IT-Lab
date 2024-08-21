#include <iostream>
#include <math.h>

using namespace std;

class Rectangle
{
private:
    double length;
    double breadth;

public:
    Rectangle(double length, double breadth);
    double area();
    double perimeter();
    void printArea();
};

Rectangle::Rectangle(double length, double breadth)
{
    this->length = length;
    this->breadth = breadth;
}

double Rectangle::area()
{
    return (this->length) * (this->breadth);
}

double Rectangle::perimeter()
{
    return 2 * (this->length + this->breadth);
}

void Rectangle::printArea()
{
    cout << "area is = " << this->area() << "\n";
}

int main()
{
    Rectangle r1(10, 20); // func to calc area of the rectangle
    Rectangle r2(2, 3);
    Rectangle r3(5, 14);
    Rectangle r4(2.5, 9.1);

    r1.printArea();
    r2.printArea();
    r3.printArea();
    r4.printArea();
}