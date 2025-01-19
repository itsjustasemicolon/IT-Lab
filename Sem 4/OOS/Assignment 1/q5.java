class Complex {
    float real, imaginary;

    Complex() {
        real = 0;
        imaginary = 0;
    }

    Complex(float r) {
        real = r;
        imaginary = 0;
    }

    Complex(float r, float i) {
        real = r;
        imaginary = i;
    }

    void add(Complex c) {
        System.out.println("Sum: " + (real + c.real) + "+ (" + (imaginary + c.imaginary) + "i)");
    }

    void mul(Complex c) {
        System.out.println("Product: " + (real * c.real - imaginary * c.imaginary) + "+ (" + (real * c.imaginary + imaginary * c.real) + "i)");
    }
}

class q5 {
    public static void main(String[] args) {
        Complex c1 = new Complex(3, 2);
        Complex c2 = new Complex(4, -2);
        c1.add(c2);
        c1.mul(c2);
    }
}
