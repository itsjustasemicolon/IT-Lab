#include <iostream>
#include <math.h>

using namespace std;

class Complex
{
private:
    float real, imag;

public:
    void setReal(float r);
    void setImag(float i);
    double getReal();
    double getImag();
    Complex sum(Complex);
    void disp();
};

void Complex::setReal(float r)
{
    this->real = r;
}
void Complex::setImag(float i)
{
    this->imag = i;
}
double Complex::getReal()
{
    return this->real;
}
double Complex::getImag()
{
    return this->imag;
}

Complex Complex::sum(Complex c)
{
    Complex temp;

    temp.real = this->real + c.real;
    temp.imag = this->imag + c.imag;

    return temp;
}

void Complex::disp()
{
    cout << '(' << this->real << "," << this->imag << ")\n";
}

int main()
{
    Complex c1, c2;

    c1.setReal(5);
    c1.setImag(-7);

    c1.disp();

    c2.setReal(9);
    c2.setImag(4);

    c2.disp();

    Complex c3 = c1.sum(c2);
    cout << "The sum is: ";
    c3.disp();
}