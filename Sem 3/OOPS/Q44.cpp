#include <iostream>
#include <math.h>
using namespace std;

class Shape
{
public:
    Shape() {}
    virtual float getArea() = 0;
    virtual float getVolume() = 0;
    virtual string getShape() = 0;
};

class TwoDShape : public Shape
{
public:
    virtual float getArea() = 0;
    virtual string getShape() = 0;
};

class ThreeDShape : public Shape
{
public:
    virtual float getArea() = 0;
    virtual float getVolume() = 0;
    virtual string getShape() = 0;
};

class Circle : public TwoDShape
{
    float radius;

public:
    Circle(float rad)
    {
        radius = rad;
    }
    string getShape() { return "Circle"; }
    float getArea()
    {
        return 3.14 * radius * radius;
    }
    float getVolume() { return 0; }
};

class Ellipse : public TwoDShape
{
    float major_axis, minor_axis;

public:
    Ellipse(float maj, float min)
    {
        major_axis = maj;
        minor_axis = min;
    }
    string getShape() { return "Ellipse"; }
    float getArea()
    {
        return 3.14 * major_axis * minor_axis / 4;
    }
    float getVolume() { return 0; }
};

class Triangle : public TwoDShape
{
    float s1, s2, s3;

public:
    Triangle(float a, float b, float c)
    {
        s1 = a;
        s2 = b;
        s3 = c;
    }
    string getShape() { return "Triangle"; }
    float getArea()
    {
        float sp = (s1 + s2 + s3) / 2;
        return sqrt(sp * (sp - s1) * (sp - s2) * (sp - s3));
    }
    float getVolume() { return 0; }
};

class Sphere : public ThreeDShape
{
    float radius;

public:
    Sphere(float rad)
    {
        radius = rad;
    }
    string getShape() { return "Sphere"; }
    float getArea()
    {
        return 4 * 3.14 * radius * radius;
    }
    float getVolume()
    {
        return 4 * 3.14 * radius * radius * radius / 3;
    }
};

class Cube : public ThreeDShape
{
    float side;

public:
    Cube(float s)
    {
        side = s;
    }
    string getShape() { return "Cube"; }
    float getArea()
    {
        return 6 * side * side;
    }
    float getVolume()
    {
        return side * side * side;
    }
};

int main()
{

    Circle c = Circle(6);
    Ellipse e = Ellipse(3, 4);
    Triangle t = Triangle(6, 8, 10);
    Sphere s = Sphere(7);
    Cube cu = Cube(3);

    Shape *S[5];
    S[0] = &c;
    S[1] = &e;
    S[2] = &t;
    S[3] = &s;
    S[4] = &cu;

    for (int i = 0; i < 5; i++)
    {
        cout << "SHAPE " << i + 1 << "\n";
        cout << "Shape: " << S[i]->getShape() << "\n";
        cout << "Area: " << S[i]->getArea() << "\n";
        cout << "Volume: " << S[i]->getVolume() << "\n";
        cout << "\n";
    }
}