#include <iostream>
using namespace std;

class Index {
    int value;

public:
    Index(int v = 0) {
        value = v;
    }

    operator int() {
        return value;
    }

    Index& operator=(int v) {
        value = v;
        return *this;
    }
};

class Integer {
    int value;

public:
    Integer(int v = 0) {
        value = v;
    }

    Integer& operator=(Index idx) {
        value = static_cast<int>(idx);
        return *this;
    }

    operator int() {
        return value;
    }
};

int main() {
    Index in(4), out(10);
    int x = in;
    int y = in + out;
    in = 2;
    Integer i;
    i = in;
}
