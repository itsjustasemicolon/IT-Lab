#include <iostream>

using namespace std;

inline int add(int p, int q, int r)
{
    return p + q + r;
}

int main()
{
    cout << "Enter 3 numbers : \n";
    int p, q, r;
    cin >> p >> q >> r;
    cout << add(p, q, r) << "\n";

    return 0;
}