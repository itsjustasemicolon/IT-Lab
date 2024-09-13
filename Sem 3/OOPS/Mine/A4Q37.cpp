#include <iostream>

using namespace std;

class Complex {
private:
    double real;
    double imag;

public:
    Complex(double r = 0.0, double i = 0.0)
    { real = r;
     imag = i;
    }

    Complex operator+( Complex& ob)  {
        return Complex(real + ob.real, imag + ob.imag);
    }

    Complex operator-( Complex& ob)  {
        return Complex(real - ob.real, imag - ob.imag);
    }

    Complex operator*( Complex& ob)  {
        return Complex(
            real * ob.real - imag * ob.imag,
            real * ob.imag + imag * ob.real
        );
    }

    Complex operator/( Complex& ob)  {
        double denominator = ob.real * ob.real + ob.imag * ob.imag;
        return Complex(
            (real * ob.real + imag * ob.imag) / denominator,
            (imag * ob.real - real * ob.imag) / denominator
        );
    }

    void show()  {
        cout << real;
        if (imag >= 0)
            cout << " + " << imag << "i" << endl;
        else
            cout << " - " << -imag << "i" << endl;
    }
};

int main() {
    double r1, i1, r2, i2;

    cout << "Enter real and imaginary part of first complex number: ";
    cin >> r1 >> i1;

    cout << "Enter real and imaginary part of second complex number: ";
    cin >> r2 >> i2;

    Complex a(r1, i1);
    Complex b(r2, i2);

    Complex sum = a + b;
    Complex difference = a - b;
    Complex product = a * b;
    Complex quotient = a / b;

    cout << "a: "; a.show();
    cout << "b: "; b.show();
    cout << "a + b: "; sum.show();
    cout << "a - b: "; difference.show();
    cout << "a * b: "; product.show();
    cout << "a / b: "; quotient.show();

    return 0;
}
