#include <iostream>
using namespace std;
int  main(){
    for (int i = 2; i <=50; i++)
    {
        bool isPrime=true;
        for (int n = 2; n < i; n++)
        {
            if (i%n==0)
            {
                isPrime=false;
                break;
            }
        }
        if (isPrime){
            cout<<i<<" ";
        }
    }
    cout<<endl;
    return 0;
}