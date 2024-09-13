#include <iostream>
#include <cmath>

using namespace std;

class Complex {
private:
    double real, imag;

public:
    Complex(double r = 0.0, double i = 0.0){
        real = r;
        imag = i;
    }

    friend ostream& operator<<(ostream& os, const Complex& c) {
        if (c.imag >= 0)
            os << c.real << " + " << c.imag << "i";
        else
            os << c.real << " - " << -c.imag << "i";
        return os;
    }
};

class Quadratic {
private:
    double a, b, c;

public:
    Quadratic() : a(0), b(0), c(0) {}
    Quadratic(double a, double b, double c) : a(a), b(b), c(c) {}

    Quadratic operator+(const Quadratic& q) const {
        return Quadratic(a + q.a, b + q.b, c + q.c);
    }

    friend ostream& operator<<(ostream& os, const Quadratic& q) {
        os << q.a << "x^2 + " << q.b << "x + " << q.c;
        return os;
    }

    friend istream& operator>>(istream& is, Quadratic& q) {
        is >> q.a >> q.b >> q.c;
        return is;
    }

    double evaluate(double x) const {
        return a * x * x + b * x + c;
    }

    void computeRoots() const {
        double discriminant = b * b - 4 * a * c;
        if (discriminant > 0) {
            double root1 = (-b + sqrt(discriminant)) / (2 * a);
            double root2 = (-b - sqrt(discriminant)) / (2 * a);
            cout << "Real roots: " << root1 << " and " << root2 << endl;
        } else if (discriminant == 0) {
            double root = -b / (2 * a);
            cout << "One real root: " << root << endl;
        } else {
            Complex root1((-b) / (2 * a), sqrt(-discriminant) / (2 * a));
            Complex root2((-b) / (2 * a), -sqrt(-discriminant) / (2 * a));
            cout << "Complex roots: " << root1 << " and " << root2 << endl;
        }
    }
};

int main() {
    Quadratic q1(1, -3, 2);
    Quadratic q2(1, 2, 1);
    Quadratic sum = q1 + q2;

    cout << "q1: " << q1 << endl;
    cout << "q2: " << q2 << endl;
    cout << "Sum: " << sum << endl;

    cout << "q1 evaluated at x=1: " << q1.evaluate(1) << endl;

    cout << "Roots of q1: ";
    q1.computeRoots();

    return 0;
}
