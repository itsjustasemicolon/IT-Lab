#include <iostream>
using namespace std;

class Table
{
    int rows, cols;
    int *data;

public:
    Table(int r, int c)
    {
        rows = r;
        cols = c;
        data = new int[r * c]();
    }

    ~Table()
    {
        delete[] data;
    }

    int *operator[](int i)
    {
        return data + i * cols;
    }

    Table &operator=(Table &ob)
    {
        if (this != &ob)
        {
            delete[] data;
            rows = ob.rows;
            cols = ob.cols;
            data = new int[rows * cols];
            for (int i = 0; i < rows * cols; ++i)
                data[i] = ob.data[i];
        }
        return *this;
    }

    friend istream &operator>>(istream &in, Table &t)
    {
        for (int i = 0; i < t.rows * t.cols; ++i)
            in >> t.data[i];
        return in;
    }

    friend ostream &operator<<(ostream &out, Table &t)
    {
        for (int i = 0; i < t.rows; ++i)
        {
            for (int j = 0; j < t.cols; ++j)
                out << t.data[i * t.cols + j] << " ";
            out << "\n";
        }
        return out;
    }
};

int main()
{
    Table t(4, 5), t1(4, 5);
    cin >> t;
    t[0][0] = 5;
    int x = t[2][3];
    t1 = t;
    cout << t << "\n"
         << t1;
}
