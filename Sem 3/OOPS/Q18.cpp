#include <iostream>
#include <math.h>
using namespace std;

class point_3d
{
private:
    double x;
    double y;
    double z;

public:
    point_3d();
    point_3d(double x, double y, double z);
    static double distance(point_3d, point_3d);
};

point_3d::point_3d()
{
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
}

point_3d::point_3d(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

double point_3d::distance(point_3d p1, point_3d p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
}

int main()
{
    point_3d p1(1, 2, 3);
    point_3d p2(3, 6, 9);

    cout << "distance = " << point_3d::distance(p1, p2) << "\n";
}