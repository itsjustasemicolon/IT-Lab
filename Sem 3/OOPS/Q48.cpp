#include <iostream>
using namespace std;


class CollisionException
{
public:
    CollisionException() {}
};

class InvalidInputException
{
public:
    InvalidInputException() {}
};

class Car
{
    int lane, dir;

public:
    Car(int ll, int dd)
    {
        lane = ll;
        dir = dd;
    }
    void checkValidInput()
    {
        if (lane < 1 || lane > 2 || dir < 0 || dir > 1){
            throw InvalidInputException();
        }
        else{
            cout << "Input validated !\n";
        }
    }
    int checkSafeDriving(Car c)
    {
        int safe = 0;
        if (lane == c.lane)
        {
            if (dir != c.dir){
                throw CollisionException();
            }
            else{
                safe = 1;
            }
        }
        else{
            safe = 1; 
        }
        return safe;
    }
};

int main()
{
    cout << "Lane is either 1 or 2.\nDriving direction: Up = 1 and Down = 0\n\n";

    int l, d;
    cout << "Enter lane and direction of Car 1 : \n";
    cin >> l >> d;
    Car c1(l, d);
    cout << "Enter lane and direction of Car 2 : \n";
    cin >> l >> d;
    Car c2(l, d);
    try
    {
        c1.checkValidInput();
        c2.checkValidInput();
        int isSafe = c1.checkSafeDriving(c2);
        if (isSafe == 1)
        {
            cout << "Cars driving safely!\n";
        }
    }
    catch (InvalidInputException e)
    {
        cout << "Invalid input given for one or more cars\n";
    }
    catch (CollisionException e)
    {
        cout << "Cars not safe. Rerouting to be undertaken to avoid collision.\n";
    }
}