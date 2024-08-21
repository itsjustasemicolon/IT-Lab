#include <bits/stdc++.h>

using namespace std;

inline int add_inline(int a, int b, int c)
{
    return a + b + c;
}


int add(int a, int b, int c)
{
    return a + b + c;
}

int main()
{
    cout << "Enter 3 numbers\n";
    int a, b, c;
    cin >> a >> b >> c;

    clock_t begin, end;

    begin = clock();
    int result = add_inline(a, b, c);
    end = clock();
    cout << "Time for inline function: " << 1000 * double(end - begin) / 1.0 * CLOCKS_PER_SEC << "\n";

    begin = clock();
    result = add(a, b, c);
    end = clock();
    cout << "Time for non-inline function: " << 1000 * double(end - begin) / 1.0 * CLOCKS_PER_SEC << "\n";

    cout << "Inline function takes lesser time \n";
}