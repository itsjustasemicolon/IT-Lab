#include <iostream>
using namespace std;

class DivisionByZeroException
{
public:
    DivisionByZeroException() {}
};

int main()
{
    float x, y, res;
    while (true)
    {
        cout << "enter x and y to get x/y \n";
        cin >> x >> y;
        try
        {
            if (y == 0){
                throw DivisionByZeroException();
            }
            else
            {
                res = x / y;
                cout << "Quotient=" << res << "\n";
            }
        }
        catch (DivisionByZeroException e)
        {
            cout << "Division by zero not possible \nException thrown...\nTerminating program...\n";
            break;
        }
    }
}