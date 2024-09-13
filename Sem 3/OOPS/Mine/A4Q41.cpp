#include <iostream>

using namespace std;

class Integer
{
private:
    int val;

public:
    Integer(int val = 0)
    {
        this->val = val;
    }

    Integer(const Integer &ob1)
    {
        this->val = ob1.val;
    }

    Integer operator=(const Integer &ob1)
    {
        if (this != &ob1)
        {
            val = ob1.val;
        }
        return *this;
    }

    Integer operator++(int)
    {
        Integer temp = *this;
        val++;
        return temp;
    }

    Integer operator+(const Integer &ob1) const
    {
        return Integer(val + ob1.val);
    }

    operator int()
    {
        return val;
    }

    friend ostream &operator<<(ostream &os, const Integer &ob2)
    {
        os << ob2.val;
        return os;
    }
};

int main()
{
    Integer a = 4, b = a, c;
    c = a + b++;
    int i = a;
    cout << a << " " << b << " " << c << endl;
    return 0;
}
