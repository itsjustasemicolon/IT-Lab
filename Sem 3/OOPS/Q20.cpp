#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string>
using namespace std;

class point_2d
{
private:
    double x;
    double y;

public:
    point_2d(double x = 0, double y = 0)
    {
        this->x = x;
        this->y = y;
    }
    static double distance(point_2d p1, point_2d p2)
    {
        return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
    }
};

class Device
{
private:
    point_2d location;
    string id;
    double range;

public:
    Device();
    Device(point_2d location, string id, double range);
    void neighbors(Device devices[], int n_devices);
};

Device::Device()
{
    this->location = point_2d(0, 0);
    this->id = "";
    this->range = 0.0;
}
Device::Device(point_2d location, string id, double range)
{
    this->location = location;
    this->id = id;
    this->range = range;
}

void Device::neighbors(Device devices[], int n_devices)
{
    cout << "Finding neighboring devices with id " << this->id << "\n";
    for (int i = 0; i < n_devices; i++)
    {
        if (this->id != devices[i].id)
        {
            if (point_2d::distance(this->location, devices[i].location) <= this->range)
                cout << "Neighboring device found with id " << devices[i].id << "\n";
        }
    }
}

int main()
{

    int n_devices = 10;
    Device devices[n_devices];

    for (int i = 0; i < n_devices; i++)
    {
        devices[i] = Device(point_2d(rand() * 0.65, rand() * 0.55), "device" + to_string(i), rand() * 0.8);
    }

    for (int i = 0; i < n_devices; i++)
    {
        devices[i].neighbors(devices, n_devices);
    }
}