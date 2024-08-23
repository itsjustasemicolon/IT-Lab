#include <iostream>

class Rectangle
{
private:
    double length;
    double width;

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
};

int main()
{
    Rectangle rect1(4, 5);
    Rectangle rect2(3, 6);
    Rectangle rect3(2, 8);
    Rectangle rect4(7, 2);

    std::cout << "Area of Rectangle 1: " << rect1.area() << std::endl;
    std::cout << "Area of Rectangle 2: " << rect2.area() << std::endl;
    std::cout << "Area of Rectangle 3: " << rect3.area() << std::endl;
    std::cout << "Area of Rectangle 4: " << rect4.area() << std::endl;

    return 0;
}