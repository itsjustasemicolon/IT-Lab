#include <iostream>
#include <math.h>
#include <string>
using namespace std;

class Complex
{
private:
    float real, imag;

public:
    Complex(float r, float i)
    {
        real = r;
        imag = i;
    }
    float value()
    {
        return sqrt(real * real + imag * imag);
    }
    void disp()
    {
        cout << '(' << real << ',' << imag << ")\n";
    }
};


template <class T>
T maximum(T x, T y)
{
    return (x > y) ? x : y;
}

template <>
Complex maximum(Complex c1, Complex c2)
{
    return c1.value() > c2.value() ? c1 : c2;
}

template <>
string maximum(string s1, string s2)
{
    int max = -1;
    for (int i = 0; i < min(s1.size(), s2.size()); i++)
    {
        if (s1[i] < s2[i])
        {
            max = 1;
            break;
        }
        else if (s1[i] > s2[i])
        {
            max = 0;
            break;
        }
    }
    if (max == -1)
    {
        max = (s1.size() < s2.size()) ? 1 : 0;
    }
    return (max == 1) ? s2 : s1;
}

int main()
{
    cout << maximum(10, 52) << "\n";
    cout << maximum(9.98, 8.03) << "\n";
    cout << maximum('S', 'r') << "\n";

    Complex c1(2, 3), c2(3, -7);
    Complex cmax = maximum(c1, c2);
    cmax.disp();

    string s1 = "ronaldo", s2 = "messi";
    cout << maximum(s1, s2) << "\n";
}