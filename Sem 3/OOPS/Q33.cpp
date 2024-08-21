#include <iostream>
using namespace std;

class INT
{
    int i;

public:
    INT(int a) : i(a) {}
    ~INT() {}
    INT operator++()
    {
        INT temp(0);
        temp.i = ++i;
        return temp;
    }
    INT operator++(int d)
    {
        INT temp(0);
        temp.i = i++;
        return temp;
    }
    operator int()
    {
        return i;
    }
};
int main()
{
    int x = 3;
    INT y = x;
    y++ = ++y;
    x = y;
    return 0;
}