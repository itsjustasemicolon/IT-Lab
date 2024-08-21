#include <iostream>
using namespace std;

class Point
{
    int x, y;
    mutable int z;

public:
    Point()
    {
        x = 0;
        y = 0;
        z = 0;
    }
    void setX(int xx)
    {
        x = xx;
    }
    void setY(int yy)
    {
        y = yy;
    }
    void setZ(int zz) const
    {
        z = zz; /*since z is mutable so setZ can change the value inspite of being constant func */
    }
    int getX() const
    {
        return x;
    }
    int getY() const
    {
        return y;
    }
    int getZ() const
    {
        return z;
    }
};

int main()
{
    Point p;
    p.setX(5);
    p.setY(7);
    p.setZ(-9);

    cout << p.getX() << "," << p.getY() << "," << p.getZ() << "\n";

    p.setZ(10);
    cout << p.getX() << "," << p.getY() << "," << p.getZ() << "\n";
}