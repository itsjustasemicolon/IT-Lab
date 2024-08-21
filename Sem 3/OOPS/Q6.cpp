#include <iostream>

#define PI 3.14

int main(){
    int rad;
    std::cout<<"Enter radius of the circle : ";
    std::cin>>rad;

    float area= PI*(rad*rad);
    std::cout<<"The area of the circle is = "<<area<<"\n";

    return 0;
}
