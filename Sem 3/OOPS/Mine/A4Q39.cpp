#include <iostream>

using namespace std;

class INT {
private:
    int i;

public:
    INT(int a) : i(a) {}

    ~INT() {}

    INT& operator++() {
        ++i;
        return *this;
    }

    INT operator++(int) {
        INT temp = *this;
        i++;
        return temp;
    }

    INT& operator=( INT& other) {
        if (this != &other) {
            this->i = other.i;
        }
        return *this;
    }

    operator int()  {
        return i;
    }
};


int main() {
    int x = 3;
    INT y = x;
    y++ = ++y;
    x = y;
    cout << "x = " << x << endl;
    return 0;
}
