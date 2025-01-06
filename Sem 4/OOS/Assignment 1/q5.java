class Complex
{
    float re,im;
    Complex()
    {
        re=0;
        im=0;
    }
    Complex(float r)
    {
        re=r;
        im=0;
    }
    Complex(float r, float i)
    {
        re=r;
        im=i;
    }
    void add(Complex c)
    {
        System.out.println("Sum: "+(re+c.re)+"+ ("+(im+c.im)+"i)");
    }
    void mul(Complex c)
    {
        System.out.println("Product: "+(re*c.re-im*c.im)+"+ ("+(re*c.im+im*c.re)+"i)");
    }
    public static void main(String args[])
    {
        Complex c1=new Complex(3,3);
        Complex c2=new Complex(4,-2);
        c1.add(c2);
        c1.mul(c2);
    }
}
