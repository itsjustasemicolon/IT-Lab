#include <iostream>

int main(){
    for(int i=1;i<=10;i++){
        std::cout<<i<<"\n";
    }

    //std::cout<<i<<"\n"; //throws error
    //the scope of the variable "i" is within the loop only.
    return 0;
}
