#include <iostream>
#include<cmath>

using namespace std;

class Point
{
        double x, y;
        public:
                Point(double x = 0, double y = 0)
                {
                        this->x=x;
                        this->y=y;
                }

        ~Point()
        {
                cout<<"Point destroyed"<<endl;
        }


        void setX(double x)
        {       this->x=x;
        }

        void setY(double y)
        {       this->y=y;
        }


        double operator-(Point &ob)
        {
                double dx = x - ob.x;
                double dy = y - ob.y;

                return sqrt(dx*dx + dy*dy);
        }
};

int main() {
    Point p1(3.0, 4.0);
    Point p2(0.0, 0.0);

   cout << "Distance: " << (p1 - p2) << endl;

    return 0;
}
