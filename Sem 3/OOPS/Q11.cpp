#include <iostream>
using namespace std;

int factorial(const int &n)
{
    int ans=1;
    for (int i=2; i<=n; i++){
        ans *= i;
    }
    return ans;
}
int main()
{
    cout << "The factorial is : "<<factorial(5)<<"\n";
}