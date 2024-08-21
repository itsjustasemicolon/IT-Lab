#include <iostream>
#include <string.h>
using namespace std;

void Swap(char* str1, char* str2, int n)
{
    if (strlen(str1)!=strlen(str2)){
        cout << "String lengths are unequal." << endl;
        return;
    }
    char temp;
    for (int i=0; i<n; i++){
        temp = str1[i];
        str1[i] = str2[i];
        str2[i] = temp;
    }
    return;
}

int main()
{
    int n;
    cout << "Enter length of strings: " << endl;
    cin >> n;
    char s1[n+1], s2[n+1];
    s1[n]=s2[n]='\0';

    cout << "Enter string 1: " << endl;
    for (int i=0; i<n; i++)
        cin >> s1[i];

    cout << "Enter string 2: " << endl;
    for (int i=0; i<n; i++)
        cin >> s2[i];

    cout << "Strings before swapping are: " << endl;
    cout << s1 << endl << s2 << endl;
    cout << "Strings after swapping are: " << endl;
    Swap(s1, s2, n);
    cout << s1 << endl << s2 << endl;
}
