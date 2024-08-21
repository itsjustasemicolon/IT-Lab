#include <iostream>
using namespace std;

void Strcpy(string& target, const string& source){
    target.clear();
    for (int i = 0; i < source.length(); i++){
        target.push_back(source[i]);
    }
}

int main() {
    string str1 = "Aritra";
    string str2 = "Marik";
    string copd_str1, copd_str2;
    Strcpy(copd_str1, str1);
    Strcpy(copd_str2, str2);
    cout << "str1 : " << str1 << endl;
    cout << "str2 : " << str2 << endl;
    cout << "copd_str1 : " << copd_str1 << endl;
    cout << "copd_str2 : " << copd_str2 << endl;
}