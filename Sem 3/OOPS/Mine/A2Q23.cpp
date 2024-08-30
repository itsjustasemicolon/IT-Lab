#include <iostream>

using namespace std;

class Complex
{
private:
    float real;
    float img;

public:
    void setReal(float r)
    {
        real = r;
    }

    void setImg(float i)
    {
        img = i;
    }

    float getReal() const
    {
        return real;
    }

    float getImg() const
    {
        return img;
    }

    void disp() const
    {
        cout << real << " + " << img << "i" << endl;
    }

    Complex sum(const Complex &c) const
    {
        Complex result;
        result.real = real + c.real;
        result.img = img + c.img;
        return result;
    }
};

int main()
{
    Complex c1, c2, c3;

    c1.setReal(3.2);
    c1.setImg(4.5);

    c2.setReal(1.8);
    c2.setImg(2.3);

    c3 = c1.sum(c2);

    cout << "Complex number 1: ";
    c1.disp();

    cout << "Complex number 2: ";
    c2.disp();

    cout << "Sum of complex numbers: ";
    c3.disp();

    return 0;
}
