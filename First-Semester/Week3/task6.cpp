#include <iostream>
using namespace std;
int oddCount=0, evenCount=0, primeCount=0, positiveCount=0;
void counter(int number){
    positiveCount++;
    if(number%2==0){
        evenCount++;
    }
    else{
        oddCount++;
    }
    bool isPrime=true;
    for (int i = 2; i < number; i++)
    {
        if (number%i==0)
        {
            isPrime=false;
            break;
        }
    }
    if (isPrime)
        {
            primeCount++;
        }
}
void showResults(){
    cout<<"\n====================\n";
    cout<<"Positive: "<<positiveCount<<endl;
    cout<<"Even: "<<evenCount<<endl;
    cout<<"Odd: "<<oddCount<<endl;
    cout<<"Prime: "<<primeCount<<endl;
    cout<<"====================\n";
}
int main(){
    int x;
    while (true)
    {
        cout<<"Enter Number: ";
        cin>>x;
        if (x<0)
        {
            continue;
        }
        else if (x==0)
        {
            showResults();
            return 0;
        }
        else
        {
            counter(x);
        }
        
    }
    return 0;
}