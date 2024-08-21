#include <iostream>

int factorial(int i){
    if(i==0)return 1;

    else return (i*factorial(i-1));
}

int main() {

  int x;
  for(int i=1;i<=6;i++){
    x= factorial(i);
    std::cout<<i<<"! = "<<x<<"\n";
  }

  return 0;
}
