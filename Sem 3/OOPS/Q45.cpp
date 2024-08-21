#include <iostream>
using namespace std;

class Base
{
public:
    Base()
    {
        cout << "Base class constructor invoked\n";
    }
    virtual ~Base()
    {
        cout << "Base class destructor invoked\n";
    }
    virtual void func()
    {
        cout << "Base class func() invoked\n";
    }
};

class Derived : public Base
{
public:
    Derived()
    {
        cout << "Derived class constructor invoked\n";
    }
    ~Derived()
    {
        cout << "Derived class destructor invoked\n";
    }
    void func()
    {
        cout << "Derived class func() invoked\n";
    }
};

int main()
{
    /* here, derived class destructor will be invoked first, then the base class destrcutor will be invoked. 
    if base class didnot have virtual destructor then only base class destructor would have been invoked */
    Base *b1 = new Base();
    cout << "\n";

    Base *b2 = new Derived();
    cout << "\n";

    b1->func();
    b2->func();
    cout << "\n";

    delete b1; 
    cout << "\n";

    delete b2;
}