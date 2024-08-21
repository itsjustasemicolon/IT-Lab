#include <iostream>

int main(){
    for(int i=0;i<=100;i++){
        float C=i;
        float F=( (float)9/5 * C ) + 32;
        std::cout<<C<<" degree Celsius = "<<F<<" degree Farenheit"<<"\n";
    }
    return 0;
}
