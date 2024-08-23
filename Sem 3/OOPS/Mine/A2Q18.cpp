#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

class Point
{
public:
    double x, y;

    Point(double x = 0, double y = 0) : x(x), y(y) {}

    double distanceTo(const Point &other) const
    {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }
};

class WirelessDevice
{
private:
    int id;
    Point location;
    double transmissionRange;

public:
    WirelessDevice(int id, const Point &loc, double range)
        : id(id), location(loc), transmissionRange(range) {}

    int getId() const
    {
        return id;
    }

    Point getLocation() const
    {
        return location;
    }

    double getTransmissionRange() const
    {
        return transmissionRange;
    }

    void setLocation(const Point &loc)
    {
        location = loc;
    }

    vector<int> findNeighbors(const vector<WirelessDevice> &devices) const
    {
        vector<int> neighbors;
        for (const auto &device : devices)
        {
            if (device.getId() != id &&
                location.distanceTo(device.getLocation()) <= transmissionRange)
            {
                neighbors.push_back(device.getId());
            }
        }
        return neighbors;
    }
};

int main()
{
    srand(static_cast<unsigned>(time(0)));

    const int numDevices = 10;
    vector<WirelessDevice> devices;

    // Instantiate 10 devices with random locations and transmission ranges
    for (int i = 0; i < numDevices; ++i)
    {
        double x = rand() % 100;         // Random x-coordinate between 0 and 99
        double y = rand() % 100;         // Random y-coordinate between 0 and 99
        double range = 10 + rand() % 20; // Random range between 10 and 29
        devices.emplace_back(i, Point(x, y), range);
    }

    // Find neighbors for each device in the initial location
    cout << "Initial neighbors:\n";
    for (const auto &device : devices)
    {
        vector<int> neighbors = device.findNeighbors(devices);
        cout << "Device " << device.getId() << " has neighbors: ";
        for (int neighborId : neighbors)
        {
            cout << neighborId << " ";
        }
        cout << endl;
    }

    // Move devices to new random locations
    for (auto &device : devices)
    {
        double newX = rand() % 100; // Random x-coordinate between 0 and 99
        double newY = rand() % 100; // Random y-coordinate between 0 and 99
        device.setLocation(Point(newX, newY));
    }

    // Find neighbors for each device in the new location
    cout << "\nNew neighbors after moving:\n";
    for (const auto &device : devices)
    {
        vector<int> neighbors = device.findNeighbors(devices);
        cout << "Device " << device.getId() << " has neighbors: ";
        for (int neighborId : neighbors)
        {
            cout << neighborId << " ";
        }
        cout << endl;
    }

    return 0;
}

/*
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
*/