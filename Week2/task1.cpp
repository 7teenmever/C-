#include <iostream>
using namespace std;
int main(){
    for (int i = 1; i <=20 ; i++)
    {
        if (i%2==0)
        {
            cout<<i<<" is even\n";
        }
        if (i%2==1)
        {
            cout<<i<<" is odd\n";
        }
        if (i%5==0)
        {
            cout<<i<<" is divisible by 5\n";
        }
    }
    return 0;
}