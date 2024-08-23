#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

class Vector {
private:
    vector<int> data;

public:
    // Constructor
    Vector(int size) : data(size) {}

    // Constructor with initializer list
    Vector(initializer_list<int> list) : data(list) {}

    // Copy constructor
    Vector(const Vector& other) : data(other.data) {}

    // Accessor for vector size
    int size() const {
        return data.size();
    }

    // Operator for accessing elements
    int& operator[](int index) {
        if (index < 0 || index >= size()) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }

    const int& operator[](int index) const {
        if (index < 0 || index >= size()) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }

    // Addition of two vectors
    Vector operator+(const Vector& other) const {
        if (size() != other.size()) {
            throw invalid_argument("Vectors must be of the same size for addition");
        }
        Vector result(size());
        for (int i = 0; i < size(); ++i) {
            result[i] = data[i] + other[i];
        }
        return result;
    }

    // Subtraction of two vectors
    Vector operator-(const Vector& other) const {
        if (size() != other.size()) {
            throw invalid_argument("Vectors must be of the same size for subtraction");
        }
        Vector result(size());
        for (int i = 0; i < size(); ++i) {
            result[i] = data[i] - other[i];
        }
        return result;
    }

    // Equality check
    bool operator==(const Vector& other) const {
        return data == other.data;
    }

    // Inequality check
    bool operator!=(const Vector& other) const {
        return data != other.data;
    }

    // Less than comparison
    bool operator<(const Vector& other) const {
        return data < other.data;
    }

    // Greater than comparison
    bool operator>(const Vector& other) const {
        return data > other.data;
    }

    // Printing the vector
    void print() const {
        for (int i = 0; i < size(); ++i) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    // Create two vectors
    Vector v1 = {1, 2, 3};
    Vector v2 = {4, 2, 11};

    // Perform addition
    Vector v3 = v1 + v2;
    cout << "v1 + v2 = ";
    v3.print();

    // Perform subtraction
    Vector v4 = v1 - v2;
    cout << "v1 - v2 = ";
    v4.print();

    // Check equality
    cout << "v1 == v2: " << (v1 == v2 ? "True" : "False") << endl;

    // Check inequality
    cout << "v1 != v2: " << (v1 != v2 ? "True" : "False") << endl;

    // Check less than
    cout << "v1 < v2: " << (v1 < v2 ? "True" : "False") << endl;

    // Check greater than
    cout << "v1 > v2: " << (v1 > v2 ? "True" : "False") << endl;

    return 0;
}
