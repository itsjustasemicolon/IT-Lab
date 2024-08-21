#include <iostream>
using namespace std;

class Shape2D
{
protected:
    float height, width;

public:
    Shape2D(float h = 0, float w = 0)
    {
        height = h;
        width = w;
    }
    virtual float area() = 0;
    virtual float perimeter() = 0;
};

class Circle : public Shape2D
{
    float radius;

public:
    Circle(float r)
    {
        radius = r;
    }
    float area()
    {
        return 3.14 * radius * radius;
    }
    float perimeter()
    {
        return 2 * 3.14 * radius;
    }
};

class Rectangle : public Shape2D
{
public:
    Rectangle(int h, int w)
    {
        height = h;
        width = w;
    }
    float area()
    {
        return height * width;
    }
    float perimeter()
    {
        return 2 * (height + width);
    }
};

int main()
{

    Circle c1(2.3), c2(3.4), c3(5.6);
    Rectangle r1(2, 3), r2(11, 13);

    Shape2D *S[5];

    S[0] = &c1;
    S[1] = &c2;
    S[2] = &c3;

    S[3] = &r1;
    S[4] = &r2;

    for (int i = 0; i < 5; i++)
    {
        cout << "For Shape: " << i + 1 << "\n";
        cout << "Area: " << S[i]->area() << "\n";
        cout << "Perimeter: " << S[i]->perimeter() << "\n";
        cout << "\n\n";
    }
}