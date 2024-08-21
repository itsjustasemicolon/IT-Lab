#include <iostream>

long long int factorial(const int a){
    if (a==0) return 1;

    else return (a*factorial(a-1));
}

int main(){
    int n;
    std::cout<<"Enter the number : ";
    std::cin>>n;
    const int a=n;
	long long int ans = factorial(a);
    std::cout<<"The factorial of "<<a<<" is = "<<ans<<"\n";
    return 0;
}
