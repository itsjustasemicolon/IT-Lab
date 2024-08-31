#include <iostream>
#include <cmath>

using namespace std;

class Shape2D
{
public:
    virtual double area() = 0;
    virtual double perimeter() = 0;
    virtual ~Shape2D() {}
};

class Circle : public Shape2D
{
private:
    double radius;

public:
    Circle(double r)
    {
        radius = r;
    }

    double area()
    {
        return M_PI * radius * radius;
    }

    double perimeter()
    {
        return 2 * M_PI * radius;
    }
};

class Rectangle : public Shape2D
{
private:
    double length, width;

public:
    Rectangle(double l, double w)
    {
        length = l;
        width = w;
    }

    double area()
    {
        return length * width;
    }

    double perimeter()
    {
        return 2 * (length + width);
    }
};

int main()
{
    Shape2D *shapes[5];

    shapes[0] = new Circle(3.0);
    shapes[1] = new Circle(4.0);
    shapes[2] = new Circle(5.0);
    shapes[3] = new Rectangle(4.0, 6.0);
    shapes[4] = new Rectangle(5.0, 7.0);

    for (int i = 0; i < 5; ++i)
    {
        cout << "Shape " << i + 1 << ": " << endl;
        cout << "Area: " << shapes[i]->area() << endl;
        cout << "Perimeter: " << shapes[i]->perimeter() << endl
             << endl;
    }

    for (int i = 0; i < 5; ++i)
    {
        delete shapes[i];
    }

    return 0;
}
