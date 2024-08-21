#include <iostream>
#include <chrono>
using namespace std;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void swapWithoutReference(int *a, int *b) {
    int *temp = a;
    *a = *b;
    *b = *temp;
}

int main() {
    int a = 20, b = 2;
    cout << "Time taken for swapping using reference : "; 
    auto s1 = chrono::high_resolution_clock::now();
    swap(a,b);
    auto f1 = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::nanoseconds>(f1-s1).count() << " ns\n";

    cout << "Time taken for swapping without reference : "; 
    auto s2 = chrono::high_resolution_clock::now();
    swapWithoutReference(&a, &b);
    auto f2 = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::nanoseconds>(f2-s2).count() << " ns\n";
    return 0;
}