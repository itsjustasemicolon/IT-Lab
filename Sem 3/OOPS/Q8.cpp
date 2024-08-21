#include <iostream>

void swap( int &a, int &b){
    int x=a;
    a= b;
    b=x;
}

int main(){
    int a=7;
    int b=8;
    std::cout<<"The value of a before swapping : "<<a<<"\nThe value of b before swapping : "<<b<<"\n";
    swap(a,b);
    std::cout<<"The value of a after swapping : "<<a<<"\nThe value of b after swapping : "<<b<<"\n";

    return 0;
}